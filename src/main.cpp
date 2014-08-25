#include <GL/glut.h> // Include the GLUT header file  
#include <math.h>
float angle_x = 0;
float angle_y = 0;
float angle_z = 0;

void myTranslatef( float x, float y, float z){
    const float mat[] = {1.0,0,0,0,0,1.0,0,0,0,0,1.0,0,x,y,z,1.0};
    glMultMatrixf(&mat[0]);
    return ;
};

void myScalef(float sx, float sy, float sz){
    const float mat[] = {sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1.0};
    glMultMatrixf(&mat[0]);
    return ;
};

void myRotatef(float theta,float px, float py, float pz){
    theta *= M_PI/180;
    float m[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    float l = sqrt(px*px + py*py + pz*pz);
    float cosa = cos(theta);
    float onec = 1-cosa;
    float sina = sin(theta);
    float ux = px/l;
    float uy = py/l;
    float uz = pz/l;
    m[0] = ux*ux*onec + cosa;
    m[4] = ux*uy*onec - uz*sina;
    m[8] = ux*uz*onec + uy*sina;
    m[1] = ux*uy*onec + uz*sina;
    m[5] = uy*uy*onec + cosa;
    m[9] = uy*uz*onec - ux*sina;
    m[2] = ux*uz*onec - uy*sina;
    m[6] = uz*uy*onec + ux*sina;
    m[10] = uz*uz*onec + cosa;
    const float mat[] = {m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]};
    glMultMatrixf(&mat[0]);
    return ;
};

void handleKeypressSpecial(int key, int x, int y ) {
//x and y are the current mouse coordinates
	switch (key) {
		case GLUT_KEY_UP:{
			angle_x += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_DOWN:{
			angle_x -= 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_LEFT:{
			angle_y += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_RIGHT:{
			angle_y -= 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_PAGE_UP:{
			angle_z += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_PAGE_DOWN:{
			angle_z -= 2;
			glutPostRedisplay();
			break;
		}

	}
}


void display (void) 
{    
	glClearColor(0, 0, 0, 1); // Clear the background of our window
	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer 
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  

	myTranslatef(0, 0, -10); // Push eveything 5 units back into the scene, otherwise we won't see the primitive
	myScalef(0.4,0.4,0.4);
	myRotatef(angle_x, 1, 0, 0);
	myRotatef(angle_y, 0, 1, 0);
	myRotatef(angle_z, 0, 0, 1);
	glColor3f(0.4,0.4,0.4);

		glPointSize(5);
		glBegin(GL_POINTS);
			glVertex3f(6,0,0);
		glEnd();

		myRotatef(30,1,0,0);
		glutWireCube(2);
		myRotatef(-30,1,0,0);

		glColor3f(0.8,0.8,0.4);
		myTranslatef(1,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(0,3,3);
			glVertex3f(0,-3,3);
			glVertex3f(0,-3,-3);
			glVertex3f(0,3,-3);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-5,5,5);
			glVertex3f(-5,-5,5);
			glVertex3f(-5,-5,-5);
			glVertex3f(-5,5,-5);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(6,0,0);
			glVertex3f(-5,5,5);
			glVertex3f(6,0,0);
			glVertex3f(-5,-5,5);
			glVertex3f(6,0,0);
			glVertex3f(-5,-5,-5);
			glVertex3f(6,0,0);
			glVertex3f(-5,5,-5);
		glEnd();

		myTranslatef(-1,0,0);

	glutSwapBuffers();
}  
  
void reshape (int width, int height) 
{  
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	//glOrtho(0,0,0,0,1,1);
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); //view angle (in degrees), aspect ratio, near and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  	  
}  
  
int main (int argc, char **argv) 
{  
	glutInit(&argc, argv); // Initialize GLUT  
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (500, 500); // Set the width and height of the window  
	glutInitWindowPosition (100, 100); // Set the position of the window  
	glutCreateWindow ("3D Rendering Pipeline"); // Set the title for the window  
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutSpecialFunc(handleKeypressSpecial);
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  
	glutMainLoop(); // Enter GLUT's main loop  
}  

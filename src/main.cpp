#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/polygon.h"
#include "../include/scene.h"
#include "../include/transformations.h"
using namespace std;

void myTranslatef( float x, float y, float z){
	    const float mat[] = {1.0,0,0,0,0,1.0,0,0,0,0,1.0,0,x,y,z,1.0};
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

	myTranslatef(0, 0, -3); // Push eveything 5 units back into the scene, otherwise we won't see the primitive
//	myScalef(1.4,1.4,1.4);
//	myRotatef(angle_x, 1, 0, 0);
//	myRotatef(angle_y, 0, 1, 0);
//	myRotatef(angle_z, 0, 0, 1);

	default_scene();

//	myTranslatef(-1,0,0);


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
	glutInitWindowSize (screen_width, screen_height); // Set the width and height of the window
	glutInitWindowPosition (window_position_x, window_position_y); // Set the position of the window
	glutCreateWindow ("3D Rendering Pipeline"); // Set the title for the window  
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutSpecialFunc(handleKeypressSpecial);
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  
	glutMainLoop(); // Enter GLUT's main loop  
}  

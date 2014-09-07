#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/structs.h"
#include "../include/polygon.h"
#include "../include/matrix.h"
#include "../include/transformations.h"
#include "../include/clipping.h"
#include "../include/scene.h"

using namespace std;

/* Global Variable Declarations
 * */
vector<polygon*> sceneData;
polygon clippingArea;
vector<float*> clipping_plane_eq;
float* viewingCordMatrix;
float* inverseviewingCordMatrix;

/* For manipulating the rotation of objects
 * */
float angle_x = 0;
float angle_y = 0;
float angle_z = 0;
float scale_factor = 1;


void handleKeypressSpecial(int key, int x, int y ) {
//x and y are the current mouse coordinates
	switch (key) {
		case GLUT_KEY_UP:{
			angle_x += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_DOWN:{
			angle_x += -2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_LEFT:{
			angle_y += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_RIGHT:{
			angle_y += -2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_PAGE_UP:{
			angle_z += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_PAGE_DOWN:{
			angle_z += -2;
			glutPostRedisplay();
			break;
		}

		case GLUT_KEY_HOME:{
			scale_factor += 0.05;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_INSERT:{
			scale_factor += -0.05;
			glutPostRedisplay();
			break;
		}
	}
}



void reshape (int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10,10,-10,10,-100,100);
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void){  
	
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity(); 

	glTranslatef(0,0,-10);
	glScalef(scale_factor,scale_factor,scale_factor);
	glRotatef(angle_x, 1, 0, 0);
	glRotatef(angle_y, 0, 1, 0);
	glRotatef(angle_z, 0, 0, 1);
	glTranslatef(0,0,10);

	clippingArea.draw();
	for(int i=0;i<sceneData.size();i++)
		sceneData.at(i)->draw();

    glFlush();
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(screen_width/4,screen_height/4);
    glutCreateWindow("Polygon Clipping!");
    glutSpecialFunc(handleKeypressSpecial);
    init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);    
	glutMainLoop();
    return 0;
}

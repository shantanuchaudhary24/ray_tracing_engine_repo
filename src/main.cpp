
#include "../include/headers.h"

using namespace std;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 20.0f, 50.0f, 50.0f, 0.0f };
const GLfloat light_position2[] = { -20.0f, -50.0f, -50.0f, 0.0f };


void initRendering(){
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

	glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
}

void handleResize(int w, int h){
    screen_width = w ;
    screen_height = h ;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 1.0, 2000.0);

}


void handleMouseMotion(int x, int y)
{
	GLdouble model_view[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	double dx; double dy; double dz;
	GLfloat depth[2];
	glReadPixels (x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, depth);
	gluUnProject(x, y, depth[0], model_view, projection, viewport, &dx, &dy, &dz);

    glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y ) {

	//x and y are the current mouse coordinates
	switch (key) {
		case 27:{ //escape key
			exit(0); //exit the program
			break;
			}
		case 109:{
            glutPostRedisplay();
			break;
		}
	}
	return  ;
}


void handleKeypressSpecial(int key, int x, int y ) {
//x and y are the current mouse coordinates
	switch (key) {
		case GLUT_KEY_UP:{

			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_DOWN:{

			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_LEFT:{

			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_RIGHT:{

			glutPostRedisplay();
			break;
		}

	}
}

void drawScene(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glPushMatrix();

	/* Insert translation and rotation functions here!
	 *
	 * */
//	myScalef(0.1,0.1,0.1);
//
//	myTranslatef(0,0,-200);
//
//	glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
//
//	glRotatef(angle_y, 0.0f, 1.0f, 0.0f);

	glColor3f(0.4,0.4,0.4);


//    if(ball){
//        glPushMatrix();
//        myTranslatef(ball_coor[0],ball_coor[1],ball_coor[2]);
//        glutSolidSphere(20,30,30);
//        glPopMatrix();
//    }

	glPopMatrix();
	glutSwapBuffers();
}


void handleMouse(int button, int state, int x, int y){

	switch(button)
    {
        case GLUT_LEFT_BUTTON :{
		    if(state == GLUT_DOWN)
            {
//				if(!ball){
//                glutMotionFunc(NULL);
//                setDefault();
//				fist = !fist ;
//                if(fist)
//                glutIdleFunc(createFist);
//				else
//                glutIdleFunc(openFist);
//                }
//                else{
//                glutMotionFunc(handleMouseMotion);
                }
			}
            if(state == GLUT_UP){
                glutMotionFunc(NULL);
//                if(!ball) return ;
//                else{
//                    glutIdleFunc(NULL);
//                    grabBall();
//                    glutPostRedisplay();
//                }
            }
        }
		break;
	}
}

int main(int argc, char** argv){

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(screen_width,screen_height);

	glutCreateWindow("Assignment 1 - 2010CS50282");

	initRendering();

	glutDisplayFunc(drawScene);

	glutSpecialFunc(handleKeypressSpecial);

	glutKeyboardFunc(handleKeypress);

    glutMouseFunc(handleMouse);

    glutMotionFunc(NULL);

	glutReshapeFunc(handleResize);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();

	return 0;
}

#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/polygon.h"
#include "../include/scene.h"
#include "../include/transformations.h"
#include "../include/frustum.h"
#include "../include/clipping.h"

using namespace std;

/* Main function where the basic OpenGL calls take place
 * Basic Clipping and Projection calls are called here.
 * */

float angle_x = 0.0f;
float angle_y = 0.0f;
float angle_z = 0.0f;

/* Defines the clipping area*/
polygon clippingArea;

/* Stores info on clipping plane*/
vector<float*> clipping_plane_eq;

/* Defines the number of objects to be drawn in the scene*/
#define NUMBER_OF_OBJECTS 3

/* For storing details of objects in the scene*/
polygon scene_data[NUMBER_OF_OBJECTS];

/* Handles key presses for changing rotation angles*/
void handleKeypressSpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: {
		angle_x = 2.5;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_DOWN: {
		angle_x = -2.5;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_LEFT: {
		angle_y = 2.5;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_RIGHT: {
		angle_y = -2.5;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_PAGE_UP: {
		angle_z = 2.5;
		glutPostRedisplay();
		break;
	}
	case GLUT_KEY_PAGE_DOWN: {
		angle_z = -2.5;
		glutPostRedisplay();
		break;
	}

	}
}

/* Display callback function for drawing scene objects from scene_data array*/
void display(void) {
	glClearColor(0, 0, 0, 1); // Clear the background of our window
	glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	int i = 0;
	for (i = 0; i < NUMBER_OF_OBJECTS; i++) {
		scene_data[i].draw();
		scene_data[i].rotate(1, 0, 0, angle_x);
		scene_data[i].rotate(0, 1, 0, angle_y);
		scene_data[i].rotate(0, 0, 1, angle_z);
	}
	glutSwapBuffers();
}

void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei) width, (GLsizei) height); // Set our view port to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(60, (GLfloat) width / (GLfloat) height, 1.0, 100.0); //view angle (in degrees), aspect ratio, near and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  	  
}

void init() {
	/* Generating objects*/
	scene_data[0] = generate_plane(0, 0, 0, 3, 3, 0, -3, -10);// Generate plane
	scene_data[1] = generate_cuboid(0, 0, 0, 1.5, 1.5, 1.5, -1, 1, -10);// Generate cuboid

	float eye[] = { 0.0f, 0.0f, 0.0f };
	float eyenormal[] = { 0.0f, 0.0f, -1.0f };
	float d1 = 10;
	float d2 = 12;
	float width = 1;
	float height = 1;

	RGB_value color = RGB_value(0.5, 0.5, 0.5);

	float* frustrum = create_frustrum(eye, eyenormal, d1, d2, width, height);

	int planes[] = { 3, 2, 1, 0,		//front plane
			4, 5, 6, 7,		//back plane
			2, 6, 5, 1,		//left plane
			0, 4, 7, 3,		//right plane
			1, 5, 4, 0,		//up plane
			3, 7, 6, 2,		//down plane
			};
	int i, j, k;
	for (i = 0; i < 6; i++) {
		float verts[3 * 4];
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 3; k++) {
				verts[3 * j + k] = frustrum[3 * planes[4 * i + j] + k];
			}
		}

		vertex face[] = { vertex(verts[0], verts[1], verts[2]), vertex(verts[3],
				verts[4], verts[5]), vertex(verts[6], verts[7], verts[8]),
				vertex(verts[9], verts[10], verts[11]), };

		clippingArea.add_face(4, face, &color);
		clipping_plane_eq.push_back(
				plane_equation(clippingArea.get_face_set(i)));
	}

//	sceneData.push_back(clippingArea);
	scene_data[2] = clippingArea;
	for (i = 0; i < NUMBER_OF_OBJECTS; i++) {

//		for(j=0;j<scene_data[i].get_num_faces();j++)
//			polygonClipping(scene_data[i].get_face_set(j));
	}

}

/* Main function
 * */
int main(int argc, char **argv) {
	clippingArea = polygon();

	glutInit(&argc, argv); // Initialize GLUT  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize(screen_width, screen_height); // Set the width and height of the window
	glutInitWindowPosition(window_position_x, window_position_y); // Set the position of the window
	glutCreateWindow("3D Rendering Pipeline"); // Set the title for the window
	init();
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutSpecialFunc(handleKeypressSpecial);
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  
	glutMainLoop(); // Enter GLUT's main loop  
}

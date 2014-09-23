#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/structs.h"
#include "../include/polygon.h"
#include "../include/matrix.h"
#include "../include/transformations.h"
#include "../include/clipping.h"
#include "../include/scene.h"
#include "../include/parser.h"
#include "../include/illumination.h"
#include <fstream>
using namespace std;

/* Global Variable Declarations
 * */
vector<polygon*> sceneData;
polygon clippingArea;
vector<float*> clipping_plane_eq;
float* viewingCordMatrix;
float* inverseviewingCordMatrix;
GLuint texName;
config* parameters;
bool drawScene=false;

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
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); 

	glTranslatef(0,0,-14);
	glScalef(scale_factor,scale_factor,scale_factor);
	glRotatef(angle_x, 1, 0, 0);
	glRotatef(angle_y, 0, 1, 0);
	glRotatef(angle_z, 0, 0, 1);
	glTranslatef(0,0,14);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);
	face_info* face=clippingArea.get_face_set(1);
	glBegin(GL_QUADS);
		glTexCoord2f(1,0); glVertex3f(face->vertex_set[0].x_pos,face->vertex_set[0].y_pos,face->vertex_set[0].z_pos);
		glTexCoord2f(0,0); glVertex3f(face->vertex_set[1].x_pos,face->vertex_set[1].y_pos,face->vertex_set[1].z_pos);
		glTexCoord2f(0,1); glVertex3f(face->vertex_set[2].x_pos,face->vertex_set[2].y_pos,face->vertex_set[2].z_pos);
		glTexCoord2f(1,1); glVertex3f(face->vertex_set[3].x_pos,face->vertex_set[3].y_pos,face->vertex_set[3].z_pos);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	if(drawScene)
	{
		clippingArea.draw(false);
		for(int i=0;i<sceneData.size();i++)
			sceneData.at(i)->draw(true);

		DrawLight(parameters->light_source);
		DrawSphere(parameters->sphere_array);

	}

    glFlush();
}

int main(int argc,char *argv[]){

	/* Input Verification*/
	if(argc < 2)
	{
		cout << "Error:CONFIG FILE NOT SUPPLIED!" << endl;
		exit(0);
	}

	/* Input file descriptor*/
	std::ifstream inp;

	/* Name of input file*/
	inp.open(argv[1]);

	/* Default dimensions of OpenGL window */
	int screen_width = 800 ;
	int screen_height = 400 ;

	/* Initialization of configuration structure and memory allocation*/
	config *outp;
	outp = (config *)malloc(sizeof(config));
	outp->eye_pos = (float *)malloc(3*sizeof(float));
	outp->eye_up = (float *)malloc(3*sizeof(float));
	outp->eye_side = (float *)malloc(3*sizeof(float));
	outp->eye_normal = (float *)malloc(3*sizeof(float));
	outp->window_width = 0;
	outp->window_height = 0;
	outp->backplane_distance = 0;
	outp->viewplane_distance = 0;
	outp->frontplane_width = 0;
	outp->frontplane_height = 0;
	outp->backplane_distance = 0;
	outp->specular_coeff = 0;
	outp->specular_exp = 0;
	outp->ambient_coeff = 0;
	outp->diffuse_coeff = 0;

	/* Read input parameters from configuration file*/
	read_config(inp,outp);

	parameters=outp;
	/* Set window dimensions from configuration file*/
	screen_width  = outp->window_width;
	screen_height = outp->window_height;

	/* Initial spawning position of GLUT window*/
	int window_position_x = screen_width/4;
	int window_position_y = screen_height/6;

	/* Preliminary OpenGL calls*/
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(screen_width/4,screen_height/4);
    glutCreateWindow("Ray Tracing");
    glutSpecialFunc(handleKeypressSpecial);

    /* Initialization of functions*/
    init(outp);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);    
	glutMainLoop();

	/* Free memory alloted to the configuration structure and its associated fields*/
	free(outp->eye_pos);
	free(outp->eye_up);
	free(outp->eye_side);
	free(outp->eye_normal);
	for(int i=0;i<outp->sphere_array.size();i++){
		free(outp->sphere_array.at(i)->center);
		free(outp->sphere_array.at(i)->color);
		free(outp->sphere_array.at(i));
	}
	for(int i=0;i<outp->light_source.size();i++){
		destroy_light(outp->light_source.at(i));
	}
	for(int i=0;i<outp->cube_array.size();i++){
		destroy_cube(outp->cube_array.at(i));
	}
	outp->light_source.clear();
	outp->sphere_array.clear();
	free(outp);
    return 0;
}

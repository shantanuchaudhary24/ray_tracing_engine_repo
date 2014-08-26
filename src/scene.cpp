/*
 * scene.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */
#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/polygon.h"
#include "../include/transformations.h"

/* This function is used to create the various 3D shapes in the scene.
 * The position of the various objects within the scene are fixed.
 * */
void default_scene(void)
{

	vertex plane_vertices[] = {
		vertex(-0.6, -0.75, 0),
		vertex(0.6, -0.75, 0),
		vertex(0.0, 0.75, 0)
	};

	vertex square_vertices[] = {
		vertex(-1.05, -0.5, 0.5),
		vertex(-1.05, 0.5, 0.5),
		vertex(1.05, 0.5, 0.5),
		vertex(1.05, -0.5, 0.5),
	};

	vertex cube1[] = {
		vertex(-1.05, -0.5, 0.5),
		vertex(-1.05, 0.5, 0.5),
		vertex(1.05, 0.5, 0.5),
		vertex(1.05, -0.5, 0.5),
	};
	vertex cube2[] = {
			vertex(-1.05, -0.5, 0.5),
			vertex(-1.05, 0.5, 0.5),
			vertex(1.05, 0.5, 0.5),
			vertex(1.05, -0.5, 0.5),
		};
	vertex cube3[] = {
			vertex(-1.05, -0.5, 0.5),
			vertex(-1.05, 0.5, 0.5),
			vertex(1.05, 0.5, 0.5),
			vertex(1.05, -0.5, 0.5),
		};
	vertex cube4[] = {
			vertex(-1.05, -0.5, 0.5),
			vertex(-1.05, 0.5, 0.5),
			vertex(1.05, 0.5, 0.5),
			vertex(1.05, -0.5, 0.5),
		};

	vertex cube5[] = {
			vertex(-1.05, -0.5, 0.5),
			vertex(-1.05, 0.5, 0.5),
			vertex(1.05, 0.5, 0.5),
			vertex(1.05, -0.5, 0.5),
		};
	vertex cube6[] = {
			vertex(-1.05, -0.5, 0.5),
			vertex(-1.05, 0.5, 0.5),
			vertex(1.05, 0.5, 0.5),
			vertex(1.05, -0.5, 0.5),
		};

	RGB_value color = color_comp(0.5,0.5,0.23);

	polygon plane = polygon();
	polygon square = polygon();
	plane.add_face(3,plane_vertices,&color);
	plane.draw();
	plane.scale(3,1,0);
	plane.draw();

//	square.add_face(4,square_vertices,&color);
//	square.draw();
//	myRotatef(angle_x, 1, 0, 0);
//	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer
//	square.translate(-,-,-);
//	square.scale(2,2,2);
//	square.draw();

	return ;
}





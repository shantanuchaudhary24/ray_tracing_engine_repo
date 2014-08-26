/*
 * scene.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */
#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/polygon.h"

/* This function is used to create the various 3D shapes in the scene.
 * The position of the various objects within the scene are fixed.
 * */
void default_scene(void)
{

	vertex plane_vertices[] = {
			vertex(1,-0.6, -0.75, 0.5),
			vertex(2,0.6, -0.75, 0),
			vertex(3, 0, 0.75, 0)
	};

	RGB_value color = color_comp(1,0,0);

	polygon plane = polygon();
	plane.add_face(3,plane_vertices,&color);
	plane.draw_polygon();

	return ;
}





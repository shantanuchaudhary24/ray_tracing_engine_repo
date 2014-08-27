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

extern float angle_x ;
extern float angle_y ;
extern float angle_z ;

void draw_plane(float x, float y, float z, float l, float b, float x_distance, float y_distance, float z_distance, float x_rot, float y_rot, float z_rot)
{
	RGB_value color = color_comp(0.5,0.5,0.23);

	vertex plane_vertices[] = {
		vertex(x+l/2,y+b/2,0),
		vertex(x+l/2,y-b/2,0),
		vertex(x-l/2,y-b/2,0),
		vertex(x-l/2,y+b/2,0)
	};

	polygon plane = polygon( x, y, z,x_distance, y_distance, z_distance,4,plane_vertices,&color);
	plane.rotate(1,0,0,angle_x);
	plane.rotate(0,1,0,angle_y);
	plane.rotate(0,0,1,angle_z);
	plane.draw();
	return;
}

void draw_cuboid(float x, float y, float z, float l, float b, float h, float x_distance, float y_distance, float z_distance)
{
	RGB_value color = color_comp(0.5,0.5,1);

	vertex face1_vertices[] = {
		vertex(x+l/2,y+h/2,z+b/2),
		vertex(x+l/2,y-h/2,z+b/2),
		vertex(x-l/2,y-h/2,z+b/2),
		vertex(x-l/2,y+h/2,z+b/2)
	};

	vertex face2_vertices[] = {
		vertex(x+l/2,y+h/2,z-b/2),
		vertex(x+l/2,y-h/2,z-b/2),
		vertex(x-l/2,y-h/2,z-b/2),
		vertex(x-l/2,y+h/2,z-b/2)
	};

	vertex face3_vertices[] = {
		vertex(x+l/2,y+h/2,z+b/2),
		vertex(x+l/2,y+h/2,z-b/2),
		vertex(x+l/2,y-h/2,z-b/2),
		vertex(x+l/2,y-h/2,z+b/2)
	};

	vertex face4_vertices[] = {
		vertex(x-l/2,y+h/2,z+b/2),
		vertex(x-l/2,y-h/2,z+b/2),
		vertex(x-l/2,y-h/2,z-b/2),
		vertex(x-l/2,y+h/2,z-b/2)
	};

	vertex face5_vertices[] = {
		vertex(x+l/2,y+h/2,z+b/2),
		vertex(x+l/2,y+h/2,z-b/2),
		vertex(x-l/2,y+h/2,z-b/2),
		vertex(x-l/2,y+h/2,z+b/2)
	};

	vertex face6_vertices[] = {
		vertex(x+l/2,y-h/2,z+b/2),
		vertex(x+l/2,y-h/2,z-b/2),
		vertex(x-l/2,y-h/2,z-b/2),
		vertex(x-l/2,y-h/2,z+b/2)
	};

	polygon face1 = polygon(x,y,z,x_distance,y_distance, z_distance,4, face1_vertices, &color);
	polygon face2 = polygon(x,y,z,x_distance,y_distance, z_distance,4, face2_vertices, &color);
	polygon face3 = polygon(x,y,z,x_distance,y_distance, z_distance,4, face3_vertices, &color);
	polygon face4 = polygon(x,y,z,x_distance,y_distance, z_distance,4, face4_vertices, &color);
	polygon face5 = polygon(x,y,z,x_distance,y_distance, z_distance,4, face5_vertices, &color);
	polygon face6 = polygon(x,y,z,x_distance,y_distance, z_distance,4, face6_vertices, &color);

	face1.rotate(1,0,0,angle_x);
	face1.rotate(0,1,0,angle_y);
	face1.rotate(0,0,1,angle_z);
	face2.rotate(1,0,0,angle_x);
	face2.rotate(0,1,0,angle_y);
	face2.rotate(0,0,1,angle_z);
	face3.rotate(1,0,0,angle_x);
	face3.rotate(0,1,0,angle_y);
	face3.rotate(0,0,1,angle_z);
	face4.rotate(1,0,0,angle_x);
	face4.rotate(0,1,0,angle_y);
	face4.rotate(0,0,1,angle_z);
	face5.rotate(1,0,0,angle_x);
	face5.rotate(0,1,0,angle_y);
	face5.rotate(0,0,1,angle_z);
	face6.rotate(1,0,0,angle_x);
	face6.rotate(0,1,0,angle_y);
	face6.rotate(0,0,1,angle_z);

	face1.draw();
	face2.draw();
	face3.draw();
	face4.draw();
	face5.draw();
	face6.draw();


}

/* This function is used to create the various 3D shapes in the scene.
 * The position of the various objects within the scene are fixed.
 * */
void default_scene(void)
{

	float x_plane, y_plane, z_plane;
	float x_cube, y_cube, z_cube;
	float x_composite, y_composite, z_composite;
	x_composite = 0;
	y_composite = 0;
	z_composite = 0;

//	draw_plane(x_composite,y_composite,z_composite,3,3,0,0,-10);
	draw_cuboid(x_composite,y_composite,z_composite,1.5,1.5,1.5,0,0,-10);

	return ;
}

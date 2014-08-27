/*
 * scene.cpp
 *	Contains code for generating plane and Cuboid.
 *	Note that the figures are only generated and not
 *	drawn. The figures are drawn in the display callback function
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */
#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/polygon.h"
#include "../include/transformations.h"

/* Generates a plane using polygon class.
 * x: X coordinate of center of plane
 * y: Y coordinate of center of plane
 * z: Z coordinate of center of plane
 * l: Length of Plane
 * b: Width of plane
 * x_distance: X-coordinate Initial position of plane after creation w.r.t position of camera
 * y_distance: Y-coordinate Initial position of plane after creation w.r.t position of camera
 * z_distance: Z-coordinate Initial position of plane after creation w.r.t position of camera
 * */
polygon generate_plane(float x, float y, float z, float l, float b, float x_distance, float y_distance, float z_distance)
{
	/* Color for plane*/
	RGB_value color = color_comp(0.5,0.5,0.23);

	/* Vertices representing plane*/
	vertex plane_vertices[] = {
		vertex(x+l/2,y+b/2,0),
		vertex(x+l/2,y-b/2,0),
		vertex(x-l/2,y-b/2,0),
		vertex(x-l/2,y+b/2,0)
	};

	/* Construction of instance of polygon class as plane*/
	polygon plane = polygon();

	/* Add info about the vertices about the corresponding face*/
	plane.add_face(4,plane_vertices,&color);

	/* Shift the plane to the specified distance*/
	plane.translate(x_distance, y_distance, z_distance);

	/* For Debugging. Prints information about the plane.*/
//	plane.debug();

	return plane;
}

/* Generates a plane using polygon class.
 * x: X coordinate of center of cuboid
 * y: Y coordinate of center of cuboid
 * z: Z coordinate of center of cuboid
 * l: Length of cuboid
 * b: Width of cuboid
 * x_distance: X-coordinate Initial position of cuboid after creation w.r.t position of camera
 * y_distance: Y-coordinate Initial position of cuboid after creation w.r.t position of camera
 * z_distance: Z-coordinate Initial position of cuboid after creation w.r.t position of camera
 * */
polygon generate_cuboid(float x, float y, float z, float l, float b, float h, float x_distance, float y_distance, float z_distance)
{
	/* Color for cuboid*/
	RGB_value color = color_comp(0.5,0.5,1);

	/* Vertex representing cuboid */
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

	/* Construction of instance of polygon class as plane */
	polygon cuboid = polygon();

	/* Add info about the vertices about the corresponding 6 faces*/
	cuboid.add_face(4, face1_vertices, &color);
	cuboid.add_face(4, face2_vertices, &color);
	cuboid.add_face(4, face3_vertices, &color);
	cuboid.add_face(4, face4_vertices, &color);
	cuboid.add_face(4, face5_vertices, &color);
	cuboid.add_face(4, face6_vertices, &color);

	/* Shift the cuboid to the specified distance*/
	cuboid.translate(x_distance,y_distance,z_distance);

	/* For Debugging. Prints information about the cuboid.*/
//	cuboid.debug();

	return cuboid;
}

/*
 * polygon.h
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include "../include/structs.h"
#include "../include/headers.h"
/* Defines class variables as well as functions
 * for polygon class used to denote 2D as well as 3D
 * objects
 * */
class polygon {

private:
	/* Number of faces of polygon*/
	int num_of_faces;

	/* Vector representing a set of set of vertices representing the corresponding faces
	 * Each element of face_set is a set of vertices representing a face of a figure (2D/3D)
	 * */
	std::vector<face_info *> face_set;

	/* Flag to determine if the polygon has been drawn or not (DEBUGGING)*/
	bool isDrawn;

	/* Coordinates of center of rotation*/
	float x_trans;
	float y_trans;
	float z_trans;

	/* For storing current angle orientation. (DEBUGGING)*/
	float theta_x;
	float theta_y;
	float theta_z;

	/* Private function that translates the center of rotation*/
	void translate_center(float a,float b, float c);

public:
	polygon(void);
	polygon(float x, float y, float z, float l, float b, float h, int num_vertices, vertex* vertex_array, RGB_value* color);
	face_info * get_face_set(int i);
	int get_num_faces(void);
	void add_face(int num_vertices, vertex* vertex_array, RGB_value* color);
	void set_rot_center(float x, float y, float z);
	void draw(void);
	void translate(float a,float b, float c);
	void scale(float a,float b, float c);
	void rotate(float x, float y, float z, float theta);
	void debug(void);
};

#endif /* POLYGON_H_ */

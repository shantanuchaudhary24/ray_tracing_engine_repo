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

	/* Properties of polygon*/
	float refractive_index;
	float specular_coeff;
	float specular_exp;
	float diffuse_coeff;

	/* Coordinates of center of rotation*/
	float x_trans;
	float y_trans;
	float z_trans;


public:
	polygon(void);
//	polygon(int num_vertices, vertex* vertex_array, RGB_value* color);
	void set_refractive_index(float value);
	void set_spec_coeff(float value);
	void set_spec_exp(float value);
	void set_diff_coeff(float value);
	float get_refractive_index();
	float get_spec_coeff();
	float get_spec_exp();
	float get_diff_coeff();
	face_info * get_face_set(int i);
	int get_num_faces(void);
	void add_face(int num_vertices, vertex* vertex_array, RGB_value* color);
	void add_face(face_info* face);
//	void set_rot_center(float x, float y, float z);
	void draw(bool isFill);
	void debug(void);
};

#endif /* POLYGON_H_ */

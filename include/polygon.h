/*
 * polygon.h
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include "../include/structs.h"

class polygon {

private:
	int num_of_faces;
	std::vector<face_info *> face_set;
	bool isDrawn;
	float x_trans;
	float y_trans;
	float z_trans;
	float theta_x;
	float theta_y;
	float theta_z;
	void translate_center(float a,float b, float c);

public:
	polygon(void);
	polygon(float x, float y, float z, float l, float b, float h, int num_vertices, vertex* vertex_array, RGB_value* color);
	int get_num_faces(void);
	void add_face(int num_vertices, vertex* vertex_array, RGB_value* color);
	void draw(void);
	void translate(float a,float b, float c);
	void scale(float a,float b, float c);
	void rotate(float x, float y, float z, float theta);
};

#endif /* POLYGON_H_ */

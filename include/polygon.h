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

public:
	polygon(void);
	void add_face(int num_vertices, vertex* vertex_array, RGB_value* color);
	void draw(void);
	void translate(float a,float b, float c);
	void scale(float a,float b, float c);
	void rotate(float x, float y, float z, float theta);
};

#endif /* POLYGON_H_ */

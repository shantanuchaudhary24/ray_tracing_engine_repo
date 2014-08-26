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
	void draw_polygon(void);
};

#endif /* POLYGON_H_ */

/*
 * clipping.h
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */

#ifndef CLIPPING_H_
#define CLIPPING_H_

float* plane_equation(face_info* face);
void polygonClipping(face_info* face);
float vector_length(vertex *pt1, vertex *pt2);
float dot_product(vertex *vector1, vertex *vector2);
float dot_product(vertex* p1,vertex* p2,vertex* p);
bool isOnPlane(vertex* p, face_info* face);
vertex* findIntersection(float* eq_plane,Ray* ray);
vertex* unitVector(vertex* point1,vertex* point2);
void unitVector(vertex* point);
float distanceFromPlane(float* plane_eq,vertex* point);
float* normalizePlane(float* plane_eq);

#endif /* CLIPPING_H_ */

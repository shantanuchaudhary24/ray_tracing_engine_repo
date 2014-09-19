/*
 * vectors.h
 *
 *  Created on: 18-Sep-2014
 *      Author: shantanu
 */

#ifndef VECTORS_H_
#define VECTORS_H_

float distancePoint(vertex* point1,vertex* point2);
float* plane_equation(face_info* face);
float vector_length(vertex *pt1, vertex *pt2);
float dot_product(vertex *vector1, vertex *vector2);
float dot_product(vertex* p1,vertex* p2,vertex* p);
float distanceFromPlane(float* plane_eq,vertex* point);
float* normalizePlane(float* plane_eq);
void crossproduct(vertex* u,vertex* v,vertex* temp);
bool isOnPlane(vertex* p, face_info* face);
bool isInsidePlane(float* eq_plane,vertex* point);
void unitVector(vertex* point);
vertex* unitVector(vertex* point1,vertex* point2);
vertex* findIntersection(float* eq_plane,Ray* ray);




#endif /* VECTORS_H_ */

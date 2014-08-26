/*
 * transformations.h
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_
#include "../include/structs.h"

vertex generic_transform(vertex point, float a, float b, float c, int option, float theta);
void myTranslatef( float x, float y, float z);
void myScalef(float sx, float sy, float sz);
void myRotatef(float theta,float px, float py, float pz);



#endif /* TRANSFORMATIONS_H_ */

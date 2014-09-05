/*
 * transformations.h
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */

#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

void perspective_transformation(float distFromViewingPlane);
void perspective_projection(float distFromViewingPlane);
void normalized_transformation(float width,float height,float near,float far,float distFromViewingPlane);
void myTranslatef( float x, float y, float z);
void myScalef(float sx, float sy, float sz);
void myRotatef(float theta,float px, float py, float pz);
#endif /* TRANSFORMATIONS_H_ */

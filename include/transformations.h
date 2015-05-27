/*
 * transformations.h
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */

#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_
void transformation(const float* mat,polygon* poly);
void perspective_transformation(float distFromViewingPlane);
void perspective_projection(float distFromViewingPlane);
void normalized_transformation(float width,float height,float near,float far,float distFromViewingPlane);
void myTranslatef( float x, float y, float z,polygon* poly);
void myScalef(float sx, float sy, float sz,polygon* poly);
void myRotatef(float theta,float px, float py, float pz,polygon* poly);
#endif /* TRANSFORMATIONS_H_ */

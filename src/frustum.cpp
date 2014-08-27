/*
 * frustum.cpp
 *
 *  Created on: Aug 27, 2014
 *      Author: Mukesh
 */
#include "../include/headers.h"

float* create_frustrum(float* eye, float* eyenormal, float d1, float d2,
		float width, float height)
{

	float* centre = (float*) malloc(3 * sizeof(float));
	centre[0] = eye[0] + d1 * eyenormal[0];
	centre[1] = eye[1] + d1 * eyenormal[1];
	centre[2] = eye[2] + d1 * eyenormal[2];

	float* frustrum = (float*) malloc(8 * 3 * sizeof(float));
	int i = 0;
	for (i = 0; i < 4; i++) {
		frustrum[3 * i] = centre[0];
		frustrum[3 * i + 1] = centre[1];
		frustrum[3 * i + 2] = centre[2];
	}

	frustrum[0] += width;		//first point
	frustrum[1] += height;

	frustrum[3 * 1 + 0] -= width;		//second point
	frustrum[3 * 1 + 1] += height;

	frustrum[3 * 2 + 0] -= width;		//third point
	frustrum[3 * 2 + 1] -= height;

	frustrum[3 * 3 + 0] += width;		//fourth point
	frustrum[3 * 3 + 1] -= height;

	//shift center to back plane
	centre[0] += (d2 - d1) * eyenormal[0];
	centre[1] += (d2 - d1) * eyenormal[1];
	centre[2] += (d2 - d1) * eyenormal[2];

	for (i = 4; i < 8; i++) {
		frustrum[3 * i] = centre[0];
		frustrum[3 * i + 1] = centre[1];
		frustrum[3 * i + 2] = centre[2];
	}

	float width2 = (d2 * width) / d1;
	float height2 = (d2 * height) / d1;
	frustrum[3 * 4 + 0] += width2;		//first point
	frustrum[3 * 4 + 1] += height2;

	frustrum[3 * 5 + 0] -= width2;		//second point
	frustrum[3 * 5 + 1] += height2;

	frustrum[3 * 6 + 0] -= width2;		//third point
	frustrum[3 * 6 + 1] -= height2;

	frustrum[3 * 7 + 0] += width2;		//fourth point
	frustrum[3 * 7 + 1] -= height2;

//	for (i = 0; i < 8; i++)
//		printf("%f %f %f\n", frustrum[3 * i], frustrum[3 * i + 1],
//				frustrum[3 * i + 2]);
	return frustrum;
}




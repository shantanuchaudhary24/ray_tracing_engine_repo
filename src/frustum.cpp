/*
 * frustum.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */

#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/structs.h"
#include "../include/frustum.h"

float* create_frustrum(float* eye,float* eyenormal,float* eyeup,float* eyeside,float d1,float d2,float width,float height){

	float* centre = (float*)malloc(3*sizeof(float));
		centre[0]= eye[0]+d1*eyenormal[0];
		centre[1]= eye[1]+d1*eyenormal[1];
		centre[2]= eye[2]+d1*eyenormal[2];

	float* frustrum = (float*)malloc(8*3*sizeof(float));

	//float diagonal=sqrt(width*width+height*height);
	float S[3]={height*eyeup[0]+width*eyeside[0],height*eyeup[1]+width*eyeside[1],height*eyeup[2]+width*eyeside[2]};
	float Sneg[3]={height*eyeup[0]-width*eyeside[0],height*eyeup[1]-width*eyeside[1],height*eyeup[2]-width*eyeside[2]};

	frustrum[0]=centre[0]+S[0];		//first point
	frustrum[1]=centre[1]+S[1];
	frustrum[2]=centre[2]+S[2];

	frustrum[3*1+0]=centre[0]+Sneg[0];		//second point
	frustrum[3*1+1]=centre[1]+Sneg[1];
	frustrum[3*1+2]=centre[2]+Sneg[2];

	frustrum[3*2+0]=centre[0]-S[0];		//third point
	frustrum[3*2+1]=centre[1]-S[1];
	frustrum[3*2+2]=centre[2]-S[2];

	frustrum[3*3+0]=centre[0]-Sneg[0];		//fourth point
	frustrum[3*3+1]=centre[1]-Sneg[1];
	frustrum[3*3+2]=centre[2]-Sneg[2];

	//shift centre to back plane
	centre[0]=eye[0]+d2*eyenormal[0];
	centre[1]=eye[1]+d2*eyenormal[1];
	centre[2]=eye[2]+d2*eyenormal[2];


	float width2=(d2*width)/d1;
	float height2=(d2*height)/d1;

	float S2[3]={height2*eyeup[0]+width2*eyeside[0],height2*eyeup[1]+width2*eyeside[1],height2*eyeup[2]+width2*eyeside[2]};
	float Sneg2[3]={height2*eyeup[0]-width2*eyeside[0],height2*eyeup[1]-width2*eyeside[1],height2*eyeup[2]-width2*eyeside[2]};

	frustrum[3*4+0]=centre[0]+S2[0];		//first point
	frustrum[3*4+1]=centre[1]+S2[1];
	frustrum[3*4+2]=centre[2]+S2[2];

	frustrum[3*5+0]=centre[0]+Sneg2[0];		//second point
	frustrum[3*5+1]=centre[1]+Sneg2[1];
	frustrum[3*5+2]=centre[2]+Sneg2[2];

	frustrum[3*6+0]=centre[0]-S2[0];		//third point
	frustrum[3*6+1]=centre[1]-S2[1];
	frustrum[3*6+2]=centre[2]-S2[2];

	frustrum[3*7+0]=centre[0]-Sneg2[0];		//fourth point
	frustrum[3*7+1]=centre[1]-Sneg2[1];
	frustrum[3*7+2]=centre[2]-Sneg2[2];

	//for(int i=0;i<8;i++)
		//printf("frustrum point %d = %f %f %f\n",i+1,frustrum[3*i],frustrum[3*i+1],frustrum[3*i+2]);
	return frustrum;
}




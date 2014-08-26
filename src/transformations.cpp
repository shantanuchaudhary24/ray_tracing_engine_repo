/*
 * transformations.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/transformations.h"
#include "../include/structs.h"

vertex generic_transform(vertex point, float a, float b, float c, int option, float theta)
{
	vertex output_pt = vertex_pt(0,0,0);
	float final_pt[]={0,0,0,1};
	const float init_point[] = {point.x_pos,point.y_pos, point.z_pos,1};
	const float translation_matrix[4][4] = {
			(1,0,0,0),
			(0,1,0,0),
			(0,0,1,0),
			(a,b,c,1)
	};

	const float scaling_matrix[4][4] = {
			(a,0,0,0),
			(0,b,0,0),
			(0,0,c,0),
			(0,0,0,1)
	};

	switch (option){
		case 1:
			output_pt.x_pos = init_point[0]+a;
			output_pt.y_pos= init_point[1]+b;
			output_pt.z_pos = init_point[2]+c;
			break;
		case 2:
			output_pt.x_pos = init_point[0]*a;
			output_pt.y_pos = init_point[1]*b;
			output_pt.z_pos = init_point[2]*c;
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;

	}
	return output_pt;
}
//	const float rotation_matrix[][] = {
//
//
//
//	}
//
//	int i,j=0;
//	for(i=0;i<4;i++)
//	{
//		for(j=0;j<4;j++)
//		{
//			final_pt[i] += init_point[j]*transform_matrix[i][j];
//		}
//	}


void myTranslatef( float x, float y, float z){
	    const float mat[] = {1.0,0,0,0,0,1.0,0,0,0,0,1.0,0,x,y,z,1.0};
	    glMultMatrixf(&mat[0]);
	    return ;
	};

void myScalef(float sx, float sy, float sz){
    const float mat[] = {sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1.0};
    glMultMatrixf(&mat[0]);
    return ;
};

void myRotatef(float theta,float px, float py, float pz){
    theta *= M_PI/180;
    float m[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    float l = sqrt(px*px + py*py + pz*pz);
    float cosa = cos(theta);
    float onec = 1-cosa;
    float sina = sin(theta);
    float ux = px/l;
    float uy = py/l;
    float uz = pz/l;
    m[0] = ux*ux*onec + cosa;
    m[4] = ux*uy*onec - uz*sina;
    m[8] = ux*uz*onec + uy*sina;
    m[1] = ux*uy*onec + uz*sina;
    m[5] = uy*uy*onec + cosa;
    m[9] = uy*uz*onec - ux*sina;
    m[2] = ux*uz*onec - uy*sina;
    m[6] = uz*uy*onec + ux*sina;
    m[10] = uz*uz*onec + cosa;
    const float mat[] = {m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]};
    glMultMatrixf(&mat[0]);
    return ;
};





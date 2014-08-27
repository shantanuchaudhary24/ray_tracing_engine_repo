/*
 * transformations.cpp
 * Contains code for transformation operations on vertices
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/transformations.h"
#include "../include/structs.h"
//TODO
// WCS to VCS pending

/* Translates the point (point) by the specified points (a,b,c)
 * corresponding to three coordinate axes
 * */
vertex translate_transform(vertex point, float a, float b, float c)
{
	return vertex_pt(point.x_pos+a, point.y_pos+b, point.z_pos+c);
}

/* Scales the point (point) by the specified points (a,b,c) corresponding
 * to three coordinate axes
 * */
vertex scale_transform(vertex point, float a, float b, float c)
{
	return vertex_pt(point.x_pos*a, point.y_pos*b, point.z_pos*c);
}

/* Apply rotational transformation on point
 * point: Input point to apply transformation on
 * a: Transformation w.r.t X
 * b: Transformation w.r.t Y
 * c: Transformation w.r.t Z
 * theta: Angle by which we need to rotate
 * */
vertex rotate_transform(vertex point, float a, float b, float c, float theta)
{
	theta *= M_PI/180;
	float pt_matrix[] = {point.x_pos, point.y_pos, point.z_pos, 1};
	float out_matrix[] = {0,0,0,0};
	float m[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	float l = sqrt(a*a + b*b + c*c);
	float cosa = cos(theta);
	float onec = 1-cosa;
	float sina = sin(theta);
	float ux = a/l;
	float uy = b/l;
	float uz = c/l;
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
	int i=0;
	for(i=0;i<4;i++)
	{
		out_matrix[i]=pt_matrix[0]*mat[i] + pt_matrix[1]*mat[(i+4)] + pt_matrix[2]*mat[i+8] + pt_matrix[3]*mat[i+12];
	}
	return vertex(out_matrix[0], out_matrix[1], out_matrix[2]);
}

/* Auxiliary translate function using openGL transformation operation
 * */
void myTranslatef( float x, float y, float z){
	    const float mat[] = {1.0,0,0,0,0,1.0,0,0,0,0,1.0,0,x,y,z,1.0};
	    glMultMatrixf(&mat[0]);
	    return ;
	};

/* Auxiliary scale function using openGL transformation operation
 * */
void myScalef(float sx, float sy, float sz){
    const float mat[] = {sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1.0};
    glMultMatrixf(&mat[0]);
    return ;
};

/* Auxiliary rotation function using openGL transformation operation
 * */
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


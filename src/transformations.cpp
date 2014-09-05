/*
 * transformations.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */
#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/structs.h"
#include "../include/polygon.h"
#include "../include/transformations.h"
#include "../include/matrix.h"


extern std::vector<polygon*> sceneData;
extern polygon clippingArea;
extern float* viewingCordMatrix;
extern float* inverseviewingCordMatrix;

void transformation(const float* mat){

	for(int i=0;i<sceneData.size();i++)
	{
		polygon* poly=sceneData.at(i);
		for(int j=0;j<poly->get_num_faces();j++)
		{
			face_info* faces=poly->get_face_set(j);
			vertex* verts=faces->vertex_set;
			for(int k=0;k<faces->number_of_vertices;k++)
			{
				matrix_mult(verts+k,mat);
			}
		}
	}
}

void transformationsaveZ(const float* mat){

	for(int i=0;i<sceneData.size();i++)
		{
			polygon* poly=sceneData.at(i);
			for(int j=0;j<poly->get_num_faces();j++)
			{
				face_info* faces=poly->get_face_set(j);
				vertex* verts=faces->vertex_set;
				for(int k=0;k<faces->number_of_vertices;k++)
				{
					matrix_multsaveZ(verts+k,mat);
				}
			}
		}
}

void transformationOnFrustrum(const float* mat){

		for(int j=0;j<clippingArea.get_num_faces();j++)
		{
			face_info* faces=clippingArea.get_face_set(j);
			vertex* verts=faces->vertex_set;
			for(int k=0;k<faces->number_of_vertices;k++)
			{
				matrix_mult(verts+k,mat);
			}
		}
}
void transformationOnFrustrumsaveZ(const float* mat){

		for(int j=0;j<clippingArea.get_num_faces();j++)
		{
			face_info* faces=clippingArea.get_face_set(j);
			vertex* verts=faces->vertex_set;
			for(int k=0;k<faces->number_of_vertices;k++)
			{
				matrix_multsaveZ(verts+k,mat);
			}
		}
}

void perspective_transformation(float distFromViewingPlane){
	//TODO
	const float mat[]={1,0,0,0,0,1,0,0,0,0,1,1/distFromViewingPlane,0,0,0,1};

	transformation(viewingCordMatrix);
	transformationsaveZ(&mat[0]);
	transformation(inverseviewingCordMatrix);

	transformationOnFrustrum(viewingCordMatrix);
	transformationOnFrustrumsaveZ(&mat[0]);
	transformationOnFrustrum(inverseviewingCordMatrix);
}
void perspective_projection(float distFromViewingPlane){
	//TODO
	const float mat[]={1,0,0,0,0,1,0,0,0,0,0,1/distFromViewingPlane,0,0,0,1};
	transformation(viewingCordMatrix);
	transformation(&mat[0]);
	transformation(inverseviewingCordMatrix);

	transformationOnFrustrum(viewingCordMatrix);
	transformationOnFrustrum(&mat[0]);
	transformationOnFrustrum(inverseviewingCordMatrix);

}

void normalized_transformation(float width,float height,float near,float far,float distFromViewingPlane){

	perspective_transformation(distFromViewingPlane);

	const float mat[]={1/width,0,0,0,0,1/height,0,0,0,0,2/(far-near),0,0,0,-distFromViewingPlane,1};
	transformation(viewingCordMatrix);
	transformation(&mat[0]);
	transformation(inverseviewingCordMatrix);

	transformationOnFrustrum(viewingCordMatrix);
	transformationOnFrustrum(&mat[0]);
	transformationOnFrustrum(inverseviewingCordMatrix);

}

void myTranslatef( float x, float y, float z){
    const float mat[] = {1.0,0,0,0,0,1.0,0,0,0,0,1.0,0,x,y,z,1.0};
    transformation(viewingCordMatrix);
    transformation(&mat[0]);
    transformation(inverseviewingCordMatrix);
    //glMultMatrixf(&mat[0]);
    return ;
}

void myScalef(float sx, float sy, float sz){
    const float mat[] = {sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1.0};
    transformation(viewingCordMatrix);
    transformation(&mat[0]);
    transformation(inverseviewingCordMatrix);
    //glMultMatrixf(&mat[0]);
    return ;
}

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
    transformation(viewingCordMatrix);
    transformation(&mat[0]);
    transformation(inverseviewingCordMatrix);
    //glMultMatrixf(&mat[0]);
    return ;
}





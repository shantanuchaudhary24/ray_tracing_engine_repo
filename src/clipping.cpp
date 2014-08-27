/*
 * clipping.cpp
 *
 *  Created on: Aug 27, 2014
 *      Author: Mukesh
 */
#include "../include/headers.h"
#include "../include/structs.h"
extern std::vector<float*> clipping_plane_eq;


float* plane_equation(face_info* face){
	vertex* verts = face->vertex_set;
	int num = face->number_of_vertices;

	float u[3];
	float v[3];

		u[0]=verts[2].x_pos-verts[0].x_pos;
		u[1]=verts[2].y_pos-verts[0].y_pos;
		u[2]=verts[2].z_pos-verts[0].z_pos;
		v[0]=verts[2].x_pos-verts[1].x_pos;
		v[1]=verts[2].y_pos-verts[1].y_pos;
		v[2]=verts[2].z_pos-verts[1].z_pos;

	float* eq = (float*)malloc(4*sizeof(float));
	eq[0]=u[1]*v[2]-u[2]*v[1];
	eq[1]=u[2]*v[0]-u[0]*v[2];
	eq[2]=u[0]*v[1]-u[1]*v[0];
	//TODO
	eq[3]=-eq[0]*verts[0].x_pos-eq[1]*verts[0].y_pos-eq[2]*verts[0].z_pos;

	return eq;
}

bool isInsidePlane(float* eq_plane,vertex point){

		if((eq_plane[0]*point.x_pos+eq_plane[1]*point.y_pos+eq_plane[2]*point.z_pos+eq_plane[3])>=0)
			return true;
		else
			return false;
}

vertex findIntersection(float* eq_plane,vertex point1,vertex point2){

	float normalize=sqrtf((point1.x_pos-point2.x_pos)*(point1.x_pos-point2.x_pos)+(point1.y_pos-point2.y_pos)*(point1.y_pos-point2.y_pos)+(point1.z_pos-point2.z_pos)*(point1.z_pos-point2.z_pos));
	float unitvect[] ={(point1.x_pos-point2.x_pos)/normalize,(point1.y_pos-point2.y_pos)/normalize,(point1.z_pos-point2.z_pos)/normalize};

	float a= eq_plane[0]*unitvect[0]+eq_plane[1]*unitvect[1]+eq_plane[2]*unitvect[2];
	float b= eq_plane[0]*point1.x_pos+eq_plane[1]*point1.y_pos+eq_plane[2]*point1.z_pos+eq_plane[3];

	if(abs(a)>0.00001)
	{
		//float intersectionPoint[3]={point1[0]-(b*unitvect[0])/a,point1[1]-(b*unitvect[1])/a,point1[2]-(b*unitvect[2])/a};
		vertex intersectionPoint ;//= (vertex *)malloc(sizeof(vertex));
		//for(int i=0;i<3;i++) intersectionPoint[i] = point1[i]-(b*unitvect[i])/a;
		intersectionPoint.x_pos = point1.x_pos-(b*unitvect[0])/a;
		intersectionPoint.y_pos = point1.y_pos-(b*unitvect[1])/a;
		intersectionPoint.z_pos = point1.z_pos-(b*unitvect[2])/a;
//		printf("intersection point %f %f %f \n",intersectionPoint[0],intersectionPoint[1],intersectionPoint[2]);
		return intersectionPoint;
	}
	else
	{
		vertex intersectionPoint ;//= (vertex *)malloc(sizeof(vertex));
//		for(int i=0;i<3;i++)	intersectionPoint[i]=point2[i];
		intersectionPoint.x_pos=point2.x_pos;
		intersectionPoint.y_pos=point2.y_pos;
		intersectionPoint.z_pos=point2.z_pos;
//		printf("intersection askdaskdn nan point %f %f %f \n",intersectionPoint[0],intersectionPoint[1],intersectionPoint[2]);
		return intersectionPoint;
	}
}
void polygonClipping(face_info* polygon){
	int i=0;

	vertex* verts=polygon->vertex_set;
	int count=polygon->number_of_vertices;
	std::vector<vertex> CvTable;
	std::vector<vertex> CvTabletemp;

	for(i=0;i<count;i++){
//		float* point=verts+3*i;
		CvTable.push_back(verts[i]);
	}


	for(i=0;i<clipping_plane_eq.size();i++)
	{
		float* eq_plane=clipping_plane_eq.at(i);
		printf("equation of plane %f %f %f %f \n",eq_plane[0],eq_plane[1],eq_plane[2],eq_plane[3]);

		int j;
		for(j=0;j<CvTable.size();j++)
		{
			//printf("j= %d \n",j);
			vertex point1=CvTable.at(j);
			//printf("%f %f %f\n",point1[0],point1[1],point1[2]);
			vertex point2=CvTable.at((j+1)%CvTable.size());
			//printf("%f %f %f\n",point2[0],point2[1],point2[2]);
			int k;
			if(isInsidePlane(eq_plane,point1))								//if v1 is inside
			{
				if(isInsidePlane(eq_plane,point2))		//if v2 is inside
				{
					printf("1\n");
					CvTabletemp.push_back(point2);
				}
				else															//if v2 is outside
				{
					printf("2\n");
					//find intersection point and put in cvtable
					CvTabletemp.push_back(findIntersection(eq_plane,point1,point2));
				}
			}
			else																//if v1 is outside
			{
				if(isInsidePlane(eq_plane,point2))			//if v2 is inside
				{
					printf("3\n");
					//find intersection point and put in cvtable
					CvTabletemp.push_back(findIntersection(eq_plane,point1,point2));
					CvTabletemp.push_back(point2);
				}
				else
				{
					printf("4\n");
				}
			}
		}

		CvTable.clear();
		int k;
		vertex temp;
		for(k=0;k<CvTabletemp.size();k++){
//			printf("polygon points %f %f %f \n",CvTabletemp.at(k)[0],CvTabletemp.at(k)[1],CvTabletemp.at(k)[2]);
			temp = CvTabletemp.at(k);
			CvTable.push_back(temp);
		}
		printf("\n\n\n");
		CvTabletemp.clear();
	}


	vertex* newverts= (vertex*)malloc(CvTable.size()*sizeof(vertex));
	for(i=0;i<CvTable.size();i++){
		newverts[i]=CvTable.at(i);
	}
	polygon->vertex_set=newverts;
	polygon->number_of_vertices=CvTable.size();
}


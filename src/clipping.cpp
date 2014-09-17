/*
 * clipping.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */

#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/structs.h"
#include "../include/polygon.h"
#include "../include/clipping.h"

extern std::vector<float*> clipping_plane_eq;

float* plane_equation(face_info* face){
	vertex* verts = face->vertex_set;
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
	eq[3]=-eq[0]*verts[0].x_pos-eq[1]*verts[0].y_pos-eq[2]*verts[0].z_pos;

	normalizePlane(eq);
	return eq;
}
float vector_length(vertex *pt1, vertex *pt2)
{
	return sqrt(pow((pt1->x_pos - pt2->x_pos),2)+pow((pt1->y_pos - pt2->y_pos),2)+pow((pt1->z_pos - pt2->z_pos),2));
}

float dot_product(vertex *vector1, vertex *vector2)
{
	return vector1->x_pos*vector2->x_pos + vector1->y_pos*vector2->y_pos + vector1->z_pos*vector2->z_pos;
}

float dot_product(vertex* p1,vertex* p2,vertex* p){
	return (p2->x_pos-p1->x_pos)*(p->x_pos-p2->x_pos)+(p2->y_pos-p1->y_pos)*(p->y_pos-p2->y_pos)+(p2->z_pos-p1->z_pos)*(p->z_pos-p2->z_pos);
}

float distanceFromPlane(float* plane_eq,vertex* point){
	return plane_eq[0]*point->x_pos+plane_eq[1]*point->y_pos+plane_eq[2]*point->z_pos+plane_eq[3];
}

float* normalizePlane(float* plane_eq){
	float normalize= sqrtf((plane_eq[0])*(plane_eq[0])+(plane_eq[1])*(plane_eq[1])+(plane_eq[2])*(plane_eq[2]));
	plane_eq[0]=plane_eq[0]/normalize;
	plane_eq[1]=plane_eq[1]/normalize;
	plane_eq[2]=plane_eq[2]/normalize;
	plane_eq[3]=plane_eq[3]/normalize;
	return plane_eq;
}

void crossproduct(vertex* u,vertex* v,vertex* temp){

	temp->x_pos=u->y_pos*v->z_pos-u->z_pos*v->y_pos;
	temp->y_pos=u->z_pos*v->x_pos-u->x_pos*v->z_pos;
	temp->z_pos=u->x_pos*v->y_pos-u->y_pos*v->x_pos;
}

bool isOnPlane(vertex* p, face_info* face){

	vertex temp=vertex(0,0,0);
	for(int i=0;i<face->number_of_vertices;i++){
		vertex* p1 = &face->vertex_set[i];
		vertex* p2 = &face->vertex_set[(i+1)%face->number_of_vertices];

		vertex* u=unitVector(p,p1);
		vertex* v=unitVector(p,p2);
		if(i==0)
			crossproduct(u,v,&temp);
		else
		{
			vertex temp2=vertex(0,0,0);
			crossproduct(u,v,&temp2);
			if(dot_product(&temp,&temp2)<0)
				return false;
		}
	}
	return true;
}

bool isInsidePlane(float* eq_plane,vertex* point){

		if((eq_plane[0]*point->x_pos+eq_plane[1]*point->y_pos+eq_plane[2]*point->z_pos+eq_plane[3])>=0)
			return true;
		else
			return false;
}

void unitVector(vertex* point){
	float normalize= sqrtf((point->x_pos)*(point->x_pos)+(point->y_pos)*(point->y_pos)+(point->z_pos)*(point->z_pos));
	point->x_pos=(point->x_pos)/normalize;
	point->y_pos=(point->y_pos)/normalize;
	point->z_pos=(point->z_pos)/normalize;
}

vertex* unitVector(vertex* point1,vertex* point2){
	float normalize=sqrtf((point1->x_pos-point2->x_pos)*(point1->x_pos-point2->x_pos)+(point1->y_pos-point2->y_pos)*(point1->y_pos-point2->y_pos)+(point1->z_pos-point2->z_pos)*(point1->z_pos-point2->z_pos));
	vertex* unitvect=(vertex*)malloc(sizeof(vertex));
	unitvect->x_pos=(point2->x_pos-point1->x_pos)/normalize;
	unitvect->y_pos=(point2->y_pos-point1->y_pos)/normalize;
	unitvect->z_pos=(point2->z_pos-point1->z_pos)/normalize;
	return unitvect;
}
vertex* findIntersection(float* eq_plane,Ray* ray){

	vertex* unitvect =ray->direction;
	vertex* point1=ray->startPoint;
	float a= eq_plane[0]*unitvect->x_pos+eq_plane[1]*unitvect->y_pos+eq_plane[2]*unitvect->z_pos;
	float b= eq_plane[0]*point1->x_pos+eq_plane[1]*point1->y_pos+eq_plane[2]*point1->z_pos+eq_plane[3];

	float t=-b/a;
	if(t>0.000001)
	{
		vertex* intersectionPoint = (vertex*)malloc(sizeof(vertex));
		intersectionPoint->x_pos = point1->x_pos+t*unitvect->x_pos;
		intersectionPoint->y_pos = point1->y_pos+t*unitvect->y_pos;
		intersectionPoint->z_pos = point1->z_pos+t*unitvect->z_pos;
		//printf("intersection point %f %f %f \n",intersectionPoint->x_pos,intersectionPoint->y_pos,intersectionPoint->z_pos);
		return intersectionPoint;
	}
	else
		return NULL;
}
void polygonClipping(face_info* face){
	int i=0;

	vertex* verts=face->vertex_set;
	int count=face->number_of_vertices;
	std::vector<vertex*> CvTable;
	std::vector<vertex*> CvTabletemp;

	for(i=0;i<count;i++){
		vertex* point=verts+i;
		CvTable.push_back(point);
	}


	for(i=0;i<clipping_plane_eq.size();i++)
	{
		float* eq_plane=clipping_plane_eq.at(i);
		//printf("equation of plane %d  %f %f %f %f \n",i,eq_plane[0],eq_plane[1],eq_plane[2],eq_plane[3]);

		int j;
		for(j=0;j<CvTable.size();j++)
		{
			vertex* point1=CvTable.at(j);
			vertex* point2=CvTable.at((j+1)%CvTable.size());
			vertex* unitvect=unitVector(point1,point2);
			Ray* ray=(Ray*)malloc(sizeof(Ray));
			ray->direction=unitvect;
			ray->startPoint=point1;
			//printf("point1=%f %f %f\n",point1->x_pos,point1->y_pos,point1->z_pos);
			//printf("point2=%f %f %f\n",point2->x_pos,point2->y_pos,point2->z_pos);
			int k;
			if(isInsidePlane(eq_plane,point1))								//if v1 is inside
			{
				if(isInsidePlane(eq_plane,point2))		//if v2 is inside
				{
					//printf("1\n");
					CvTabletemp.push_back(point2);
				}
				else															//if v2 is outside
				{
					//find intersection point and put in cvtable
					vertex* temp=findIntersection(eq_plane,ray);
					if(temp!=NULL)
					CvTabletemp.push_back(temp);
				}
			}
			else																//if v1 is outside
			{
				if(isInsidePlane(eq_plane,point2))			//if v2 is inside
				{
					//find intersection point and put in cvtable
					vertex* temp=findIntersection(eq_plane,ray);
					if(temp!=NULL)
						CvTabletemp.push_back(temp);
					CvTabletemp.push_back(point2);
				}
			}
		}

		CvTable.clear();
		int k;
		for(k=0;k<CvTabletemp.size();k++){
			CvTable.push_back(CvTabletemp.at(k));
		}
		CvTabletemp.clear();
	}


	vertex* newverts= (vertex*)malloc(CvTable.size()*sizeof(vertex));
	for(i=0;i<CvTable.size();i++){
		newverts[i]=CvTable.at(i)[0];
	}

	face->vertex_set=newverts;
	face->number_of_vertices=CvTable.size();
}


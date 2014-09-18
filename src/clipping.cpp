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
#include "../include/vectors.h"

extern std::vector<float*> clipping_plane_eq;

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


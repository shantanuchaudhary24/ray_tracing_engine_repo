/*
 * polygon.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/structs.h"
#include "../include/polygon.h"
#include "../include/transformations.h"


	polygon::polygon(void){
		num_of_faces = 0;
	}

	void polygon::add_face(int num_vertices, vertex* vertex_array, RGB_value* color){
		num_of_faces++;
		face_info* vector_obj = (face_info*)malloc(sizeof(face_info));
		vector_obj->face_color=(RGB_value *)malloc(sizeof(RGB_value));
		vector_obj->vertex_set=(vertex *)malloc(num_vertices*sizeof(vertex));
		vector_obj->number_of_vertices =num_vertices;
		memcpy(vector_obj->face_color, color,sizeof(RGB_value));
		memcpy(vector_obj->vertex_set, vertex_array, num_vertices*sizeof(vertex));
		face_set.push_back(vector_obj);


	}

	void polygon::draw(void){

	int i,j;
#ifndef DEBUG
		for (i=0;i<face_set.size();i++)
		{
			glColor3f(face_set[i]->face_color->R_value, face_set[i]->face_color->G_value, face_set[i]->face_color->B_value);
			glBegin(GL_POLYGON);
			for(j=0;j<face_set[i]->number_of_vertices;j++)
			{
				glVertex3f(face_set[i]->vertex_set[j].x_pos, face_set[i]->vertex_set[j].y_pos, face_set[i]->vertex_set[j].z_pos);
			}
			glEnd();
		}
	}
#endif
#ifdef DEBUG
		for (i=0;i<face_set.size();i++)
		{
			for(j=0;j<face_set[i]->number_of_vertices;j++)
			{
				std::cout << "Vertex " << j << " coordinates:\n";
				std::cout << "( " ;
				std::cout << face_set[i]->vertex_set[j].x_pos << ", ";
				std::cout << face_set[i]->vertex_set[j].y_pos << ", ";
				std::cout << face_set[i]->vertex_set[j].z_pos << " ";
				std::cout << ")\n" ;
			}
		}
		exit(0);
	}
#endif

	void polygon::translate(float a,float b, float c)
	{
		int i,j;
		vertex output_pt = vertex_pt();
		for (i=0;i<face_set.size();i++)
		{
			for(j=0;j<face_set[i]->number_of_vertices;j++)
			{
				output_pt = generic_transform(face_set[i]->vertex_set[j], a, b, c, 1, 0);
				face_set[i]->vertex_set[j].x_pos = output_pt.x_pos;
				face_set[i]->vertex_set[j].y_pos = output_pt.y_pos;
				face_set[i]->vertex_set[j].z_pos = output_pt.z_pos;
			}
		}
	}

	void polygon::scale(float a,float b, float c)
	{
		int i,j;
		vertex output_pt = vertex_pt();
		for (i=0;i<face_set.size();i++)
		{
			for(j=0;j<face_set[i]->number_of_vertices;j++)
			{
				output_pt = generic_transform(face_set[i]->vertex_set[j], a, b, c, 2, 0);
				face_set[i]->vertex_set[j].x_pos = output_pt.x_pos;
				face_set[i]->vertex_set[j].y_pos = output_pt.y_pos;
				face_set[i]->vertex_set[j].z_pos = output_pt.z_pos;
			}
		}
	}

//	void polygon::translate()



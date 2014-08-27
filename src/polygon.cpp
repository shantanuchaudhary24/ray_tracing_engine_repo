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


	polygon::polygon(void)
	{
		num_of_faces = 0;
		isDrawn = false;
		x_trans = 0;
		y_trans = 0;
		z_trans = 0;
		theta_x = 0;
		theta_y = 0;
		theta_z = 0;

	}

	polygon::polygon(float x, float y, float z, float cx, float cy, float cz, int num_vertices, vertex* vertex_array, RGB_value* color)
		{
			num_of_faces = 1;
			isDrawn = false;
			x_trans = x;
			y_trans = y;
			z_trans = z;
			theta_x = 0;
			theta_y = 0;
			theta_z = 0;
			num_of_faces++;
			face_info* vector_obj = (face_info*)malloc(sizeof(face_info));
			vector_obj->face_color=(RGB_value *)malloc(sizeof(RGB_value));
			vector_obj->vertex_set=(vertex *)malloc(num_vertices*sizeof(vertex));
			vector_obj->number_of_vertices =num_vertices;
			memcpy(vector_obj->face_color, color,sizeof(RGB_value));
			memcpy(vector_obj->vertex_set, vertex_array, num_vertices*sizeof(vertex));
			face_set.push_back(vector_obj);
			translate(cx,cy,cz);
		}

	int polygon::get_num_faces(void)
	{
		return num_of_faces;
	}

	void polygon::add_face(int num_vertices, vertex* vertex_array, RGB_value* color)
	{
		num_of_faces++;
		face_info* vector_obj = (face_info*)malloc(sizeof(face_info));
		vector_obj->face_color=(RGB_value *)malloc(sizeof(RGB_value));
		vector_obj->vertex_set=(vertex *)malloc(num_vertices*sizeof(vertex));
		vector_obj->number_of_vertices =num_vertices;
		memcpy(vector_obj->face_color, color,sizeof(RGB_value));
		memcpy(vector_obj->vertex_set, vertex_array, num_vertices*sizeof(vertex));
		face_set.push_back(vector_obj);
	}

	void polygon::draw(void)
	{

	int i,j;
#ifndef DEBUG
//	if(!isDrawn)
//	{
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
//	}
	}
#endif
#ifdef DEBUG
		for (i=0;i<face_set.size();i++)
		{
			std::cout << "Face :" << i+1 << "\n"  ;
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
		std::cout << x_trans << "\n";
		std::cout << y_trans << "\n";
		std::cout << z_trans << "\n";
		exit(0);
	}
#endif

	void polygon::translate(float a,float b, float c)
	{
		int i,j;
		x_trans += a;
		y_trans += b;
		z_trans += c;
		for (i=0;i<face_set.size();i++)
			for(j=0;j<face_set[i]->number_of_vertices;j++)
				face_set[i]->vertex_set[j] = translate_transform(face_set[i]->vertex_set[j], a, b, c);
	}

	void polygon::scale(float a,float b, float c)
	{
		int i,j;
		a = (a==0)?1:a;
		b = (b==0)?1:b;
		c = (c==0)?1:c;
		for (i=0;i<face_set.size();i++)
			for(j=0;j<face_set[i]->number_of_vertices;j++)
				face_set[i]->vertex_set[j] = scale_transform(face_set[i]->vertex_set[j], a, b, c);
	}

	void polygon::translate_center(float a,float b, float c)
	{
		int i,j;
		for (i=0;i<face_set.size();i++)
			for(j=0;j<face_set[i]->number_of_vertices;j++)
				face_set[i]->vertex_set[j] = translate_transform(face_set[i]->vertex_set[j], a, b, c);
	}

	void polygon::rotate(float a, float b, float c, float theta)
	{
		int i,j;
		vertex center = vertex(0,0,0);
		if(theta_x!=theta || theta_y!=theta || theta_z!=theta )
		{
//			translate(0,0,+7);
			translate_center(-x_trans,-y_trans,-z_trans);
			for (i=0;i<face_set.size();i++)
				for(j=0;j<face_set[i]->number_of_vertices;j++)
					face_set[i]->vertex_set[j] = rotate_transform(face_set[i]->vertex_set[j], a, b, c, theta);
//			center = rotate_transform(vertex(x_trans, y_trans, z_trans),a,b,c,theta);
//			x_trans = center.x_pos;
//			y_trans = center.y_pos;
//			z_trans = center.z_pos;
			translate_center(x_trans,y_trans,z_trans);
//			translate(0,0,-7);
		}
	}

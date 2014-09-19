/*
 * polygon.cpp
 * Polygon class code has been defined here.
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/structs.h"
#include "../include/polygon.h"

	/* Main constructor for class
	* */
	polygon::polygon(void)
	{
		this->num_of_faces 		= 0;
		this->isDrawn 			= false;
		this->refractive_index	= 1;
		this->specular_coeff	= 1;
		this->specular_exp		= 1;
		this->diffuse_coeff		= 1;
		this->x_trans			= 0;
		this->y_trans			= 0;
		this->z_trans			= 0;


	}

//	/* Secondary constructor for class
//	 * */
//	polygon::polygon( int num_vertices, vertex* vertex_array, RGB_value* color)
//	{
//		num_of_faces = 1;
//		isDrawn = false;
//		num_of_faces++;
//		face_info* vector_obj = (face_info*)malloc(sizeof(face_info));
//		vector_obj->face_color=(RGB_value *)malloc(sizeof(RGB_value));
//		vector_obj->vertex_set=(vertex *)malloc(num_vertices*sizeof(vertex));
//		vector_obj->number_of_vertices =num_vertices;
//		memcpy(vector_obj->face_color, color,sizeof(RGB_value));
//		memcpy(vector_obj->vertex_set, vertex_array, num_vertices*sizeof(vertex));
//		face_set.push_back(vector_obj);
//	}


	void polygon::set_refractive_index(float value)
	{
		this->refractive_index = value;
	}

	void polygon::set_spec_coeff(float value)
	{
		this->specular_coeff = value;
	}

	void polygon::set_spec_exp(float value)
	{
		this->specular_exp = value;
	}

	void polygon::set_diff_coeff(float value)
	{
		this->diffuse_coeff = value;
	}

	float polygon::get_refractive_index()
	{
		return this->refractive_index;
	}

	float polygon::get_spec_coeff()
	{
		return this->specular_coeff;
	}

	float polygon::get_spec_exp()
	{
		return this->specular_exp;
	}

	float polygon::get_diff_coeff()
	{
		return this->diffuse_coeff;
	}

	/* Returns the set of vertices corresponding to face
	 * */
	face_info* polygon::get_face_set(int i)
	{
		return face_set[i];
	}

	/* Returns the number of faces of the 3D object constructed using the class*/
	int polygon::get_num_faces(void)
	{
		return num_of_faces;
	}

	/* For inserting info about a face for a 3D object
	 * num_vertices	: Specifies the number of vertices on the face
	 * vertex_array	: Specifies the set of vertices constituting the face
	 * color		: Specifies the color of the face
	 * */
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

	/* Draws the corresponding polygon face using OpenGL
	 * */
	void polygon::draw(bool isFill)
	{

		int i,j;
		//printf("drawing polygon \n ");
		for (i=0;i<face_set.size();i++)
		{
			glColor3f(face_set[i]->face_color->R_value, face_set[i]->face_color->G_value, face_set[i]->face_color->B_value);
			//printf("face %d with %d vertices \n",i,face_set[i]->number_of_vertices);
			if(isFill)
				glBegin(GL_POLYGON);
			else
				glBegin(GL_LINE_LOOP);
			for(j=0;j<face_set[i]->number_of_vertices;j++)
				//printf("%f %f %f \n",face_set[i]->vertex_set[j].x_pos, face_set[i]->vertex_set[j].y_pos, face_set[i]->vertex_set[j].z_pos);
				glVertex3f(face_set[i]->vertex_set[j].x_pos, face_set[i]->vertex_set[j].y_pos, face_set[i]->vertex_set[j].z_pos);
			glEnd();
		}
	}

	/* For debugging info about the class object
	 * Prints info about all faces and the vertices constituting that face.
	 * */
	void polygon::debug(void)
	{
		int i,j;
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
	}

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
#include "../include/transformations.h"

	/* Main constructor for class
	* */
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

	/* Secondary constructor for class
	 * */
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

	/* Sets the center of mass/center of rotation of the composite body
	 * */
	void polygon::set_rot_center(float x, float y, float z)
	{
		x_trans = x;
		y_trans = y;
		z_trans = z;
	}

	/* Draws the corresponding polygon face using OpenGL
	 * */
	void polygon::draw(void)
	{

		int i,j;
		//printf("drawing polygon \n ");
		for (i=0;i<face_set.size();i++)
		{
			glColor3f(face_set[i]->face_color->R_value, face_set[i]->face_color->G_value, face_set[i]->face_color->B_value);
			//printf("face %d with %d vertices \n",i,face_set[i]->number_of_vertices);
			glBegin(GL_LINE_LOOP);
			for(j=0;j<face_set[i]->number_of_vertices;j++)
				//printf("%f %f %f \n",face_set[i]->vertex_set[j].x_pos, face_set[i]->vertex_set[j].y_pos, face_set[i]->vertex_set[j].z_pos);
				glVertex3f(face_set[i]->vertex_set[j].x_pos, face_set[i]->vertex_set[j].y_pos, face_set[i]->vertex_set[j].z_pos);
			glEnd();
		}
	}
/* Debugging the drawing operation*/
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
		exit(0);
	}
#endif

	/* Shift the object by specified units
	 * a : in X direction
	 * b : in Y direction
	 * c : in Z direction
	 * */
	/*void polygon::translate(float a,float b, float c)
	{
		int i,j;

		 Shift the center of rotation/center of mass
		x_trans += a;
		y_trans += b;
		z_trans += c;
		for (i=0;i<face_set.size();i++)
			for(j=0;j<face_set[i]->number_of_vertices;j++)
				face_set[i]->vertex_set[j] = translate_transform(face_set[i]->vertex_set[j], a, b, c);
	}*/

	/* Scale the object by specified units
	 * a : in X direction
	 * b : in Y direction
	 * c : in Z direction
	 * */
	/*void polygon::scale(float a,float b, float c)
	{
		int i,j;

		Ensure that the scaling factors are not zero. If they are then change their value to 1
		a = (a==0)?1:a;
		b = (b==0)?1:b;
		c = (c==0)?1:c;

		for (i=0;i<face_set.size();i++)
			for(j=0;j<face_set[i]->number_of_vertices;j++)
				face_set[i]->vertex_set[j] = scale_transform(face_set[i]->vertex_set[j], a, b, c);
	}*/

	/* For translation of center of rotation/center of mass*/
	/*void polygon::translate_center(float a,float b, float c)
	{
		int i,j;
		for (i=0;i<face_set.size();i++)
			for(j=0;j<face_set[i]->number_of_vertices;j++)
				face_set[i]->vertex_set[j] = translate_transform(face_set[i]->vertex_set[j], a, b, c);
	}
*/
	/* For rotating the object
	 * a: with respect to X
	 * b: with respect to Y
	 * c: with respect to Z
	 * theta: angle by which the object needs to be rotated
	 * */
	/*void polygon::rotate(float a, float b, float c, float theta)
	{
		int i,j;
		vertex center = vertex(0,0,0);
		translate_center(-x_trans,-y_trans,-z_trans);
			for (i=0;i<face_set.size();i++)
				for(j=0;j<face_set[i]->number_of_vertices;j++)
					face_set[i]->vertex_set[j] = rotate_transform(face_set[i]->vertex_set[j], a, b, c, theta);
		translate_center(x_trans,y_trans,z_trans);
	}*/

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

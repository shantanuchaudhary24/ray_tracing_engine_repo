/*
 * illumination.cpp
 *
 *  Created on: 14-Sep-2014
 *      Author: shantanu
 */

#include <math.h>
#include "../include/structs.h"

/* Given an initial and final vertices, the following
 * function generates the vector pointing from initial
 * to final vertex.
 * init_vertex	: Pointer to initial vertex
 * final_vertex	: Pointer to final vertex
 * */
vertex generate_vector(vertex* init_vertex, vertex* final_vertex)
{
	return vertex(final_vertex->x_pos - init_vertex->x_pos, final_vertex->y_pos - init_vertex->y_pos, final_vertex->z_pos - init_vertex->z_pos);
}

/* Returns the dot product of two vectors
 * vector1	: Pointer to Input vector 1
 * vector2	: Pointer to Input vector 2
 * */
float dot_product(vertex *vector1, vertex *vector2)
{
	return(vector1->x_pos*vector2->x_pos + vector1->y_pos*vector2->y_pos + vector1->z_pos*vector2->z_pos );
}

/* Following function calculates the length of the vector between
 * two vertex in the 3D space.
 * pt1	: Pointer to initial pt. of vector
 * pt2	: Pointer to final pt. of vector
 * */
float vector_length(vertex *pt1, vertex *pt2)
{
	float length = 0;
	length = sqrt(pow((pt1->x_pos - pt2->x_pos),2)+pow((pt1->y_pos - pt2->y_pos),2)+pow((pt1->z_pos - pt2->z_pos),2));
	return length;
}

/* Following function calculates the RGB vector obtained after diffuse
 * reflection. Standard optical physics has been followed.
 * normal_vector	: Pointer to Normal Vector at the point of incidence
 * intersectionPt	: Pointer to Coordinates of pt. of incidence
 * pt_color			: Pointer to Color of the point of incidence on the surface
 * light_src		: Pointer to data structure of light source
 * diff_coeff		: Surface diffuse reflection coefficient
 * */
RGB_value diffuse_reflection(vertex* normal_vector, vertex* intersectionPt, RGB_value *pt_color, light* light_src, float diff_coeff)
{
	RGB_value color_vector = RGB_value(0,0,0);
	vertex light_vector = generate_vector(intersectionPt, light_src->position );
	float distance_light = vector_length(light_src->position, intersectionPt);
	float cos_theta = dot_product(&light_vector, normal_vector);
	float att_factor = (light_src->att_factor[0] + light_src->att_factor[1]*distance_light + light_src->att_factor[2]*distance_light*distance_light);
	att_factor = 1/att_factor;
	diff_coeff = diff_coeff/att_factor;
	color_vector.R_value = diff_coeff*cos_theta*(pt_color->R_value)*(light_src->color->R_value);
	color_vector.G_value = diff_coeff*cos_theta*(pt_color->G_value)*(light_src->color->G_value);
	color_vector.B_value = diff_coeff*cos_theta*(pt_color->B_value)*(light_src->color->B_value);
	return color_vector;
}

/* Following function calculates the RGB vector obtained after specular
 * reflection. Standard optical physics has been followed.
 * normal_vector	: Pointer to Normal Vector at the point of incidence
 * intersectionPt	: Pointer to Coordinates of pt. of incidence
 * pt_color			: Pointer to Color of the point of incidence on the surface
 * light_src		: Pointer to data structure of light source
 * spec_coeff		: Surface diffuse reflection coefficient
 * spec_exp			: Specular reflection coefficient
 * */
RGB_value specular_reflection(vertex* normal_vector, vertex* intersectionPt, vertex *eye_position, RGB_value *pt_color, light* light_src, float spec_coeff, float spec_exp)
{
	RGB_value color_vector = RGB_value(0,0,0);
	vertex eye_vector = generate_vector(intersectionPt, eye_position);
	vertex light_vector = generate_vector(intersectionPt, light_src->position );
	float cos_theta = dot_product(&light_vector, normal_vector);
	vertex temp_vector = vertex(2*cos_theta*light_vector.x_pos, 2*cos_theta*light_vector.y_pos, 2*cos_theta*light_vector.z_pos);
	vertex reflection_vector = generate_vector(&light_vector,&temp_vector);
	float cos_alpha = dot_product(&reflection_vector, &eye_vector);
	color_vector.R_value = pow(spec_coeff,spec_exp)*cos_theta*(pt_color->R_value)*(light_src->color->R_value);
	color_vector.G_value = pow(spec_coeff,spec_exp)*cos_theta*(pt_color->G_value)*(light_src->color->G_value);
	color_vector.B_value = pow(spec_coeff,spec_exp)*cos_theta*(pt_color->B_value)*(light_src->color->B_value);
	return color_vector;
}

/* Following function calculates the RGB vector obtained after ambient
 * reflection. Standard optical physics has been followed.
 * normal_vector	: Pointer to Normal Vector at the point of incidence
 * intersectionPt	: Pointer to Coordinates of pt. of incidence
 * pt_color			: Pointer to Color of the point of incidence on the surface
 * light_src		: Pointer to data structure of light source
 * diff_coeff		: Surface diffuse reflection coefficient
 * */
RGB_value ambient_reflection(vertex* normal_vector, vertex* intersectionPt, RGB_value *pt_color, light* light_src, float ambi_coeff)
{
	RGB_value color_vector = RGB_value(0,0,0);
	color_vector.R_value = ambi_coeff*(pt_color->R_value)*(light_src->color->R_value);
	color_vector.G_value = ambi_coeff*(pt_color->G_value)*(light_src->color->G_value);
	color_vector.B_value = ambi_coeff*(pt_color->B_value)*(light_src->color->B_value);
	return color_vector;
}

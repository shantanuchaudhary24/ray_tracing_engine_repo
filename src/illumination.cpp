/*
 * illumination.cpp
 *
 *  Created on: 14-Sep-2014
 *      Author: shantanu
 */

#include <math.h>
#include <iostream>
#include "../include/structs.h"
#include "../include/macros.h"


/* For printing color values
 * */
void print_color(RGB_value *color)
{
	std::cout << "RGB Vector: ";
	std::cout << color->R_value << " , ";
	std::cout << color->G_value << " , ";
	std::cout << color->B_value << std::endl;
}

/* For printing vertices
 * */
void print_vertex(vertex *pt)
{
	std::cout << "Vertex Coordinates: ";
	std::cout << pt->x_pos << " , ";
	std::cout << pt->y_pos << " , ";
	std::cout << pt->z_pos << std::endl;
}

/* For printing light source information
 * */
void print_light(light *src)
{
	std::cout << "Light Position Vector: " ;
	print_vertex(src->position);
	std::cout << "Light RGB Vector: " ;
	print_color(src->color);
	std::cout << "Light Attenuation Vector: " ;
	std::cout << src->att_factor[0] << " , ";
	std::cout << src->att_factor[1]<< " , ";
	std::cout << src->att_factor[2]<< std::endl;
}

/* Given an initial and final vertices, the following
 * function generates the vector pointing from initial
 * to final vertex (normalized).
 * init_vertex	: Pointer to initial vertex
 * final_vertex	: Pointer to final vertex
 * */
vertex generate_vector(vertex* init_vertex, vertex* final_vertex)
{

	float normal_factor = sqrt(pow(final_vertex->x_pos - init_vertex->x_pos,2)+pow(final_vertex->y_pos - init_vertex->y_pos,2)+pow(final_vertex->z_pos - init_vertex->z_pos,2));
	return vertex((final_vertex->x_pos - init_vertex->x_pos)/normal_factor,
				(final_vertex->y_pos - init_vertex->y_pos)/normal_factor,
				(final_vertex->z_pos - init_vertex->z_pos)/normal_factor);
}

/* Returns the dot product of two vectors
 * vector1	: Pointer to Input vector 1
 * vector2	: Pointer to Input vector 2
 * */
float dot_product(vertex *vector1, vertex *vector2)
{
	float result = vector1->x_pos*vector2->x_pos + vector1->y_pos*vector2->y_pos + vector1->z_pos*vector2->z_pos;
	if(result < 0)
		return 0;
	return result;
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
RGB_value diffuse_reflection(vertex* normal_vector, vertex* intersectionPt, RGB_value *pt_color, light *light_src, float diff_coeff)
{
	RGB_value color_vector = RGB_value(0,0,0);
	vertex light_vector = generate_vector(intersectionPt, light_src->position );
	float distance_light = vector_length(light_src->position, intersectionPt);
	float cos_theta = dot_product(&light_vector, normal_vector);
	if(cos_theta>0){
	float att_factor = (light_src->att_factor[0] + light_src->att_factor[1]*distance_light + light_src->att_factor[2]*distance_light*distance_light);
	att_factor = 1/att_factor;
	diff_coeff = diff_coeff/att_factor;
	color_vector.R_value = diff_coeff*cos_theta*(pt_color->R_value)*(light_src->color->R_value);
	color_vector.G_value = diff_coeff*cos_theta*(pt_color->G_value)*(light_src->color->G_value);
	color_vector.B_value = diff_coeff*cos_theta*(pt_color->B_value)*(light_src->color->B_value);
	}
	else{
		color_vector.R_value = 0;
		color_vector.G_value = 0;
		color_vector.B_value = 0;
	}

	/* For debugging colors*/
#ifdef DEBUG_DIFFUSE
	std::cout << "<<<<<<<<<<< Diffused Reflection Calculation: Start >>>>>>>>>>>>" << std::endl;
	std::cout << "Normal Vector: " ;
	print_vertex(normal_vector);

	std::cout << "IntersectionPt Vector: " ;
	print_vertex(intersectionPt);

	std::cout << "Color Vector of Surface: " ;
	print_color(pt_color);

	std::cout << "Distance of Light Source: " ;
	std::cout << distance_light << std::endl;

	print_light(light_src);

	std::cout << "Calculated Attenuation Factor: " ;
	std::cout << att_factor << std::endl;

	std::cout << "Diffused Reflection Coefficient: ";
	std::cout << diff_coeff << std::endl;

	// TODO
	std::cout << "Calculated cos_theta Factor: " ;
	std::cout << cos_theta << std::endl;

	std::cout << "Calculated Diffused Reflection Color Vector: " ;
	print_color(&color_vector);
	std::cout << "Diffused Reflection Calculation: End" << std::endl << std::endl << std::endl;
#endif

	return color_vector;
}

/* Following function calculates the RGB vector obtained after specular
 * reflection. Standard optical physics has been followed.
 * normal_vector	: Pointer to Normal Vector at the point of incidence
 * intersectionPt	: Pointer to Coordinates of pt. of incidence
 * pt_color			: Pointer to Color of the point of incidence on the surface
 * light_src		: Pointer to data structure of light source
 * spec_coeff		: Surface specular reflection coefficient
 * spec_exp			: Specular reflection coefficient
 * */
RGB_value specular_reflection(vertex* normal_vector, vertex* intersectionPt, vertex *eye_position, RGB_value *pt_color, light* light_src, float specular_coeff, float spec_exp)
{
	RGB_value color_vector = RGB_value(0,0,0);
	vertex eye_vector = generate_vector(intersectionPt, eye_position);
	vertex light_vector = generate_vector(intersectionPt, light_src->position );
	float cos_theta = dot_product(&light_vector, normal_vector);
	if(cos_theta>0){
	vertex temp_vector = vertex(2*cos_theta*normal_vector->x_pos, 2*cos_theta*normal_vector->y_pos, 2*cos_theta*normal_vector->z_pos);
	vertex reflection_vector = generate_vector(&light_vector,&temp_vector);
	float cos_alpha = dot_product(&reflection_vector, &eye_vector);
	color_vector.R_value = pow(cos_alpha,spec_exp)*specular_coeff*(pt_color->R_value)*(light_src->color->R_value);
	color_vector.G_value = pow(cos_alpha,spec_exp)*specular_coeff*(pt_color->G_value)*(light_src->color->G_value);
	color_vector.B_value = pow(cos_alpha,spec_exp)*specular_coeff*(pt_color->B_value)*(light_src->color->B_value);
	}
	else{
		color_vector.R_value = 0;
		color_vector.G_value = 0;
		color_vector.B_value = 0;
	}

	/* For debugging colors*/
#ifdef DEBUG_SPECULAR
	std::cout << "<<<<<<<<<< Specular Reflection Calculation: Start >>>>>>>>>>>>" << std::endl;
	std::cout << "Normal Vector: " ;
	print_vertex(normal_vector);

	std::cout << "IntersectionPt Vector: " ;
	print_vertex(intersectionPt);

	std::cout << "Color Vector of Surface: " ;
	print_color(pt_color);

	std::cout << "Light Position Vector: " ;
	print_vertex(light_src->position);

	std::cout << "Light RGB Vector: " ;
	print_color(light_src->color);

	std::cout << "Specular Reflection Coefficient: ";
	std::cout << specular_coeff << std::endl;

	std::cout << "Specular Reflection Exponent: ";
	std::cout << spec_exp << std::endl;

	std::cout << "Calculated cos_theta Factor: " ;
	std::cout << cos_theta << std::endl;

	std::cout << "Calculated cos_alpha Factor: " ;
	std::cout << cos_alpha << std::endl;

	std::cout << "Calculated Specular Reflection Color Vector: " ;
	print_color(&color_vector);
	std::cout << "Specular Reflection Calculation: End" << std::endl << std::endl << std::endl;
#endif

	return color_vector;
}

/* Following function calculates the RGB vector obtained after ambient
 * reflection. Standard optical physics has been followed.
 * normal_vector	: Pointer to Normal Vector at the point of incidence
 * intersectionPt	: Pointer to Coordinates of pt. of incidence
 * pt_color			: Pointer to Color of the point of incidence on the surface
 * light_src		: Pointer to data structure of light source
 * ambi_coeff		: Surface ambient reflection coefficient
 * */
RGB_value ambient_reflection(vertex* normal_vector, vertex* intersectionPt, RGB_value *pt_color, light* light_src, float ambi_coeff)
{
	RGB_value color_vector = RGB_value(0,0,0);

	color_vector.R_value = ambi_coeff*(pt_color->R_value)*(light_src->color->R_value);
	color_vector.G_value = ambi_coeff*(pt_color->G_value)*(light_src->color->G_value);
	color_vector.B_value = ambi_coeff*(pt_color->B_value)*(light_src->color->B_value);

	/* For debugging colors*/
#ifdef DEBUG_AMBIENT
	std::cout << "<<<<<<<<<< Ambient Reflection Calculation: Start >>>>>>>>>>>>" << std::endl;
	std::cout << "Normal Vector: " ;
	print_vertex(normal_vector);

	std::cout << "IntersectionPt Vector: " ;
	print_vertex(intersectionPt);

	std::cout << "Color Vector of Surface: " ;
	print_color(pt_color);

	print_light(light_src);

	std::cout << "Ambient Reflection Coefficient: ";
	std::cout << ambi_coeff << std::endl;

	std::cout << "Calculated Ambient Reflection Color Vector: " ;
	print_color(&color_vector);

	std::cout << "Ambient Reflection Calculation: End" << std::endl << std::endl << std::endl;
#endif

	return color_vector;
}

/* Calculates the net color obtained after diffused, specular
 * and ambient reflection for a single light source.
 * */
RGB_value total_reflection(vertex* normal_vector, vertex* intersectionPt, vertex* ray_startPt, RGB_value *pt_color , config* config_ptr, int index)
{
	RGB_value final_color=color_comp(0,0,0);
	RGB_value diff_color= diffuse_reflection(normal_vector,intersectionPt, pt_color, config_ptr->light_source[index],config_ptr->diffuse_coeff);
	RGB_value spec_color= specular_reflection(normal_vector, intersectionPt, ray_startPt, pt_color, config_ptr->light_source[index], config_ptr->specular_coeff, config_ptr->specular_exp);
	RGB_value amb_color= ambient_reflection( normal_vector, intersectionPt, pt_color, config_ptr->light_source[index],config_ptr->ambient_coeff);

	final_color=color_comp(diff_color.R_value+spec_color.R_value+amb_color.R_value,
									diff_color.G_value+spec_color.G_value+amb_color.G_value,
									diff_color.B_value+spec_color.B_value+amb_color.B_value);
	final_color.R_value=final_color.R_value/(final_color.R_value+final_color.G_value+final_color.B_value);
	final_color.G_value=final_color.G_value/(final_color.R_value+final_color.G_value+final_color.B_value);
	final_color.B_value=final_color.B_value/(final_color.R_value+final_color.G_value+final_color.B_value);

	return final_color;
}

/* Calculate the net color obtained for all the light sources
 * in the scene.
 * */
RGB_value scene_illumination(vertex* normal_vector, vertex* intersectionPt, vertex* ray_startPt, RGB_value *pt_color, config* config_ptr)
{
	RGB_value final_color=color_comp(0,0,0);
	RGB_value temp_color=color_comp(0,0,0);
	int num_sources = config_ptr->num_lights;
	for(int i=0; i<num_sources;i++)
	{
		temp_color = total_reflection(normal_vector, intersectionPt, ray_startPt, pt_color, config_ptr, i);
		final_color.R_value += temp_color.R_value;
		final_color.G_value += temp_color.G_value;
		final_color.B_value += temp_color.B_value;
	}

	final_color.R_value=final_color.R_value/(final_color.R_value+final_color.G_value+final_color.B_value);
	final_color.G_value=final_color.G_value/(final_color.R_value+final_color.G_value+final_color.B_value);
	final_color.B_value=final_color.B_value/(final_color.R_value+final_color.G_value+final_color.B_value);

	return final_color;
}

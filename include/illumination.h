/*
 * illumiantion.h
 *
 *  Created on: 14-Sep-2014
 *      Author: shantanu
 */

#ifndef ILLUMIANTION_H_
#define ILLUMIANTION_H_

RGB_value scene_illumination(vertex* normal_vector, vertex* intersectionPt, vertex* ray_startPt, RGB_value *pt_color, config* config_ptr);
void print_color(RGB_value *color);
void print_vertex(vertex *pt);
vertex generate_vector(vertex* init_vertex, vertex* final_vertex);
float dot_product(vertex *vector1, vertex *vector2);
float vector_length(vertex *pt1, vertex *pt2);
void print_light(light *src);


#endif /* ILLUMIANTION_H_ */

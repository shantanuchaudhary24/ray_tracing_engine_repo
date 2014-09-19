/*
 * illumiantion.h
 *
 *  Created on: 14-Sep-2014
 *      Author: shantanu
 */

#ifndef ILLUMIANTION_H_
#define ILLUMIANTION_H_

RGB_value* scene_illumination(vertex* normal_vector, vertex* intersectionPt, Ray* ray, RGB_value *pt_color, config* config_ptr);
void print_color(RGB_value *color);
void print_vertex(vertex *pt);
void print_light(light *src);


#endif /* ILLUMIANTION_H_ */

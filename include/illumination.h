/*
 * illumiantion.h
 *
 *  Created on: 14-Sep-2014
 *      Author: shantanu
 */

#ifndef ILLUMIANTION_H_
#define ILLUMIANTION_H_


RGB_value diffuse_reflection(vertex* normal_vector, vertex* intersectionPt, RGB_value *pt_color, light* light_src, float diff_coeff);
RGB_value specular_reflection(vertex* normal_vector, vertex* intersectionPt, RGB_value *pt_color, light* light_src, float diff_coeff);
RGB_value ambient_reflection(vertex* normal_vector, vertex* intersectionPt, RGB_value *pt_color, light* light_src, float diff_coeff);

#endif /* ILLUMIANTION_H_ */

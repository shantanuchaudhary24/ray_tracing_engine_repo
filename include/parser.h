/*
 * parser.h
 *
 *  Created on: 07-Sep-2014
 *      Author: shantanu
 */

#ifndef PARSER_H_
#define PARSER_H_

void destroy_light(light *src);
void destroy_cube(cube* sample);
void read_config(std::ifstream& in, config *out);
void debug_sphere(sphere* sample);


#endif /* PARSER_H_ */

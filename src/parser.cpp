/*
 * parser.cpp
 *
 *  Created on: 07-Sep-2014
 *      Author: shantanu
 */
#include "../include/headers.h"
#include "../include/structs.h"
#include "../include/illumination.h"
#include <iomanip>
#include <exception>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdexcept>

/* Typecasts a string into float*/
float ConvertStringToFloat(const std::string& str)
{
  std::istringstream ss(str);
  float number = 0;
  try{
	  ss >> number;
  }
  catch (const std::invalid_argument& ia) {
  	  std::cerr << "Invalid argument: " << ia.what() << '\n';
  }
  return number;
}

/* Typecasts a string into short int*/
float ConvertStringToShort(const std::string& str)
{
  std::istringstream ss(str);
  short number = 0;
  try{
	  ss >> number;
  }
  catch (const std::invalid_argument& ia) {
  	  std::cerr << "Invalid argument: " << ia.what() << '\n';
  }
  return number;
}

/* This function takes an input string and separates the CSV of coordinates
 * passed to it in the form of string and typecasts the individual coordinates
 * and stores them into the array passed to it.
 *
 * */
void config_coordinates(std::string str, float *array)
{
	size_t found1 = str.find_first_of(",");
	size_t found2 = str.find_last_of(",");

	if(found1 != std::string::npos && found2 != std::string::npos)
	{
		array[0] = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,found1 - str.find_first_of(" ") -1));
		array[1] = ConvertStringToFloat(str.substr(found1 + 2, found2-found1-2));
		array[2] = ConvertStringToFloat(str.substr(found2 + 2, str.length()-found2 - 2));
	}
}

/* This function takes an input string and separates the CSV of coordinates
 * passed to it in the form of string and typecasts the individual coordinates
 * and stores them into the array passed to it.
 *
 * */
void config_vertex(std::string str, vertex *pt)
{
	size_t found1 = str.find_first_of(",");
	size_t found2 = str.find_last_of(",");

	if(found1 != std::string::npos && found2 != std::string::npos)
	{
		pt->x_pos = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,found1 - str.find_first_of(" ") -1));
		pt->y_pos = ConvertStringToFloat(str.substr(found1 + 2, found2-found1-1));
		pt->z_pos = ConvertStringToFloat(str.substr(found2 + 2, str.length()-found2 - 2));
	}
}

/* This function takes an input string and separates the CSV of coordinates
 * passed to it in the form of string and typecasts the individual coordinates
 * and stores them into the array passed to it.
 *
 * */
void config_color(std::string str, RGB_value *color)
{
	size_t found1 = str.find_first_of(",");
	size_t found2 = str.find_last_of(",");

	if(found1 != std::string::npos && found2 != std::string::npos)
	{
		color->R_value = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,found1 - str.find_first_of(" ") -1));
		color->G_value = ConvertStringToFloat(str.substr(found1 + 2, found2-found1-1));
		color->B_value = ConvertStringToFloat(str.substr(found2 + 2, str.length()-found2 - 2));
	}
}

/* This function takes input string and parses the CSV which
 * express the properties of light.
 * */
void addLightSource(std::string str, light *src)
{
	size_t found11 = str.find_first_of("<");
	size_t found12 = str.find_first_of(">");
	size_t found21 = str.find_last_of("<");
	size_t found22 = str.find_last_of(">");


	src->position = (vertex *)malloc(sizeof(vertex));
	src->color = (RGB_value *)malloc(sizeof(RGB_value));
	src->att_factor = (float *)malloc(3*sizeof(float));

	if(found11 != std::string::npos && found21 != std::string::npos && found12 != std::string::npos && found22 != std::string::npos)
	{
		config_vertex(str.substr(found11,found12 - found11),src->position);
		config_color(str.substr(found12+3,found21 - found12-5),src->color);
		config_coordinates(str.substr(found21,found22 - found21 -1),src->att_factor);
	}
}

void read_config(std::ifstream& in, config *out) {
	/* Name of input file*/
	in.open("config.cfg");
	std::string str;

	while(!in.eof()) {
		while(getline(in,str)) {
			std::string::size_type begin = str.find_first_not_of(" \f\t\v");

			//Skips blank lines
			if(begin == std::string::npos)
				continue;

			//Skips #
			if(std::string("#").find(str[begin]) != std::string::npos)
				continue;

			std::string firstWord;
			try {
				firstWord = str.substr(0,str.find(" "));
				//std::cout << "word: " << firstWord << std::endl;
			}
			catch(std::exception& e) {
				firstWord = str.erase(str.find_first_of(" "),str.find_first_not_of(" "));
			}

			if(firstWord == "WINDOW_WIDTH")
				out->window_width = ConvertStringToShort(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "WINDOW_HEIGHT")
				out->window_height = ConvertStringToShort(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "EYE_POSITION")
				config_coordinates(str, out->eye_pos);

			if(firstWord == "EYE_UP")
				config_coordinates(str, out->eye_up);

			if(firstWord == "EYE_SIDE")
				config_coordinates(str, out->eye_side);

			if(firstWord == "EYE_NORMAL")
				config_coordinates(str, out->eye_normal);

			if(firstWord == "FRONTPLANE_DISTANCE")
				out->frontplane_distance = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "BACKPLANE_DISTANCE")
				out->backplane_distance = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "VIEWPLANE_DISTANCE")
				out->viewplane_distance = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "FRONTPLANE_WIDTH")
				out->frontplane_width = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "FRONTPLANE_HEIGHT")
				out->frontplane_height = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "SPHERE_CENTER")
				config_coordinates(str, out->spherecenter);

			if(firstWord == "SPHERE_COLOR")
				config_coordinates(str, out->spherecolor);

			if(firstWord == "SPHERE_RADIUS")
				out->sphereradius = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "SPECULAR_EXP")
				out->specular_exp = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "SPECULAR_COEFF")
				out->specular_coeff = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "DIFFUSE_COEFF")
				out->diffuse_coeff = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "AMBIENT_COEFF")
				out->ambient_coeff = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "NUM_LIGHT_SOURCES")
			{
				/* Initialize the light sources array by allotting memory*/
				out->num_lights = ConvertStringToShort(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
				out->current_index = 0;
				out->light_source = (light **)malloc((out->num_lights)*sizeof(light *));
			}

			if(firstWord == "LIGHT_SOURCE")
			{
				if(out->current_index < out->num_lights)
				{
					out->light_source[out->current_index] = (light *)malloc(sizeof(light));
					addLightSource(str, out->light_source[out->current_index]);
					out->current_index++;
				}
			}
		}
	}
}




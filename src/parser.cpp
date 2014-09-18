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

	std::cout << str << std::endl;
	size_t found1 = str.find_first_of("<");
	size_t found2 = str.find_last_of(">");
	size_t found3 = str.find_first_of(",");	// First "," in the string
	size_t found4 = str.find_last_of(",");	// Last "," in the string
	std::string mid_string = str.substr(found3+2, found4 - found3 - 2);

	if(found3 != std::string::npos && found4 != std::string::npos )
	{
		color->R_value	= ConvertStringToFloat(str.substr(found1+2, found3-found1-2));
		color->G_value	= ConvertStringToFloat(mid_string.substr(0,mid_string.find_first_of(",")));
		color->B_value	= ConvertStringToFloat(mid_string.substr(mid_string.find_first_of(",") + 2, mid_string.length() - 1));
		color->alpha	= ConvertStringToFloat(str.substr(found4 + 2, found2-found4-3));
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

void addSphere(std::string str, sphere *src)
{
	size_t found11 = str.find_first_of("<");
	size_t found12 = str.find_first_of(">");
	size_t found21 = str.find_last_of("<");
	size_t found22 = str.find_last_of(">");


	src->center = (vertex *)malloc(sizeof(vertex));
	src->color = (RGB_value *)malloc(sizeof(RGB_value));

	if(found11 != std::string::npos && found21 != std::string::npos && found12 != std::string::npos && found22 != std::string::npos)
	{
		config_vertex(str.substr(found11,found12 - found11),src->center);
		config_color(str.substr(found21,found22 - found21 + 1),src->color);
		src->radius=ConvertStringToFloat(str.substr(found22+2));
	}
}

/* Hash function for mapping strings to string_code
 * */
string_code hashit (std::string const& inString) {
    if (inString == "WINDOW_WIDTH") return WINDOW_WIDTH;
    if (inString == "WINDOW_HEIGHT") return WINDOW_HEIGHT;
    if (inString == "EYE_POSITION") return EYE_POSITION;
    if (inString == "EYE_UP") return EYE_UP;
    if (inString == "EYE_SIDE") return EYE_SIDE;
    if (inString == "EYE_NORMAL") return EYE_NORMAL;
    if (inString == "FRONTPLANE_DISTANCE") return FRONTPLANE_DISTANCE;
    if (inString == "BACKPLANE_DISTANCE") return BACKPLANE_DISTANCE;
    if (inString == "VIEWPLANE_DISTANCE") return VIEWPLANE_DISTANCE;
    if (inString == "FRONTPLANE_WIDTH") return FRONTPLANE_WIDTH;
    if (inString == "FRONTPLANE_HEIGHT") return FRONTPLANE_HEIGHT;
    if (inString == "SPHERE") return SPHERE;
    if (inString == "SPECULAR_EXP") return SPECULAR_EXP;
    if (inString == "SPECULAR_COEFF") return SPECULAR_COEFF;
    if (inString == "DIFFUSE_COEFF") return DIFFUSE_COEFF;
    if (inString == "AMBIENT_COEFF") return AMBIENT_COEFF;
    if (inString == "LIGHT_SOURCE") return LIGHT_SOURCE;
    return NULL_STR;
}

/* Function responsible for parsing and pushing data
 * to various data structures.
 * */
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

			switch(hashit(firstWord)){

				case WINDOW_WIDTH:
					out->window_width = ConvertStringToShort(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case WINDOW_HEIGHT:
					out->window_height = ConvertStringToShort(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case EYE_POSITION:
					config_coordinates(str, out->eye_pos);
					break;

				case EYE_UP:
					config_coordinates(str, out->eye_up);
					break;

				case EYE_SIDE:
					config_coordinates(str, out->eye_side);
					break;

				case EYE_NORMAL:
					config_coordinates(str, out->eye_normal);
					break;

				case FRONTPLANE_DISTANCE:
					out->frontplane_distance = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case BACKPLANE_DISTANCE:
					out->backplane_distance = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case VIEWPLANE_DISTANCE:
					out->viewplane_distance = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case FRONTPLANE_WIDTH:
					out->frontplane_width = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case FRONTPLANE_HEIGHT:
					out->frontplane_height= ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case SPHERE:
				{
					sphere* sp=(sphere*)malloc(sizeof(sphere));
					addSphere(str,sp);
					out->sphere_array.push_back(sp);
					break;
				}
				case SPECULAR_EXP:
					out->specular_exp = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case SPECULAR_COEFF:
					out->specular_coeff = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case DIFFUSE_COEFF:
					out->diffuse_coeff = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case AMBIENT_COEFF:
					out->ambient_coeff = ConvertStringToFloat(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));
					break;

				case LIGHT_SOURCE:
				{
					light* source = (light *)malloc(sizeof(light));
					addLightSource(str, source);
					out->light_source.push_back(source);
					break;
				}
			}
		}
	}
}




/*
 * parser.cpp
 *
 *  Created on: 07-Sep-2014
 *      Author: shantanu
 */
#include "../include/headers.h"
#include "../include/structs.h"
#include <iomanip>
#include <exception>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdexcept>

/* Typecasts a string into float*/
float ConvertStringToNumber(const std::string& str)
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

/* This function takes an input string and separated the CSV of coordinates
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
		array[0] = ConvertStringToNumber(str.substr(str.find_first_of(" ")+1,found1 - str.find_first_of(" ") -1));
		array[1] = ConvertStringToNumber(str.substr(found1 + 2, found2-found1-2));
		array[2] = ConvertStringToNumber(str.substr(found2 + 2, str.length()-found2 - 2));
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

			if(firstWord == "EYE_POSITION")
				config_coordinates(str, out->eye_pos);

			if(firstWord == "EYE_UP")
				config_coordinates(str, out->eye_up);

			if(firstWord == "EYE_SIDE")
				config_coordinates(str, out->eye_side);

			if(firstWord == "EYE_NORMAL")
				config_coordinates(str, out->eye_normal);

			if(firstWord == "FRONTPLANE_DISTANCE")
				out->frontplane_distance = ConvertStringToNumber(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "BACKPLANE_DISTANCE")
				out->backplane_distance = ConvertStringToNumber(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "VIEWPLANE_DISTANCE")
				out->viewplane_distance = ConvertStringToNumber(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "FRONTPLANE_WIDTH")
				out->frontplane_width = ConvertStringToNumber(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "FRONTPLANE_HEIGHT")
				out->frontplane_height = ConvertStringToNumber(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

			if(firstWord == "SPHERE_CENTER")
				config_coordinates(str, out->spherecenter);

			if(firstWord == "SPHERE_COLOR")
				config_coordinates(str, out->spherecolor);

			if(firstWord == "SPHERE_RADIUS")
				out->sphereradius = ConvertStringToNumber(str.substr(str.find_first_of(" ")+1,str.length()-str.find_first_of(" ")-1));

		}
	}
}




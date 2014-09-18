/*
 * structs.h
 * structs for project source code
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */
#include <vector>

#ifndef STRUCTS_H_
#define STRUCTS_H_

/* Enumeration for strings to be used in
 * switch-case statements in the parser
 * */
enum string_code{
	WINDOW_WIDTH,
	WINDOW_HEIGHT,
	EYE_POSITION,
	EYE_UP,
	EYE_SIDE,
	EYE_NORMAL,
	FRONTPLANE_DISTANCE,
	BACKPLANE_DISTANCE,
	VIEWPLANE_DISTANCE,
	FRONTPLANE_WIDTH,
	FRONTPLANE_HEIGHT,
	SPHERE,
	SPECULAR_EXP,
	SPECULAR_COEFF,
	DIFFUSE_COEFF,
	AMBIENT_COEFF,
	LIGHT_SOURCE,

	/* NULL string in case none of the above */
	NULL_STR
};

/* Defines a tuple of RBG value
 * */
typedef struct color_comp{
	float R_value;
	float G_value;
	float B_value;
	float alpha;

	color_comp(){
			R_value = 1;
			G_value = 1;
			B_value = 1;
			alpha	= 1;
		}

	color_comp(float R, float G, float B){
		R_value = R;
		G_value = G;
		B_value = B;
		alpha	= 1;
	}

	color_comp(float R, float G, float B, float A){
		R_value = R;
		G_value = G;
		B_value = B;
		alpha	= A;
	}
}RGB_value;

/* Defines a tuple of x,y,z coordinates of a point
 * */
typedef struct vertex_pt{
	float x_pos;
	float y_pos;
	float z_pos;

	vertex_pt(){
		x_pos = 0;
		y_pos = 0;
		z_pos = 0;
	}

	vertex_pt( float vx, float vy, float vz){
		x_pos = vx;
		y_pos = vy;
		z_pos = vz;

	}
}vertex;

/* Defines the info about the polygon face
 * */
typedef struct info_face{
	/* Defines color of the face*/
	RGB_value* face_color;

	/* Pointer to the vertex set*/
	vertex* vertex_set;

	/* Number of vertices constituting the face*/
	int number_of_vertices;
}face_info;

typedef struct Sphere{

	RGB_value* color;

	vertex* center;

	float radius;
}sphere;


typedef struct Ray_{

	vertex* direction;

	vertex* startPoint;

}Ray;

/* Struct that defines light properties */
typedef struct struct_light{
	vertex *position;	// Position of light
	RGB_value *color;		// Color of light (RGB (0-1))
	float *att_factor;	// Attenuation Factor 'aX' in 1/(a0 + a1*d + a2*d^2)
}light;

/* Struct for parsing information from config file*/
typedef struct config_struct {

	/* OpenGL window size variables*/
	int window_width;
	int window_height;

	/* Scene Properties*/
	float *eye_pos;
	float *eye_up;
	float *eye_side;
	float *eye_normal;
	float backplane_distance;
	float frontplane_distance;
	float viewplane_distance;
	float frontplane_width;
	float frontplane_height;

	/* Surface Properties (For all surfaces in the scene)*/
	float specular_coeff;
	float specular_exp;
	float diffuse_coeff;
	float ambient_coeff;

	/* Light source properties*/
	std::vector<light*> light_source;
	std::vector<sphere*> sphere_array;

}config;

#endif /* STRUCTS_H_ */

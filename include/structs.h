/*
 * structs.h
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_


typedef struct color_comp{
	float R_value;
	float G_value;
	float B_value;

	color_comp(){
			R_value = 1;
			G_value = 1;
			B_value = 1;
		}

	color_comp(float R, float G, float B){
		R_value = R;
		G_value = G;
		B_value = B;
	}
}RGB_value;

typedef struct vertex_pt{
	int vertex_number;
	double x_pos;
	double y_pos;
	double z_pos;

	vertex_pt(){
		vertex_number = 0;
		x_pos = 0;
		y_pos = 0;
		z_pos = 0;
	}

	vertex_pt(int number, double vx, double vy, double vz){
		vertex_number = number;
		x_pos = vx;
		y_pos = vy;
		z_pos = vz;

	}

	vertex_pt(int number, double vx, double vy, double vz, RGB_value color){
			vertex_number = number;
			x_pos = vx;
			y_pos = vy;
			z_pos = vz;
	}

}vertex;

typedef struct info_face{
	RGB_value* face_color;
	vertex* vertex_set;
	int number_of_vertices;
}face_info;


#endif /* STRUCTS_H_ */

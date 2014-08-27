/*
 * structs.h
 * structs for project source code
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

/* Defines a tuple of RBG value
 * */
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


#endif /* STRUCTS_H_ */

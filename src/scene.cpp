/*
 * scene.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */

#include "../include/headers.h"
#include "../include/structs.h"
#include "../include/polygon.h"
#include "../include/matrix.h"
#include "../include/transformations.h"
#include "../include/frustum.h"
#include "../include/clipping.h"
#include "../include/scene.h"


extern std::vector<polygon*> sceneData;
extern polygon clippingArea;
extern std::vector<float*> clipping_plane_eq;
extern float* viewingCordMatrix;
extern float* inverseviewingCordMatrix;

void create_scene(){
	RGB_value color1 = color_comp(1.0f,0.0f,0.0f);

		vertex face1[] = {
							vertex(3.0f,3.0f,-2.0f),
							vertex(-3.0f,3.0f,-2.0f),
							vertex(-3.0f,-3.0f,-2.0f),
							vertex(3.0f,-3.0f,-2.0f),
						};
	RGB_value color2 = color_comp(1.0f,1.0f,0.0f);
		vertex face2[] = {
							vertex(3.0f,3.0f,-2.5f),
							vertex(-3.0f,3.0f,-2.5f),
							vertex(-3.0f,-3.0f,-2.5f),
							vertex(3.0f,-3.0f,-2.5f),
						};
	RGB_value color3 = color_comp(1.0f,0.0f,1.0f);
		vertex face3[] = {
							vertex(3.0f,3.0f,-2.0f),
							vertex(3.0f,3.0f,-2.5f),
							vertex(3.0f,-3.0f,-2.5f),
							vertex(3.0f,-3.0f,-2.0f),
						};
	RGB_value color4 = color_comp(0.0f,1.0f,1.0f);
		vertex face4[] = {
							vertex(3.0f,3.0f,-2.0f),
							vertex(3.0f,3.0f,-2.5f),
							vertex(-3.0f,3.0f,-2.5f),
							vertex(-3.0f,3.0f,-2.0f),
						};
	RGB_value color5 = color_comp(0.0f,1.0f,0.5f);
		vertex face5[] = {
							vertex(-3.0f,3.0f,-2.0f),
							vertex(-3.0f,3.0f,-2.5f),
							vertex(-3.0f,-3.0f,-2.5f),
							vertex(-3.0f,-3.0f,-2.0f),
						};
	RGB_value color6 = color_comp(1.0f,0.0f,0.5f);
		vertex face6[] = {
							vertex(3.0f,-3.0f,-2.0f),
							vertex(3.0f,-3.0f,-2.5f),
							vertex(-3.0f,-3.0f,-2.5f),
							vertex(-3.0f,-3.0f,-2.0f),
						};
		polygon* poly = (polygon*)malloc(sizeof(polygon));
		poly->add_face(4,face1,&color1);
		poly->add_face(4,face2,&color2);
		poly->add_face(4,face3,&color3);
		poly->add_face(4,face4,&color4);
		poly->add_face(4,face5,&color5);
		poly->add_face(4,face6,&color6);
		sceneData.push_back(poly);

	RGB_value color7 = color_comp(0.5f,0.5f,0.0f);
		vertex face7[] = {
							vertex(3.0f,3.0f,-2.5f),
							vertex(-3.0f,-3.0f,-2.5f),
							vertex(-3.0f,3.0f,-2.0f),
						};

		polygon* poly2 = (polygon*)malloc(sizeof(polygon));
		poly2->add_face(3,face7,&color1);
		sceneData.push_back(poly2);
}

void init(config *ptr){

	float eye[]={ptr->eye_pos[0],ptr->eye_pos[1],ptr->eye_pos[2]};
	float eyeup[]={ptr->eye_up[0],ptr->eye_up[1],ptr->eye_up[2]};
	float eyeside[]={ptr->eye_side[0],ptr->eye_side[1],ptr->eye_side[2]};
	float eyenormal[]={ptr->eye_normal[0],ptr->eye_normal[1],ptr->eye_normal[2]};
	float d1=ptr->frontplane_distance;		//distance of front plane from eye
	float d2=ptr->backplane_distance;		//distance of back plane from eye
	float d3=ptr->viewplane_distance;		//distance of view plane from eye
	float width=ptr->frontplane_width;	//width and height of front plane
	float height=ptr->frontplane_height;
	float midpointViewPlane[]={eye[0]+d3*eyenormal[0],eye[1]+d3*eyenormal[1],eye[2]+d3*eyenormal[2]};		//midpoint of view plane
	float rdash[]={0,0,0};


		for(int j=0;j<3;j++)
			rdash[0]+=-midpointViewPlane[j]*eyeside[j];
		for(int j=0;j<3;j++)
			rdash[1]+=-midpointViewPlane[j]*eyeup[j];
		for(int j=0;j<3;j++)
			rdash[2]+=-midpointViewPlane[j]*eyenormal[j];

	float Matrix[]={eyeside[0],eyeup[0],eyenormal[0],0,eyeside[1],eyeup[1],eyenormal[1],0,eyeside[2],eyeup[2],eyenormal[2],0,rdash[0],rdash[1],rdash[2],1};

	viewingCordMatrix = (float*)malloc(16*sizeof(float));
	for(int i=0;i<16;i++)
		viewingCordMatrix[i]=Matrix[i];

	inverseviewingCordMatrix=(float*)malloc(16*sizeof(float));
	InverseMatrix(viewingCordMatrix,inverseviewingCordMatrix);

	float* frustrum=create_frustrum(eye,eyenormal,eyeup,eyeside,d1,d2,width,height);

	RGB_value color = color_comp(0.0f,1.0f,0.0f);
	int planes[]={
				3,2,1,0,		//front plane
				4,5,6,7,		//back plane
				2,6,5,1,		//left plane
				0,4,7,3,		//right plane
				1,5,4,0,		//up plane
				3,7,6,2,		//down plane
				};
	clippingArea = polygon();
	for(int i=0;i<6;i++){
		vertex verts[4];
		for(int j=0;j<4;j++){
			verts[j]= vertex(frustrum[3*planes[4*i+j]],frustrum[3*planes[4*i+j]+1],frustrum[3*planes[4*i+j]+2]);
		}

		clippingArea.add_face(4,verts,&color);
		clipping_plane_eq.push_back(plane_equation(clippingArea.get_face_set(i)));
	}
	create_scene();
	myTranslatef(-eye[0],-eye[1],-eye[2]);

	for(int i=0;i<sceneData.size();i++){
		polygon* poly=sceneData.at(i);
		for(int j=0;j<poly->get_num_faces();j++){
			polygonClipping(poly->get_face_set(j));
		}
	}


	normalized_transformation((d3*width)/d1,(d3*height)/d1,d1,d2,d3);
	//perspective_transformation(d3);
	//perspective_projection(d3);

}



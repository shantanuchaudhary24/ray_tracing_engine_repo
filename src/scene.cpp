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
#include "../include/illumination.h"

using namespace std;
extern std::vector<polygon*> sceneData;
extern polygon clippingArea;
extern std::vector<float*> clipping_plane_eq;
extern float* viewingCordMatrix;
extern float* inverseviewingCordMatrix;
extern GLuint texName;

float* matInverse;
float* matTranspose;
float* mat;
bool isDistort=true;

/* Function for creating a cube
 * */
polygon* create_cube(cube* src)
{
	float width=src->width;
	float height=src->height;
	float depth=src->depth;
	RGB_value color = color_comp(src->color->R_value,src->color->G_value,src->color->B_value);

		vertex face1[] = {
							vertex(width,height,0),
							vertex(-width,height,0),
							vertex(-width,-height,0),
							vertex(width,-height,0),
						};

		vertex face2[] = {
							vertex(width,height,-depth),
							vertex(-width,height,-depth),
							vertex(-width,-height,-depth),
							vertex(width,-height,-depth),
						};

		vertex face3[] = {
							vertex(width,height,0),
							vertex(width,height,-depth),
							vertex(width,-height,-depth),
							vertex(width,-height,0),
						};
		vertex face4[] = {
							vertex(width,height,0),
							vertex(width,height,-depth),
							vertex(-width,height,-depth),
							vertex(-width,height,0),
						};
		vertex face5[] = {
							vertex(-width,height,0),
							vertex(-width,height,-depth),
							vertex(-width,-height,-depth),
							vertex(-width,-height,0),
						};
		vertex face6[] = {
							vertex(width,-height,0),
							vertex(width,-height,-depth),
							vertex(-width,-height,-depth),
							vertex(-width,-height,0),
						};
		polygon* poly = (polygon*)malloc(sizeof(polygon));
		poly->add_face(4,face1,&color);
		poly->add_face(4,face2,&color);
		poly->add_face(4,face3,&color);
		poly->add_face(4,face4,&color);
		poly->add_face(4,face5,&color);
		poly->add_face(4,face6,&color);
		return poly;

}

void create_scene(float* eye, config* ptr ){
//	RGB_value color1 = color_comp(1.0f,0.0f,0.0f);
//
//	float width=0.68,height=0.68,depth=0.68;
//	vertex centre=vertex(0,0,3.5);
//		vertex face1[] = {
//							vertex(width,height,0),
//							vertex(-width,height,0),
//							vertex(-width,-height,0),
//							vertex(width,-height,0),
//						};
//	RGB_value color2 = color_comp(1.0f,1.0f,0.0f);
//		vertex face2[] = {
//							vertex(width,height,-depth),
//							vertex(-width,height,-depth),
//							vertex(-width,-height,-depth),
//							vertex(width,-height,-depth),
//						};
	RGB_value color3 = color_comp(1.0f,0.0f,1.0f);
//		vertex face3[] = {
//							vertex(width,height,0),
//							vertex(width,height,-depth),
//							vertex(width,-height,-depth),
//							vertex(width,-height,0),
//						};
//	RGB_value color4 = color_comp(0.0f,1.0f,1.0f);
//		vertex face4[] = {
//							vertex(width,height,0),
//							vertex(width,height,-depth),
//							vertex(-width,height,-depth),
//							vertex(-width,height,0),
//						};
//	RGB_value color5 = color_comp(0.0f,1.0f,0.5f);
//		vertex face5[] = {
//							vertex(-width,height,0),
//							vertex(-width,height,-depth),
//							vertex(-width,-height,-depth),
//							vertex(-width,-height,0),
//						};
//	RGB_value color6 = color_comp(1.0f,0.0f,0.5f);
//		vertex face6[] = {
//							vertex(width,-height,0),
//							vertex(width,-height,-depth),
//							vertex(-width,-height,-depth),
//							vertex(-width,-height,0),
//						};
//		polygon* poly = (polygon*)malloc(sizeof(polygon));
//		poly->add_face(4,face1,&color2);
//		poly->add_face(4,face2,&color2);
//		poly->add_face(4,face3,&color2);
//		poly->add_face(4,face4,&color2);
//		poly->add_face(4,face5,&color2);
//		poly->add_face(4,face6,&color2);
		int i=0;
		polygon *poly;
		for(i=0;i<ptr->cube_array.size();i++)
		{
			poly = create_cube(ptr->cube_array.at(i) );
			myTranslatef(-eye[0],-eye[1],-eye[2],poly);
			myTranslatef(ptr->cube_array.at(i)->center->x_pos,ptr->cube_array.at(i)->center->y_pos,ptr->cube_array.at(i)->center->z_pos,poly);
			myRotatef(-30,1,0,0,poly);
			myRotatef(-30,0,1,0,poly);
			sceneData.push_back(poly);
		}



	RGB_value color7 = color_comp(0.0f,0.0f,1.0f);
		vertex face7[] = {
							vertex(1.5f,1.5f,-4.5f),
							vertex(-1.5f,-1.5f,-4.5f),
							vertex(-1.5f,1.5f,-3.2f),
						};

		polygon* poly2 = (polygon*)malloc(sizeof(polygon));
		poly2->add_face(3,face7,&color7);
		myTranslatef(-eye[0],-eye[1],-eye[2],poly2);
		//sceneData.push_back(poly2);

		vertex face8[] = {
							vertex(2,-2,-3.5f),
							vertex(2,-1,-5.5f),
							vertex(-2,-1,-5.5f),
							vertex(-2,-2,-3.5f),
						};
		polygon* poly3 = (polygon*)malloc(sizeof(polygon));
		poly3->add_face(4,face8,&color3);
		myTranslatef(-eye[0],-eye[1],-eye[2],poly3);
		sceneData.push_back(poly3);

}

void DrawLight(vector<light*> array)
{

	glPointSize(5);
	glBegin(GL_POINTS);
	for(int i=0;i<array.size();i++){
		vertex* point=array.at(i)->position;
		glVertex3f(point->x_pos,point->y_pos,point->z_pos);
	}
	glEnd();
}

void DrawSphere(vector<sphere*> array)
{

	glScalef(2,1,1);
	for(int i=0;i<array.size();i++){
		sphere* sphere1=array.at(i);
		glColor3f(sphere1->color->R_value,sphere1->color->G_value,sphere1->color->B_value);
		glTranslatef(sphere1->center->x_pos,sphere1->center->y_pos,sphere1->center->z_pos);
		glutSolidSphere(sphere1->radius,100,100);
		glTranslatef(-sphere1->center->x_pos,-sphere1->center->y_pos,-sphere1->center->z_pos);
	}
	glScalef(0.5,1,1);
}

float intersection_with_plane(Ray* ray, config* config_ptr,float* color,vertex* intersectionPoint,bool onlyfirst){

	float distancePlane=100000;
	float* frontPlane=clipping_plane_eq.at(0);
	vertex* normalpoint=(vertex*)malloc(sizeof(vertex));

	for(int m=0;m<sceneData.size();m++)
	{
		polygon* poly=sceneData.at(m);
		for (int q=0;q<poly->get_num_faces();q++)
		{
			face_info* face=poly->get_face_set(q);
			float* plane_eq=plane_equation(face);
			vertex* temp=findIntersection(plane_eq,ray);

			if(temp!=NULL)
			{
				float currdist=distanceFromPlane(frontPlane,temp);
				if(isOnPlane(temp,face) && currdist<distancePlane)
				{
					if(onlyfirst)
					{
						free(temp);
						free(normalpoint);
						return -1;
					}

					distancePlane=currdist;
					memcpy(intersectionPoint,temp,sizeof(vertex));
					normalpoint->x_pos=plane_eq[0];
					normalpoint->y_pos=plane_eq[1];
					normalpoint->z_pos=plane_eq[2];
					//printf("intersectionPoint with plane: %f %f %f \n",intersectionPoint->x_pos,intersectionPoint->y_pos,intersectionPoint->z_pos);

					RGB_value final_color = scene_illumination(normalpoint,intersectionPoint, ray->startPoint, face->face_color, config_ptr);
					color[0] = 255*final_color.R_value;
					color[1] = 255*final_color.G_value;
					color[2] = 255*final_color.B_value;

				}
			}
			free(temp);
		}
	}
	free(normalpoint);
	return distancePlane;
}

float intersection_with_sphere(Ray* ray, config* config_ptr,float* color,vertex* intersectionPoint,float distancePlane,bool onlyfirst){

	float* frontPlane=clipping_plane_eq.at(0);
	vertex* normalpoint=(vertex*)malloc(sizeof(vertex));

	for(int i=0;i<config_ptr->sphere_array.size();i++)
	{
		sphere* sphere1=config_ptr->sphere_array.at(i);
		vertex* R0=ray->startPoint;
		vertex* Rd=ray->direction;

		if(isDistort)
			matrix_mult(R0,matInverse);

		float B=2*(Rd->x_pos*(R0->x_pos-sphere1->center->x_pos)+Rd->y_pos*(R0->y_pos-sphere1->center->y_pos)+Rd->z_pos*(R0->z_pos-sphere1->center->z_pos));
		float C= (R0->x_pos-sphere1->center->x_pos)*(R0->x_pos-sphere1->center->x_pos)+
				(R0->y_pos-sphere1->center->y_pos)*(R0->y_pos-sphere1->center->y_pos)+
				(R0->z_pos-sphere1->center->z_pos)*(R0->z_pos-sphere1->center->z_pos)-sphere1->radius*sphere1->radius;

		float D=B*B-4*C;
		if(D>=0)
		{
			float t0= (-B+sqrt(D))/2;
			float t1= (-B-sqrt(D))/2;
			float t;
			if(t0<0){
				if(t1>=0)
					t=t1;
				else
					t=0;
			}
			else{
				if(t1>=0)
					t=t0>t1?t1:t0;
				else
					t=t0;
			}

			vertex* temp=(vertex*)malloc(sizeof(vertex));
			temp->x_pos=R0->x_pos+Rd->x_pos*t;
			temp->y_pos=R0->y_pos+Rd->y_pos*t;
			temp->z_pos=R0->z_pos+Rd->z_pos*t;
			float currdist=distanceFromPlane(frontPlane,temp);
			if(t!=0 && currdist<distancePlane)
			{

				if(onlyfirst)
				{
					free(temp);
					free(normalpoint);
					return -1;
				}

				distancePlane=currdist;
				if(isDistort)
				matrix_mult(temp,matInverse);
				//intersectionpoint=initialintersectionpoint*M;
				memcpy(intersectionPoint,temp,sizeof(vertex));
				//printf("intersectionPoint with sphere: %f %f %f \n",intersectionPoint->x_pos,intersectionPoint->y_pos,intersectionPoint->z_pos);

				normalpoint->x_pos=(intersectionPoint->x_pos-sphere1->center->x_pos)/sphere1->radius;
				normalpoint->y_pos=(intersectionPoint->y_pos-sphere1->center->y_pos)/sphere1->radius;
				normalpoint->z_pos=(intersectionPoint->z_pos-sphere1->center->z_pos)/sphere1->radius;
				// normal= initialnormal*(Transpose(Inverse(M)))
				if(isDistort)
				matrix_mult(normalpoint,matTranspose);
				unitVector(normalpoint);

				RGB_value final_color = scene_illumination(normalpoint,intersectionPoint, ray->startPoint, sphere1->color, config_ptr);

				color[0] = 255*final_color.R_value;
				color[1] = 255*final_color.G_value;
				color[2] = 255*final_color.B_value;

			}
			free(temp);
		}
	}
	free(normalpoint);
	return 1;
}
float* projection(Ray* ray, config* config_ptr)
{
	float* color=(float*)malloc(3*sizeof(float));
	color[0]=color[1]=color[2]=0;
	vertex* intersectionPoint=(vertex*)malloc(sizeof(vertex));
	float currentdist=intersection_with_plane(ray,config_ptr,color,intersectionPoint,false);

	if(isDistort){
		matrix_mult(ray->direction,matInverse);
		matrix_mult(ray->startPoint,matInverse);
	}

	intersection_with_sphere(ray,config_ptr,color,intersectionPoint,currentdist,false);
/*
	float a=0;
	for(int i=0;i<config_ptr->light_source.size();i++)
	{
		light* source=config_ptr->light_source.at(i);
		ray->startPoint=intersectionPoint;
		ray->direction=unitVector(intersectionPoint,source->position);
		float a=intersection_with_plane(ray,config_ptr,color,intersectionPoint,true);
		if(a==-1)
			continue;
		matrix_mult(ray->direction,matInverse);
		matrix_mult(ray->startPoint,matInverse);
		a=intersection_with_sphere(ray,config_ptr,color,intersectionPoint,10000,true);
	}

	if(a==-1)
	{
		printf("shadow point");
		print_vertex(intersectionPoint);
		color[0]=color[1]=color[2]=0;
	}*/

	return color;
}

float* sampling(float pixel[],int d2,float eye[], config* config_ptr){
		vertex curRay=vertex(pixel[0],pixel[1],pixel[2]);
		vertex backRay=vertex(curRay.x_pos+d2*(curRay.x_pos-eye[0]),
							curRay.y_pos+d2*(curRay.y_pos-eye[1]),
							curRay.z_pos+d2*(curRay.z_pos-eye[2]));

		Ray* ray=(Ray*)malloc(sizeof(Ray));
		ray->startPoint=&curRay;
		ray->direction=unitVector(&curRay,&backRay);
		float* color=projection(ray,config_ptr);
		free(ray);
		return color;
}

float* supersampling(float pixel[], int d2, float eye[],float eyeside[],float eyeup[],float width,float height,int N, config* config_ptr)
{

	float* pixelcolor=(float*)malloc(3*sizeof(float));
	pixelcolor[0]=pixelcolor[1]=pixelcolor[2]=0;
	vertex* curRay=(vertex*)malloc(sizeof(vertex));
	vertex* backRay=(vertex*)malloc(sizeof(vertex));
	int sampleSize=3;
	for(int m=0;m<sampleSize;m++){
		for(int n=0;n<sampleSize;n++){

			int r=rand()%100;
			float random=(float)r/100.0f;
			float basewidth=width/(sampleSize*N);
			float tempwidth=random*basewidth;
			r=rand()%100;
			random=(float)r/100.0f;
			float baseheight=height/(sampleSize*N);
			float tempheight=random*baseheight;

			curRay->x_pos=pixel[0]+(m*basewidth+tempwidth)*eyeside[0]-(n*baseheight+tempheight)*eyeup[0];
			curRay->y_pos=pixel[1]+(m*basewidth+tempwidth)*eyeside[1]-(n*baseheight+tempheight)*eyeup[1];
			curRay->z_pos=pixel[2]+(m*basewidth+tempwidth)*eyeside[2]-(n*baseheight+tempheight)*eyeup[2];

			backRay->x_pos=curRay->x_pos+d2*(curRay->x_pos-eye[0]);
			backRay->y_pos=curRay->y_pos+d2*(curRay->y_pos-eye[1]);
			backRay->z_pos=curRay->z_pos+d2*(curRay->z_pos-eye[2]);

			Ray* ray=(Ray*)malloc(sizeof(Ray));
			ray->startPoint=curRay;
			ray->direction=unitVector(curRay,backRay);
			float* color=projection(ray, config_ptr);
			for(int k=0;k<3;k++)
				pixelcolor[k]+=color[k];
			free(color);
			free(ray);
		}
	}

	free(curRay);
	free(backRay);
	for(int k=0;k<3;k++)
		pixelcolor[k]=pixelcolor[k]/(sampleSize*sampleSize);

	return pixelcolor;
}
/*
 * Shadow: find intersection between light and intersectPoint : if intersect then dont consider that light component
 * instructions
 * find intersection with objects
 * if ray doesn't intersect with any object, check intersection with frustrum(treat frustrum as a close box)
 * find reflection ray and refracted ray
 * recursively call this function on both reflected and transmitted ray
*/

void recursive_ray_tracing(){

}
void init(config *ptr){

	float eye[]={ptr->eye_pos[0],ptr->eye_pos[1],ptr->eye_pos[2]};
	float eyeup[]={ptr->eye_up[0],ptr->eye_up[1],ptr->eye_up[2]};
	float eyeside[]={ptr->eye_side[0],ptr->eye_side[1],ptr->eye_side[2]};
	float eyenormal[]={ptr->eye_normal[0],ptr->eye_normal[1],ptr->eye_normal[2]};
	float d1=ptr->frontplane_distance;		//distance of front plane from eye
	float d2=ptr->backplane_distance;		//distance of back plane from eye
	float d3=ptr->viewplane_distance;		//distance of view plane from eye
	float width=ptr->frontplane_width;		//width and height of front plane
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

	viewingCordMatrix=(float*)malloc(16*sizeof(float));
	memcpy(viewingCordMatrix,Matrix,16*sizeof(float));

	inverseviewingCordMatrix=(float*)malloc(16*sizeof(float));
	InverseMatrix(viewingCordMatrix,inverseviewingCordMatrix);

	float* frustrum=create_frustrum(eye,eyenormal,eyeup,eyeside,d1,d2,width,height);

		RGB_value color = color_comp(0.3f,1.0f,0.1f);
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
				//printf("frustrum i=%d j=%d vertices=%f %f %f\n",i,j,verts[j].x_pos,verts[j].y_pos,verts[j].z_pos);
			}

			clippingArea.add_face(4,verts,&color);
			clipping_plane_eq.push_back(plane_equation(clippingArea.get_face_set(i)));
		}

		/*for(int i=0;i<sceneData.size();i++){
				polygon* poly=sceneData.at(i);
				for(int j=0;j<poly->get_num_faces();j++){
					polygonClipping(poly->get_face_set(j));
				}
			}*/

	create_scene(&eye[0], ptr);

	for(int i=0;i<ptr->sphere_array.size();i++)
	{
		sphere* sphere1=ptr->sphere_array.at(i);
		sphere1->center->x_pos+=eye[0];
		sphere1->center->y_pos+=eye[1];
		sphere1->center->z_pos+=eye[2];
	}

	float leftTopCoord[3];		//top left coordinate of front plane

	float Sneg[3]={height*eyeup[0]-width*eyeside[0],height*eyeup[1]-width*eyeside[1],height*eyeup[2]-width*eyeside[2]};
	for(int i=0;i<3;i++)
		leftTopCoord[i]=eye[i]+eyenormal[i]*d1+Sneg[i];

	int N=250;
	float pixel[3];
	GLubyte texture[N+1][N+1][4];

	float mattemp[] = {2,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1.0};
	mat = mattemp;
	matInverse=(float*)malloc(16*sizeof(float));
	InverseMatrix(mat,matInverse);
	matTranspose=(float*)malloc(16*sizeof(float));
	transpose_matrix(matInverse,matTranspose);

	for(int i=0;i<N+1;i++){
		for(int j=0;j<N+1;j++){
			for(int k=0;k<3;k++){
				pixel[k]=leftTopCoord[k]+(j*2*width*eyeside[k])/N-(i*2*height*eyeup[k])/N;
			}

			//float* pixelcolor=supersampling(pixel,d2,eye,eyeside,eyeup,2*width,2*height,N, ptr);
			float* pixelcolor=sampling(pixel,d2,eye,ptr);
			for(int k=0;k<3;k++)
				texture[i][j][k]=pixelcolor[k];
			texture[i][j][3]=255;
			free(pixelcolor);
		}
	}

	free(matInverse);
	free(matTranspose);

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				   GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				   GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, N+1,
				N+1, 0, GL_RGBA, GL_UNSIGNED_BYTE,
				texture);

	//normalized_transformation((d3*width)/d1,(d3*height)/d1,d1,d2,d3);
	//perspective_transformation(d3);
	//perspective_projection(d3);
}

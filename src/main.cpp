#include "../include/headers.h"
#include "../include/macros.h"
#include "../include/structs.h"
#include "../include/polygon.h"
#include "../include/transformations.h"

using namespace std;

vector<polygon*> sceneData;
polygon clippingArea;
vector<float*> clipping_plane_eq;
float* viewingCordMatrix;
float* inverseviewingCordMatrix;

float angle_x = 0;
float angle_y = 0;
float angle_z = 0;
float scale_factor = 1;


//Inverse of matrix
void InverseMatrix(float* m, float* out)
{
    float inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        out[i] = inv[i] * det;

}

void matrix_mult(vertex* verts,const float* mat){

	float initial_coordinate[]={verts->x_pos,verts->y_pos,verts->z_pos,1.0f};
	float final_coordinate[]={0,0,0,0};

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			final_coordinate[i]+=initial_coordinate[j]*mat[4*j+i];

	for(int i=0;i<3;i++)
		final_coordinate[i]=final_coordinate[i]/final_coordinate[3];

	verts->x_pos=final_coordinate[0];
	verts->y_pos=final_coordinate[1];
	verts->z_pos=final_coordinate[2];

}

void matrix_multsaveZ(vertex* verts,const float* mat){

	float initial_coordinate[]={verts->x_pos,verts->y_pos,verts->z_pos,1.0f};
		float final_coordinate[]={0,0,0,0};

		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				final_coordinate[i]+=initial_coordinate[j]*mat[4*j+i];

		for(int i=0;i<3;i++)
			final_coordinate[i]=final_coordinate[i]/final_coordinate[3];

		verts->x_pos=final_coordinate[0];
		verts->y_pos=final_coordinate[1];
		//verts.z_pos=final_coordinate[2];

}

void transformation(const float* mat){

	for(int i=0;i<sceneData.size();i++)
	{
		polygon* poly=sceneData.at(i);
		for(int j=0;j<poly->get_num_faces();j++)
		{
			face_info* faces=poly->get_face_set(j);
			vertex* verts=faces->vertex_set;
			for(int k=0;k<faces->number_of_vertices;k++)
			{
				matrix_mult(verts+k,mat);
			}
		}
	}
}

void transformationsaveZ(const float* mat){

	for(int i=0;i<sceneData.size();i++)
		{
			polygon* poly=sceneData.at(i);
			for(int j=0;j<poly->get_num_faces();j++)
			{
				face_info* faces=poly->get_face_set(j);
				vertex* verts=faces->vertex_set;
				for(int k=0;k<faces->number_of_vertices;k++)
				{
					matrix_multsaveZ(verts+k,mat);
				}
			}
		}
}

void transformationOnFrustrum(const float* mat){

		for(int j=0;j<clippingArea.get_num_faces();j++)
		{
			face_info* faces=clippingArea.get_face_set(j);
			vertex* verts=faces->vertex_set;
			for(int k=0;k<faces->number_of_vertices;k++)
			{
				matrix_mult(verts+k,mat);
			}
		}
}
void transformationOnFrustrumsaveZ(const float* mat){

		for(int j=0;j<clippingArea.get_num_faces();j++)
		{
			face_info* faces=clippingArea.get_face_set(j);
			vertex* verts=faces->vertex_set;
			for(int k=0;k<faces->number_of_vertices;k++)
			{
				matrix_multsaveZ(verts+k,mat);
			}
		}
}
void myTranslatef( float x, float y, float z){
    const float mat[] = {1.0,0,0,0,0,1.0,0,0,0,0,1.0,0,x,y,z,1.0};
    transformation(viewingCordMatrix);
    transformation(&mat[0]);
    transformation(inverseviewingCordMatrix);
    //glMultMatrixf(&mat[0]);
    return ;
}

void myScalef(float sx, float sy, float sz){
    const float mat[] = {sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1.0};
    transformation(viewingCordMatrix);
    transformation(&mat[0]);
    transformation(inverseviewingCordMatrix);
    //glMultMatrixf(&mat[0]);
    return ;
}

void myRotatef(float theta,float px, float py, float pz){
    theta *= M_PI/180;
    float m[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    float l = sqrt(px*px + py*py + pz*pz);
    float cosa = cos(theta);
    float onec = 1-cosa;
    float sina = sin(theta);
    float ux = px/l;
    float uy = py/l;
    float uz = pz/l;
    m[0] = ux*ux*onec + cosa;
    m[4] = ux*uy*onec - uz*sina;
    m[8] = ux*uz*onec + uy*sina;
    m[1] = ux*uy*onec + uz*sina;
    m[5] = uy*uy*onec + cosa;
    m[9] = uy*uz*onec - ux*sina;
    m[2] = ux*uz*onec - uy*sina;
    m[6] = uz*uy*onec + ux*sina;
    m[10] = uz*uz*onec + cosa;
    const float mat[] = {m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]};
    transformation(viewingCordMatrix);
    transformation(&mat[0]);
    transformation(inverseviewingCordMatrix);
    //glMultMatrixf(&mat[0]);
    return ;
}

void handleKeypressSpecial(int key, int x, int y ) {
//x and y are the current mouse coordinates
	switch (key) {
		case GLUT_KEY_UP:{
			angle_x += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_DOWN:{
			angle_x += -2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_LEFT:{
			angle_y += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_RIGHT:{
			angle_y += -2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_PAGE_UP:{
			angle_z += 2;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_PAGE_DOWN:{
			angle_z += -2;
			glutPostRedisplay();
			break;
		}

		case GLUT_KEY_HOME:{
			scale_factor += 0.05;
			glutPostRedisplay();
			break;
		}
		case GLUT_KEY_INSERT:{
			scale_factor += -0.05;
			glutPostRedisplay();
			break;
		}

	}
}


float* create_frustrum(float* eye,float* eyenormal,float* eyeup,float* eyeside,float d1,float d2,float width,float height){
	
	float* centre = (float*)malloc(3*sizeof(float));
		centre[0]= eye[0]+d1*eyenormal[0];
		centre[1]= eye[1]+d1*eyenormal[1];
		centre[2]= eye[2]+d1*eyenormal[2];

	float* frustrum = (float*)malloc(8*3*sizeof(float));

	//float diagonal=sqrt(width*width+height*height);
	float S[3]={height*eyeup[0]+width*eyeside[0],height*eyeup[1]+width*eyeside[1],height*eyeup[2]+width*eyeside[2]};
	float Sneg[3]={height*eyeup[0]-width*eyeside[0],height*eyeup[1]-width*eyeside[1],height*eyeup[2]-width*eyeside[2]};
	
	frustrum[0]=centre[0]+S[0];		//first point
	frustrum[1]=centre[1]+S[1];
	frustrum[2]=centre[2]+S[2];

	frustrum[3*1+0]=centre[0]+Sneg[0];		//second point
	frustrum[3*1+1]=centre[1]+Sneg[1];
	frustrum[3*1+2]=centre[2]+Sneg[2];

	frustrum[3*2+0]=centre[0]-S[0];		//third point
	frustrum[3*2+1]=centre[1]-S[1];
	frustrum[3*2+2]=centre[2]-S[2];

	frustrum[3*3+0]=centre[0]-Sneg[0];		//fourth point
	frustrum[3*3+1]=centre[1]-Sneg[1];
	frustrum[3*3+2]=centre[2]-Sneg[2];
	
	//shift centre to back plane
	centre[0]=eye[0]+d2*eyenormal[0];
	centre[1]=eye[1]+d2*eyenormal[1];
	centre[2]=eye[2]+d2*eyenormal[2];


	float width2=(d2*width)/d1;
	float height2=(d2*height)/d1;

	float S2[3]={height2*eyeup[0]+width2*eyeside[0],height2*eyeup[1]+width2*eyeside[1],height2*eyeup[2]+width2*eyeside[2]};
	float Sneg2[3]={height2*eyeup[0]-width2*eyeside[0],height2*eyeup[1]-width2*eyeside[1],height2*eyeup[2]-width2*eyeside[2]};

	frustrum[3*4+0]=centre[0]+S2[0];		//first point
	frustrum[3*4+1]=centre[1]+S2[1];
	frustrum[3*4+2]=centre[2]+S2[2];

	frustrum[3*5+0]=centre[0]+Sneg2[0];		//second point
	frustrum[3*5+1]=centre[1]+Sneg2[1];
	frustrum[3*5+2]=centre[2]+Sneg2[2];

	frustrum[3*6+0]=centre[0]-S2[0];		//third point
	frustrum[3*6+1]=centre[1]-S2[1];
	frustrum[3*6+2]=centre[2]-S2[2];

	frustrum[3*7+0]=centre[0]-Sneg2[0];		//fourth point
	frustrum[3*7+1]=centre[1]-Sneg2[1];
	frustrum[3*7+2]=centre[2]-Sneg2[2];
	
	//for(int i=0;i<8;i++)
		//printf("frustrum point %d = %f %f %f\n",i+1,frustrum[3*i],frustrum[3*i+1],frustrum[3*i+2]);
	return frustrum;
}

float* plane_equation(face_info* face){
	vertex* verts = face->vertex_set;
	float u[3];
	float v[3];
	
		u[0]=verts[2].x_pos-verts[0].x_pos;
		u[1]=verts[2].y_pos-verts[0].y_pos;
		u[2]=verts[2].z_pos-verts[0].z_pos;
		v[0]=verts[2].x_pos-verts[1].x_pos;
		v[1]=verts[2].y_pos-verts[1].y_pos;
		v[2]=verts[2].z_pos-verts[1].z_pos;

	float* eq = (float*)malloc(4*sizeof(float));
	eq[0]=u[1]*v[2]-u[2]*v[1];
	eq[1]=u[2]*v[0]-u[0]*v[2];
	eq[2]=u[0]*v[1]-u[1]*v[0];
	eq[3]=-eq[0]*verts[0].x_pos-eq[1]*verts[0].y_pos-eq[2]*verts[0].z_pos;
	
	return eq;
}

bool isInsidePlane(float* eq_plane,vertex* point){

		if((eq_plane[0]*point->x_pos+eq_plane[1]*point->y_pos+eq_plane[2]*point->z_pos+eq_plane[3])>=0)
			return true;
		else
			return false;
}

vertex* findIntersection(float* eq_plane,vertex* point1,vertex* point2){

	float normalize=sqrtf((point1->x_pos-point2->x_pos)*(point1->x_pos-point2->x_pos)+(point1->y_pos-point2->y_pos)*(point1->y_pos-point2->y_pos)+(point1->z_pos-point2->z_pos)*(point1->z_pos-point2->z_pos));
	vertex* unitvect =new vertex_pt((point1->x_pos-point2->x_pos)/normalize,(point1->y_pos-point2->y_pos)/normalize,(point1->z_pos-point2->z_pos)/normalize);

	float a= eq_plane[0]*unitvect->x_pos+eq_plane[1]*unitvect->y_pos+eq_plane[2]*unitvect->z_pos;
	float b= eq_plane[0]*point1->x_pos+eq_plane[1]*point1->y_pos+eq_plane[2]*point1->z_pos+eq_plane[3];

	if(abs(a)>0.00001)
	{
		vertex* intersectionPoint = (vertex*)malloc(sizeof(vertex));
		intersectionPoint->x_pos = point1->x_pos-(b*unitvect->x_pos)/a;
		intersectionPoint->y_pos = point1->y_pos-(b*unitvect->y_pos)/a;
		intersectionPoint->z_pos = point1->z_pos-(b*unitvect->z_pos)/a;
		//printf("intersection point %f %f %f \n",intersectionPoint->x_pos,intersectionPoint->y_pos,intersectionPoint->z_pos);
		return intersectionPoint;
	}
	else
	{
		vertex* intersectionPoint = (vertex*)malloc(sizeof(vertex));
		intersectionPoint->x_pos = point2->x_pos;
		intersectionPoint->y_pos = point2->y_pos;
		intersectionPoint->z_pos = point2->z_pos;
		//printf("intersection point %f %f %f \n",intersectionPoint->x_pos,intersectionPoint->y_pos,intersectionPoint->z_pos);
		return intersectionPoint;
	}
}
void polygonClipping(face_info* face){
	int i=0;

	vertex* verts=face->vertex_set;
	int count=face->number_of_vertices;
	vector<vertex*> CvTable;
	vector<vertex*> CvTabletemp;

	for(i=0;i<count;i++){
		vertex* point=verts+i;
		CvTable.push_back(point);
	}


	for(i=0;i<clipping_plane_eq.size();i++)
	{
		float* eq_plane=clipping_plane_eq.at(i);
		//printf("equation of plane %d  %f %f %f %f \n",i,eq_plane[0],eq_plane[1],eq_plane[2],eq_plane[3]);

		int j;
		for(j=0;j<CvTable.size();j++)
		{
			vertex* point1=CvTable.at(j);
			vertex* point2=CvTable.at((j+1)%CvTable.size());
			int k;
			if(isInsidePlane(eq_plane,point1))								//if v1 is inside
			{
				if(isInsidePlane(eq_plane,point2))		//if v2 is inside
				{
					CvTabletemp.push_back(point2);
				}
				else															//if v2 is outside
				{
					//find intersection point and put in cvtable
					CvTabletemp.push_back(findIntersection(eq_plane,point1,point2));
				}
			}
			else																//if v1 is outside
			{
				if(isInsidePlane(eq_plane,point2))			//if v2 is inside
				{
					//find intersection point and put in cvtable
					CvTabletemp.push_back(findIntersection(eq_plane,point1,point2));
					CvTabletemp.push_back(point2);
				}
			}
		}

		CvTable.clear();
		int k;
		for(k=0;k<CvTabletemp.size();k++){
			CvTable.push_back(CvTabletemp.at(k));
		}
		CvTabletemp.clear();
	}


	vertex* newverts= (vertex*)malloc(CvTable.size()*sizeof(vertex));
	for(i=0;i<CvTable.size();i++){
		newverts[i]=CvTable.at(i)[0];
	}

	face->vertex_set=newverts;
	face->number_of_vertices=CvTable.size();
}

void perspective_transformation(float distFromViewingPlane){
	//TODO
	const float mat[]={1,0,0,0,0,1,0,0,0,0,1,1/distFromViewingPlane,0,0,0,1};

	transformation(viewingCordMatrix);
	transformationsaveZ(&mat[0]);
	transformation(inverseviewingCordMatrix);

	transformationOnFrustrum(viewingCordMatrix);
	transformationOnFrustrumsaveZ(&mat[0]);
	transformationOnFrustrum(inverseviewingCordMatrix);
}
void perspective_projection(float distFromViewingPlane){
	//TODO
	const float mat[]={1,0,0,0,0,1,0,0,0,0,0,1/distFromViewingPlane,0,0,0,1};
	transformation(viewingCordMatrix);
	transformation(&mat[0]);
	transformation(inverseviewingCordMatrix);

	transformationOnFrustrum(viewingCordMatrix);
	transformationOnFrustrum(&mat[0]);
	transformationOnFrustrum(inverseviewingCordMatrix);

}

void normalized_transformation(float width,float height,float near,float far,float distFromViewingPlane){

	perspective_transformation(distFromViewingPlane);

	const float mat[]={1/width,0,0,0,0,1/height,0,0,0,0,2/(far-near),0,0,0,-distFromViewingPlane,1};
	transformation(viewingCordMatrix);
	transformation(&mat[0]);
	transformation(inverseviewingCordMatrix);

	transformationOnFrustrum(viewingCordMatrix);
	transformationOnFrustrum(&mat[0]);
	transformationOnFrustrum(inverseviewingCordMatrix);

}

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

void init(void){

	float eye[]={0.0f,0.0f,-10.0f};
	float eyeup[]={0.0f,1.0f,0.0f};
	float eyeside[]={1.0f,0.0f,0.0f};
	float eyenormal[]={0.0f,0.0f,-1.0f};
	float d1=1;		//distance of front plane from eye
	float d2=3;		//distance of back plane from eye
	float d3=2;		//distance of view plane from eye
	float width=1;	//width and height of front plane
	float height=1;
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

void reshape (int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10,10,-10,10,-100,100);
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void){  
	
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity(); 

	glTranslatef(0,0,-10);
	glScalef(scale_factor,scale_factor,scale_factor);
	glRotatef(angle_x, 1, 0, 0);
	glRotatef(angle_y, 0, 1, 0);
	glRotatef(angle_z, 0, 0, 1);
	glTranslatef(0,0,10);

	clippingArea.draw();
	for(int i=0;i<sceneData.size();i++)
		sceneData.at(i)->draw();

    glFlush();
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Polygon Clipping!");
    glutSpecialFunc(handleKeypressSpecial);
    init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);    
	glutMainLoop();
    return 0;
}

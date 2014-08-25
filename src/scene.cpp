/*
 * scene.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */
#include "../include/headers.h"
#include "../include/macros.h"


/* This function is used to create the various 3D shapes in the scene.
 * The position of the various objects within the scene are fixed.
 * */
void default_scene(void)
{

	glClearColor(0, 0, 0, 1); // Clear the background of our window
	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	myTranslatef(0, 0, -10); // Push eveything 5 units back into the scene, otherwise we won't see the primitive

	return ;
}





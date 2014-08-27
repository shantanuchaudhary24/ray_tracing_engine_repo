/*
 * scene.h
 * Function calls corresponding to the creation of scene objects
 *  Created on: Aug 26, 2014
 *      Author: shantanu
 */

#ifndef SCENE_H_
#define SCENE_H_

polygon generate_plane(float x, float y, float z, float l, float b, float x_distance, float y_distance, float z_distance);
polygon generate_cuboid(float x, float y, float z, float l, float b, float h, float x_distance, float y_distance, float z_distance);

#endif /* SCENE_H_ */

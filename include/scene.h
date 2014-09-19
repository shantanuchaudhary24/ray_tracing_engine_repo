/*
 * scene.h
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */

#ifndef SCENE_H_
#define SCENE_H_

polygon* create_cube(cube* src);
void init(config *ptr);
void DrawSphere(std::vector<sphere*> spheres);
void DrawLight(std::vector<light*> lightSources);

#endif /* SCENE_H_ */

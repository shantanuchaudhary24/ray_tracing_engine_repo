/*
 * clipping.h
 * Function definitions corresponding to clipping operation
 *  Created on: Aug 27, 2014
 *      Author: shantanu
 */

#ifndef CLIPPING_H_
#define CLIPPING_H_

void polygonClipping(face_info* polygon);
float* plane_equation(face_info* face);


#endif /* CLIPPING_H_ */

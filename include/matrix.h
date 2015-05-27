/*
 * matrix.h
 *
 *  Created on: Sep 5, 2014
 *      Author: shantanu
 */

#ifndef MATRIX_H_
#define MATRIX_H_

void InverseMatrix(float* m, float* out);
void matrix_mult(vertex* verts,const float* mat);
void matrix_multsaveZ(vertex* verts,const float* mat);
void transpose_matrix(float* mat,float* transpose);


#endif /* MATRIX_H_ */

#ifndef MATRIX_PROPERTIES_H
#define MATRIX_PROPERTIES_H

#include "matrixUtils.h"

int control_equal_dimensions(matrix_t*, matrix_t*);
int control_square_matrix(matrix_t*);
int control_lower_triangle_matrix(matrix_t*);
int control_upper_triangle_matrix(matrix_t*);
int control_diagonal_matrix(matrix_t*);
int control_identity_matrix(matrix_t*);
int control_multiplicable_matrix(matrix_t* t1, matrix_t* t2);



#endif
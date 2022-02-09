#ifndef MATRIX_MULT_H
#define MATRIX_MULT_H

#include "matrixUtils.h"
#include "properties.h"

matrix_t* product_matrix(matrix_t*, matrix_t*);
matrix_t* product_matrix_scalar(matrix_t*, float);

#endif
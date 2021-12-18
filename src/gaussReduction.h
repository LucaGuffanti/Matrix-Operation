#ifndef GAUSS_REDUCTION_H
#define GAUSS_REDUCTION_H

#include "matrixUtils.h"

matrix_t* multiply_row(matrix_t*, int, float);
matrix_t* sum_rows(matrix_t*, int, int);
matrix_t* order_rows(matrix_t*, int);
matrix_t* gauss_reduction(matrix_t*);
float* swap_rows(matrix_t*, int, int);
float* start_reduction(matrix_t*);
#endif
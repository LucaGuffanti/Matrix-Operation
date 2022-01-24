#ifndef GAUSS_REDUCTION_H
#define GAUSS_REDUCTION_H

#include "matrixUtils.h"

matrix_t* multiply_row(matrix_t*, int, float);
matrix_t* sum_rows(matrix_t*, int, int, int);
matrix_t* order_rows(matrix_t*, int, int);
matrix_t* swap_rows(matrix_t*, int, int);
matrix_t* reduce_ith(matrix_t*, int, int);
matrix_t* execute_reduction(matrix_t*);
matrix_t* square_gauss_reduction(matrix_t*);
matrix_t* gauss_simplify_matrix(matrix_t*);
#endif
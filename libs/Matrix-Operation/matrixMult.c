#include "matrixMult.h"
#include "stdlib.h"

matrix_t* product_matrix(matrix_t* m1, matrix_t* m2){
    int i, j, h, k;
    int rows, cols;
    int sum;
    matrix_t* prod;

    prod = NULL;
    if(control_multiplicable_matrix(m1, m2)){
        rows = m1->rows;
        cols = m2->cols;
        prod = init(rows, cols);
        if(control_identity_matrix(m1)){
            prod = m2;
        }else if(control_identity_matrix(m2)){
            prod = m1;
        }else{
            for(i = 0; i < rows; i++){
                for(j = 0; j < cols; j++){
                    for(h = 0, sum = 0; h < m1->cols; h++){
                        sum = sum + m1->m[i][h]*m2->m[h][j]; //not very good for cache purposes :(
                    }
                    prod->m[i][j] = sum;
                }
            }
        }
    }else{
        print_message("Error: matrices do not have the correct dimensions\n");
    }
    return prod;
}

matrix_t* product_matrix_scalar(matrix_t* mat, float val){
    int i;
    int j;

    int rows, cols;

    rows = mat->rows;
    cols = mat->cols;
    
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            mat->m[i][j] = val * mat->m[i][j];
        }
    }

    return mat;
}
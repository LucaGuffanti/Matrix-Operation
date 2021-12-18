#include "matrixSum.h"


matrix_t* sum_Matrices(matrix_t* m1, matrix_t* m2){
    matrix_t* sum;
    int i;
    int j;
    int rows, cols;

    sum = NULL;
    if(control_equal_dimensions(m1, m2)){
        rows = m1->rows;
        cols = m1->cols;

        sum = init(rows, cols);
        for(i = 0; i < rows; i++){
            for(j = 0; j < cols; j++){
                sum->m[i][j] = m1->m[i][j] + m2->m[i][j];
            } 
        }
    }else{
        print_message("ERROR: the dimensions of the matrices do not match.\n");
    }
    return sum;
}

matrix_t* sub_Matrices(matrix_t* m1, matrix_t* m2){
    matrix_t* sum;
    int i;
    int j;
    int rows, cols;

    sum = NULL;
    if(control_equal_dimensions(m1, m2)){
        rows = m1->rows;
        cols = m1->cols;

        sum = init(rows, cols);
        for(i = 0; i < rows; i++){
            for(j = 0; j < cols; j++){
                sum->m[i][j] = m1->m[i][j] - m2->m[i][j];
            } 
        }
    }else{
        print_message("ERROR: The dimensions of the matrices do not match.\n");
    }
    return sum;
}
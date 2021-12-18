#include "gaussReduction.h"

matrix_t* multiply_row(matrix_t* m1, int row, float val){
    int j;
    int cols;
    cols = m1->cols;
    for(j = 0; j < cols; j++){
        m1->m[row][j] = m1->m[row][j] * val;
    }
    return m1;
}
matrix_t* sum_rows(matrix_t* m1, int row1, int row2){
    /*add row1 and row2's elements and update row1.*/
    int j;
    int cols;
    cols = m1->cols;
    for(j = 0; j < cols; j++){
        m1->m[row1][j] = m1->m[row1][j] + m1->m[row2][j]; 
    }
    return m1;
}

matrix_t* order_rows(matrix_t* m1, int refCol){
    int i;
    int j;
    int rows, cols;

    rows = m1->rows;
    cols = m1->cols;
    
}
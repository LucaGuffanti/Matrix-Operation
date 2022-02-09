#include "gaussReduction.h"
#include "properties.h"

matrix_t* multiply_row(matrix_t* m1, int row, float val){
    int j;
    int cols;
    cols = m1->cols;
    for(j = 0; j < cols; j++){
        m1->m[row][j] = m1->m[row][j] * val;
    }
    return m1;
}
matrix_t* sum_rows(matrix_t* m1, int row1, int row2, int index){
    /*add row1 and row2's elements and update row2, in order to eliminate the j-th element in row 2.*/
    int j;
    int cols;
    float scalingFactor;
    cols = m1->cols;

    scalingFactor = (-1)*(m1->m[row1][index]/m1->m[row2][index]);
    m1 = multiply_row(m1, row2, scalingFactor);
    for(j = 0; j < cols; j++){
        m1->m[row2][j] = m1->m[row1][j] + m1->m[row2][j]; 
    }
    return m1;
}

matrix_t* swap_rows(matrix_t* m1, int row1, int row2){
    int j;
    int cols;
    float tmp;

    cols = m1->cols;
    for(j = 0; j < cols; j++){
        tmp = m1->m[row1][j];
        m1->m[row1][j] = m1->m[row2][j];
        m1->m[row2][j] = tmp;
    }
    return m1;
}

matrix_t* order_rows(matrix_t* m1, int x, int y){
    int i, j;
    int rows;
    int swapped;

    rows = m1->rows;
    if(m1->m[x][y] == 0){
        for(i = x, swapped = 0; i < rows && !swapped; i++){
            if(m1->m[i][y] != 0){
                swapped = 1;
                m1 = swap_rows(m1, x, i);
            }
        }
    }
    return m1;
}

matrix_t* reduce_ith(matrix_t* m1, int x, int y){
    int i;
    int rows;

    m1 = order_rows(m1, x, y);
    rows = m1->rows;
    for(i = x; i < rows; i++){
        if(m1->m[i][y] != 0){
            m1 = sum_rows(m1, x, i, y);
        }
    }
    return m1;
}

matrix_t* execute_reduction(matrix_t* m1){
    if(control_square_matrix(m1)){
        return square_gauss_reduction(m1);
    }
}

matrix_t* square_gauss_reduction(matrix_t* m1){
    int i, j;
    int rows, cols;
    
    rows = m1->rows;

    for(i = 0, j = 0; i < rows; i++, j++){
        m1 = reduce_ith(m1, i, j);
    }
    m1 = gauss_simplify_matrix(m1);
    return m1;
}

matrix_t* gauss_simplify_matrix(matrix_t* m1){
    int i, j;
    int reduced;
    int rows, cols;

    rows = m1->rows;
    cols = m1->cols;

    for(i = 0; i < rows; i++){
        for(j = 0, reduced = 0; j < cols && !reduced; j++){
            if(m1->m[i][j] != 0){
                reduced = 1;
                m1 = multiply_row(m1, i, 1/m1->m[i][j]);
            }
        }
    }
    return m1;
}


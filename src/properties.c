#include "properties.h"

int control_equal_dimensions(matrix_t* t1, matrix_t* t2){
    return (t1->rows == t2->rows) && (t1->cols == t2->cols); 
}

int control_square_matrix(matrix_t* t){
    return t->rows == t->cols;
}

int control_upper_triangle_matrix(matrix_t* t){
    int i;
    int j;
    int rows;
    int isUpperTriangle;

    isUpperTriangle = 0;
    if(control_square_matrix(t)){
        rows = t->rows;
        for(i = 0, isUpperTriangle = 1; isUpperTriangle && i < rows; i++){
            for(j = 0; isUpperTriangle && j < rows; j++){
                if(j < i && t->m[i][j] != 0){
                    isUpperTriangle = 0;
                }
                if(j == i && t->m[i][j] == 0){
                    isUpperTriangle = 0;
                }
            }
        }
    }
    return isUpperTriangle;
}

int control_lower_triangle_matrix(matrix_t* t){
    int i;
    int j;
    int rows;
    int isLowerTriangle;

    isLowerTriangle = 0;
    if(control_square_matrix(t)){
        rows = t->rows;
        for(i = 0, isLowerTriangle = 1; isLowerTriangle && i < rows; i++){
            for(j = 0; isLowerTriangle && j < rows; j++){
                if(j > i && t->m[i][j] != 0){
                    isLowerTriangle = 0;
                }
                if(j == i && t->m[i][j] == 0){
                    isLowerTriangle = 0;
                }
            }
        }
    }
    return isLowerTriangle;
}

int control_diagonal_matrix(matrix_t* t){
    return control_lower_triangle_matrix(t) && control_upper_triangle_matrix(t);
}

int control_identity_matrix(matrix_t* t){ 
    int i;
    int rows = t->rows;
    int isIdentity;

    isIdentity = 0;
    if(control_diagonal_matrix(t)){
        for(i = 0, isIdentity = 1; isIdentity && i < rows; i++){
            if(t->m[i][i] != 1){
                isIdentity = 0;
            }
        }
    }
    return isIdentity;
}

int control_multiplicable_matrix(matrix_t* t1, matrix_t* t2){
    return (t1->cols == t2->rows);
}

#include "matrixUtils.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

matrix_t* init(int rows, int cols){
    matrix_t* descriptor;
    int i;
    int stopAllocation;

    descriptor = NULL;

    descriptor = (matrix_t*)(malloc(sizeof(matrix_t)));
    if(descriptor != NULL){
        /*initialize the matrix with the given rows and cols. Set every element to 0*/
        descriptor->rows = rows;
        descriptor->cols = cols;

        descriptor->m = (float**)malloc(sizeof(float*) * rows);
        if(descriptor->m){
            for(i = 0, stopAllocation = 0; i < rows && !stopAllocation; i++){
                descriptor->m[i] = calloc(cols, sizeof(float));
                if(!descriptor->m){
                    stopAllocation = i;
                }
            }
            if(stopAllocation != 0){
                for(i = 0; i < stopAllocation; i++){
                    free(descriptor->m[i]);
                }
                free(descriptor->m);
                free(descriptor);
            }
        }
    }

    return descriptor;
}

matrix_t* init_square(int dim){
    matrix_t* descriptor;
    int i;
    int stopAllocation;

    descriptor = NULL;

    descriptor = (matrix_t*)(malloc(sizeof(matrix_t)));
    if(descriptor != NULL){
        /*initialize the matrix with the given rows and cols. Set every element to 0*/
        descriptor->rows = dim;
        descriptor->cols = dim;

        descriptor->m = (float**)malloc(sizeof(float*) * dim);
        if(descriptor->m){
            for(i = 0, stopAllocation = 0; i < dim && !stopAllocation; i++){
                descriptor->m[i] = calloc(dim, sizeof(float));
                if(!descriptor->m){
                    stopAllocation = i;
                }
            }
            if(stopAllocation != 0){
                for(i = 0; i < stopAllocation; i++){
                    free(descriptor->m[i]);
                }
                free(descriptor->m);
                free(descriptor);
            }
        }
    }

    return descriptor;
}

matrix_t* free_matrix(matrix_t* mat){
    int i;
    int rows;

    rows = mat->rows;
    for(i = 0; i < rows; i++){
        free(mat->m[i]);
    }
    free(mat->m);
    free(mat);

    return NULL;
}

matrix_t* user_insert_populate(matrix_t* mat){
    int i;
    int j;
    int rows, cols;
    rows = mat->rows;
    cols = mat->cols;

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            scanf("%f", &(mat->m[i][j]));
        }
    }
    return mat;
}

// Populate matrix with floats from a 2D integers buffer  
matrix_t* user_populate_from_buffer(matrix_t* mat, int *buffer){
    int i;
    int j;
    int k;
    int rows, cols;
    rows = mat->rows;
    cols = mat->cols;

    
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            mat->m[i][j] = (float)buffer[k];
            k++;
        }
    }
    return mat;
}
matrix_t* auto_populate(matrix_t* mat, int max){
    srand(time(NULL));
    int i;
    int j;
    int rows, cols;
    rows = mat->rows;
    cols = mat->cols;

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            mat->m[i][j] = rand()%max;
        }
    }
    return mat;
}

void print_matrix(matrix_t* mat){
    int i;
    int j;
    int rows, cols;
    rows = mat->rows;
    cols = mat->cols;

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%02.2f ", mat->m[i][j]);
        }
        puts("\n");
    }
    puts("\n\n");
}

void print_message(const char* msg){
    puts(msg);
}

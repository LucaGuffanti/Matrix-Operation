#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H



typedef struct _matrix{
    int rows;
    int cols;
    float** m;
} matrix_t;

matrix_t* init_square(int);
matrix_t* init(int, int);
matrix_t* free_matrix(matrix_t*);
matrix_t* user_insert_populate(matrix_t*);
void print_message(const char *);
matrix_t* auto_populate(matrix_t*, int);
//TODO: add scan from file
void print_matrix(matrix_t*);
#endif
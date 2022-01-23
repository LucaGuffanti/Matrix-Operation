#include "stdio.h"
#include "src/matrixUtils.h"
#include "src/matrixMult.h"
#include "src/gaussReduction.h"

int main(){
    matrix_t* m1;
    m1 = init_square(3);
    
    m1 = user_insert_populate(m1);
    print_matrix(m1);
    print_matrix(m1);
    free_matrix(m1);


    return 0;
}
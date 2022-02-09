#include "stdio.h"
#include "libs/Matrix-Operation/matrixUtils.h"
#include "libs/Matrix-Operation/matrixMult.h"
#include "libs/Matrix-Operation/gaussReduction.h"
#include "libs/matrixInputGui/gui.h"
#include "time.h"

int main(){
    matrix_t* m1;
    clock_t c1, c2;
    double difference;

    int entriesBuffer[3*3*4];

    
    runInterface(entriesBuffer);
    printf("Ciao");
    /*
    m1 = init_square(3);
    
    //m1 = auto_populate(m1, 10);
    user_populate_from_buffer(m1, entriesBuffer);
    //print_matrix(m1);
    
    m1 = reduce_ith(m1, 0, 0);
    print_matrix(m1);
    m1 = reduce_ith(m1, 1, 1);
    print_matrix(m1);
    m1 = reduce_ith(m1, 2, 2);
    print_matrix(m1);
    
    c1 = clock();
    m1 = execute_reduction(m1);
    c2 = clock();

    print_matrix(m1);

    difference = (double)(c2-c1)/CLOCKS_PER_SEC;
    printf("Operation took %f\n", difference);
    */
    return 0;
}
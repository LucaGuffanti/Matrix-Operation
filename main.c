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

    // MATRIX PROPS AND GUI ---------
    
    int n=2, m=2;
    
    // Max number of visible digits for every "cell" in matrix
    int cell_max_visible_digits = 4;

    int entriesBuffer[n*m*cell_max_visible_digits];

    char message[] = "Insert data into the Matrix and press TAB to continue";
    
    runInterface(entriesBuffer, message, n, m, cell_max_visible_digits);

    //------------------------------

    
    m1 = init_square(n);
    
    //m1 = auto_populate(m1, 10);
    user_populate_from_buffer(m1, entriesBuffer);

    print_matrix(m1);

    c1 = clock();
    m1 = execute_reduction(m1);
    c2 = clock();

    print_matrix(m1);

    difference = (double)(c2-c1)/CLOCKS_PER_SEC;
    printf("Operation took %f\n", difference);
    
    return 0;
}
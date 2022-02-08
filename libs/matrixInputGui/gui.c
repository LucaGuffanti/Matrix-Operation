#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "../termbox/termbox.h"
#include "../../src/matrixUtils.h"
#include "tools.h"

#define SEPARATOR_CHAR 'X'
#define EMPTY_INPUT_CHAR ' '
#define CURSOR_CHAR '_'


struct cursor {
    int x;
    int y;
};



int setCursorPosition(struct cursor *cpos, int *relativePos, int cell_max_visible_digits, int margin, int n, int m){
    
    int return_flag_value = 0;
    if(*relativePos == -1){
        *relativePos = n*m*cell_max_visible_digits - 1;
        setCursorPosition(cpos, relativePos, cell_max_visible_digits, margin, n, m);
    }
    else if(*relativePos <n*m*cell_max_visible_digits){
        int cellNumber = *relativePos/cell_max_visible_digits;
        int positionInCell = (*relativePos)%cell_max_visible_digits;
	    printf_tb(40, 0, TB_WHITE, TB_DEFAULT, "%d %d", cellNumber, positionInCell);


        // Matrix cell indexes
        int entry_X = cellNumber%m;
        int entry_Y = cellNumber/m;
        
        cpos->x = margin*(entry_X+1)+cell_max_visible_digits*(entry_X);
        cpos->y = margin*(entry_Y+1)+1*(entry_Y);

        cpos->x += positionInCell;

        printf_tb(40, 3, TB_WHITE, TB_DEFAULT, "%d %d", entry_X, entry_Y);
        printf_tb(40, 5, TB_WHITE, TB_DEFAULT, "%d %d", cpos->x, cpos->y);

        printf_tb(40, 7, TB_WHITE, TB_DEFAULT, "                    ", *relativePos);
        printf_tb(40, 7, TB_WHITE, TB_DEFAULT, "INPUT BUFFER POS: %d", *relativePos);

    }
    else{
        // End of matrix, set back to first input cell
        *relativePos = 0;
        setCursorPosition(cpos, relativePos, cell_max_visible_digits, margin, n, m);
    }

    return return_flag_value;

}



void addToInputBuffer(char inputBuffer[], int index, char digit, int occurrences){
    
    inputBuffer[index] = digit;
    occurrences--;
    if(occurrences)
        addToInputBuffer(inputBuffer, index+1, digit, occurrences);

}

void createEntriesBuffer(int entriesBuffer[], char inputBuffer[], int lenInput, int cell_max_visible_digits){
    char currNumberString[cell_max_visible_digits];
    int max_len = lenInput;
    int first_separator_flag = 1;
    
    int i = 0; // inputBuffer iterator
    int j = 0; // currNumberStrig iterator
    int k = 0; // entriesBuffer iterator

    for(i=0; i<max_len; i++){
        // Convert and save inserted number 
        if((i != 0 && i%cell_max_visible_digits == 0) || i == max_len-1){
            if(j<3)
                currNumberString[j] = '\0';

            entriesBuffer[k] = atoi(currNumberString);
            
            // Reset temporary char buffer of the current string
            fillCharBuffer(currNumberString, cell_max_visible_digits, '/0');
            j=0;

            k++;
        }
        if(inputBuffer[i]!=SEPARATOR_CHAR){
            // If the char is not a separator char (i.e. it's a digit), save it in the temp. buffer.
            currNumberString[j] = inputBuffer[i];

            j++;
        }
        
    }

}

void runInterface(){
    
    struct tb_event ev;
    struct cursor cpos;


// MATRIX PROPS ----------------
    
    // Cardinality
    int n=2, m=2;
    
    // Max number of visible digits for every "cell" in matrix
    int cell_max_visible_digits = 4;

//------------------------------

// LIBRARY VARIABLES ------------

    // Index of current digit which will be inserted in the inputBuffer
    int inputBuffer_pos = 0;
    
    // Absolute cursor position in the terminal
    cpos.x = 0;
    cpos.y = 0;
    
    // Graphical props
    int margin = 2;
    int boxWidth = m*cell_max_visible_digits + margin*(m+1);
    int boxHeight = n*1 + margin*(n+1);


    // Full string of digits inserted
    char inputBuffer[cell_max_visible_digits*n*m];

    // Actual final decimal entries
    int entriesBuffer[n*m];
// -------------------------------

    // TODO: Draw matrix body
    //draw_matrix_box(boxWidth, boxHeight); 
    //tb_present();

    // Init input buffer with empty chars
    fillCharBuffer(inputBuffer, cell_max_visible_digits*n*m, SEPARATOR_CHAR);

    // Set Cursor at the first cell of the matrix
    setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
    tb_change_cell(cpos.x, cpos.y, CURSOR_CHAR, TB_WHITE, TB_DEFAULT);

    // Wait an event to occour ( a key pressed )
    while(tb_poll_event(&ev)){
        
        switch (ev.type){
        
            // A key is pressed
            case TB_EVENT_KEY:
                
                if(ev.key == TB_KEY_ESC){
                    tb_clear();
                    tb_shutdown();
                    return;
                }

                else if(ev.key == TB_KEY_BACKSPACE || ev.key == TB_KEY_BACKSPACE2){
                    
                    tb_change_cell(cpos.x, cpos.y, ' ', TB_WHITE, TB_DEFAULT);
                    
                    inputBuffer_pos--;

                    // Note: if inputBuffer_pos is -1, cursor will be set to end of matrix
                    setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
                    
                    // Write '_'
                    tb_change_cell(cpos.x, cpos.y, CURSOR_CHAR, TB_WHITE, TB_DEFAULT);

                    // Refresh
                    tb_present();


                }

                else if(ev.key == TB_KEY_ARROW_LEFT || ev.key == TB_KEY_ARROW_RIGHT){
                    
                    // Display the digit under the cursor before the jump.
                    char digitToMantain = inputBuffer[inputBuffer_pos];
                    if(digitToMantain != SEPARATOR_CHAR)
                        tb_change_cell(cpos.x, cpos.y, digitToMantain, TB_WHITE, TB_DEFAULT);
                    else{
                        tb_change_cell(cpos.x, cpos.y, EMPTY_INPUT_CHAR, TB_WHITE, TB_DEFAULT);

                    }
                    //

                    // Handle the direction of the shift
                    if(ev.key == TB_KEY_ARROW_LEFT)
                        inputBuffer_pos--;
                    else
                        inputBuffer_pos++;
                    

                    setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
                    tb_change_cell(cpos.x, cpos.y, CURSOR_CHAR, TB_WHITE, TB_DEFAULT);


                }

                else if(ev.key == TB_KEY_ENTER){
                    
                    // Cursor and input buffer position before the jump.
                    int start = inputBuffer_pos;


                    // Display the digit under the cursor before the jump.
                    char digitToMantain = inputBuffer[inputBuffer_pos];
                    if(digitToMantain != SEPARATOR_CHAR)
                        tb_change_cell(cpos.x, cpos.y, digitToMantain, TB_WHITE, TB_DEFAULT);
                    else{
                        tb_change_cell(cpos.x, cpos.y, EMPTY_INPUT_CHAR, TB_WHITE, TB_DEFAULT);

                    }
                    //
                    
                    // Fill the inputBuffer with separator chars and handle terminal's cells until the first digit of the next matrix cell
                    // is reached. 
                    while((inputBuffer_pos)%4 !=0 || inputBuffer_pos == start){
                        setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
                        tb_change_cell(cpos.x, cpos.y, EMPTY_INPUT_CHAR, TB_WHITE, TB_DEFAULT);
                        addToInputBuffer(inputBuffer, inputBuffer_pos, SEPARATOR_CHAR, 1);
                        inputBuffer_pos ++;

                    }
                    
                    
                    setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
                    tb_change_cell(cpos.x, cpos.y, CURSOR_CHAR, TB_WHITE, TB_DEFAULT);
                    

                }

                else if(ev.key == TB_KEY_TAB){

                    //TESTING CODE ---------------

                    createEntriesBuffer(entriesBuffer, inputBuffer, cell_max_visible_digits*n*m,cell_max_visible_digits);
                    
                    d_printIntBuffer(entriesBuffer, n*m, 40, 11);
                    tb_present();

                    

                    tb_shutdown();
                    for(int i=0; i<n*m; i++){
                        printf("%d\n", entriesBuffer[i]);
                    }


                    //------------------------------
                }

                else{

                    // Check if ev.ch is digit and add it to inputBuffer
                    if(check_and_insert_digit((char)ev.ch, inputBuffer, &inputBuffer_pos)){

                        // Write digit on cmd and save it to the inputBuffer
                        tb_change_cell(cpos.x, cpos.y, ev.ch, TB_WHITE, TB_DEFAULT);                    
                        addToInputBuffer(inputBuffer, inputBuffer_pos, ev.ch, 1);

                        // Set the cursor to the next position
                        inputBuffer_pos++;
                        setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
                        tb_change_cell(cpos.x, cpos.y, CURSOR_CHAR, TB_WHITE, TB_DEFAULT);


                    }

                }
                
                d_printCharBuffer(inputBuffer, 40, 9);
                tb_present();

                break;
        }
    }    
}

int main(){
	
    // TERMBOX INIT -----------------------------------
    struct tb_event ev;
    int ret;
    ret = tb_init();
	if (ret) {
		fprintf(stderr, "tb_init() failed with error code %d\n", ret);
		return 1;
	}
	tb_select_output_mode(TB_OUTPUT_NORMAL);
    tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
    // ------------------------------------------------

    runInterface();

    return 0;
}
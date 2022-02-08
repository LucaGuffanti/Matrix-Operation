#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "./termbox/termbox.h"
#include "../src/matrixUtils.h"


#define FLAG_UPDATE_ENTRY 1
#define SEPARATOR_CHAR 'X'

struct inputBox {
    int x;
    int y;
};
struct cursor {
    int x;
    int y;
};


void draw_matrix_box(int boxWidth, int boxHeight){

    struct cursor cpos;
    cpos.x = 0;
    cpos.y = 0;

    //TODO: fare in modo che si vede il cursoee lampeggiare
    int x, y;
    for(x=0; x<boxWidth; x++){
        for(y=0; y<boxHeight; y++){
            tb_change_cell(x,y, ' ', TB_WHITE,TB_DEFAULT);
        }        
    }
    
}

int uint32_to_char(uint32_t key){
    char str[1];
    sprintf(str, "%u", key);
    return str[0]; 
}

int check_and_insert_digit(uint32_t key, char *inputBuffer, int *inputBuffer_pos){
    // Check if key is a number
    //debugPrint(0,0, key);

    if(key >= 48 && key<=57){
        key = key-48;

        inputBuffer[*inputBuffer_pos] = uint32_to_char(key);   
        return 1;
    }
    return 0;
}


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

void print_tb(const char *str, int x, int y, uint16_t fg, uint16_t bg)
{
	while (*str) {
		uint32_t uni;
		str += tb_utf8_char_to_unicode(&uni, str);
		tb_change_cell(x, y, uni, fg, bg);
		x++;
	}
}

void printf_tb(int x, int y, uint16_t fg, uint16_t bg, const char *fmt, ...)
{
	char buf[4096];
	va_list vl;
	va_start(vl, fmt);
	vsnprintf(buf, sizeof(buf), fmt, vl);
	va_end(vl);
	print_tb(buf, x, y, fg, bg);
}


void addToInputBuffer(char inputBuffer[], int index, char digit, int occurrences){
    
    inputBuffer[index] = digit;
    occurrences--;
    if(occurrences)
        addToInputBuffer(inputBuffer, index+1, digit, occurrences);

}
void flushCharBuffer(char *buffer, int len){
    for(int i=0; i<len; i++){
        buffer[i] = '\0';
    }
}
void createEntriesBuffer(int entriesBuffer[], char inputBuffer[], int lenInput, int cell_max_visible_digits){
    char currNumberString[cell_max_visible_digits];
    int i,j,k;
    int max_len = lenInput;
    int first_separator_flag = 1;
    /*23XX0XXX22223333
    numero and jvalida => save
    
    vero vero => nulla
    vero falso => save
    falso vero => save senza ultimo
    falso falso => save senza ultimo

    
    */

   //TODO: sistemare i flag 
    for(i=0, j=0, k=0; i<max_len; i++){

        if(inputBuffer[i] == SEPARATOR_CHAR || j == 3){
            if(inputBuffer[i] != SEPARATOR_CHAR)
                currNumberString[j] = inputBuffer[i];
            else{
                first_separator_flag = 0;

            }
            
            entriesBuffer[k] = atoi(currNumberString);
            
            flushCharBuffer(currNumberString, cell_max_visible_digits);

            k++;
            j=0;

        }
        else{
            first_separator_flag = 1;
            currNumberString[j] = inputBuffer[i];
            j++;
        }

    }
}
void d_printCharBuffer(char *buffer, int x, int y ){
    printf_tb(x,y, TB_WHITE, TB_DEFAULT, "                                       ");
    printf_tb(x,y, TB_WHITE, TB_DEFAULT, buffer);
}


void d_printIntBuffer(int *buffer, int len, int x, int y ){

    printf_tb(x,y, TB_WHITE, TB_DEFAULT, "                                                   ");
    int i;
    for(i=0; i<len; i++){
        printf_tb(x,y, TB_WHITE, TB_DEFAULT, "%d", buffer[i]);
        x+=2;
    }
}

void getInputLine(){
    
    struct tb_event ev;
    struct cursor cpos;

    // Relative cursor position
    int inputBuffer_pos = 0;
    
    // Absolute cursor position
    cpos.x = 0;
    cpos.y = 0;
    

    // Max number of visible digits for every "cell" in matrix
    int n=2, m=2;
    int cell_max_visible_digits = 4;
    int margin = 2;
    int boxWidth = m*cell_max_visible_digits + margin*(m+1);
    int boxHeight = n*1 + margin*(n+1);

    // Draw Matrix Body
    //draw_matrix_box(boxWidth,boxHeight);

    // Full string of digits inserted
    char inputBuffer[cell_max_visible_digits*n*m];

    // Actual decimal entries
    int entriesBuffer[n*m];

    draw_matrix_box(boxWidth, boxHeight);
    // Set Cursor at the first cell of the matrix
    setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
    tb_change_cell(cpos.x, cpos.y, '_', TB_WHITE, TB_DEFAULT);

    tb_present();

    struct tb_cell last_state;
    // TODO: Algoritmo inserimento entry da inputBuffer
    while(tb_poll_event(&ev)){
        switch (ev.type){
        
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
                tb_change_cell(cpos.x, cpos.y, '_', TB_WHITE, TB_DEFAULT);

                // Refresh
                tb_present();


            }
            else if(ev.key == TB_KEY_ARROW_LEFT || ev.key == TB_KEY_ARROW_RIGHT){
                char digitToMantain = inputBuffer[inputBuffer_pos];
                if(digitToMantain != 'X')
                    tb_change_cell(cpos.x, cpos.y, digitToMantain, TB_WHITE, TB_DEFAULT);
                else{
                    tb_change_cell(cpos.x, cpos.y, ' ', TB_WHITE, TB_DEFAULT);

                }

                if(ev.key == TB_KEY_ARROW_LEFT)
                    inputBuffer_pos--;
                else
                    inputBuffer_pos++;
                
                setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
                
                // Write '_'
                tb_change_cell(cpos.x, cpos.y, '_', TB_WHITE, TB_DEFAULT);

            
                tb_present();



            }
            else if(ev.key == TB_KEY_ENTER){
                
                int start = inputBuffer_pos;
                /*
                0 1 2 3     4 5 6 7

                8 9 10 11   12 13 14 15
                
                */



                char digitToMantain = inputBuffer[inputBuffer_pos];
                if(digitToMantain != 'X')
                    tb_change_cell(cpos.x, cpos.y, digitToMantain, TB_WHITE, TB_DEFAULT);
                else{
                    tb_change_cell(cpos.x, cpos.y, ' ', TB_WHITE, TB_DEFAULT);

                }

                
                while((inputBuffer_pos)%4 !=0 || inputBuffer_pos == start){
                    setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
                    tb_change_cell(cpos.x, cpos.y, 'X', TB_WHITE, TB_DEFAULT);
                    addToInputBuffer(inputBuffer, inputBuffer_pos, SEPARATOR_CHAR, 1);
                    inputBuffer_pos ++;

                }
                setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);
                

                // Write '_'
                tb_change_cell(cpos.x, cpos.y, '_', TB_WHITE, TB_DEFAULT);

                // Refresh
                tb_present();
                

            }
            else if(ev.key == TB_KEY_TAB){
                createEntriesBuffer(entriesBuffer, inputBuffer, cell_max_visible_digits*n*m,cell_max_visible_digits);
                
                d_printIntBuffer(entriesBuffer, n*m, 40, 11);
                tb_present();

                //TESTING

                tb_shutdown();
                    for(int i=0; i<n*m; i++){
                        printf("%d\n", entriesBuffer[i]);
                    }
    
            }
            else{

                // Check if ev.ch is digit and add it to inputBuffer
                if(check_and_insert_digit((char)ev.ch, inputBuffer, &inputBuffer_pos)){
                    // Write digit
                    tb_change_cell(cpos.x, cpos.y, ev.ch, TB_WHITE, TB_DEFAULT);                    
                    addToInputBuffer(inputBuffer, inputBuffer_pos, ev.ch, 1);
                    // Set the cursor to the next position
                    inputBuffer_pos++;
                    setCursorPosition(&cpos, &inputBuffer_pos, cell_max_visible_digits, margin, n, m);

                }

                //d_printCharBuffer(inputBuffer, 40, 9);

                // Write '_'
                tb_change_cell(cpos.x, cpos.y, 95, TB_WHITE, TB_DEFAULT);

                printf_tb(40,10, TB_DEFAULT, TB_DEFAULT, "%d", inputBuffer_pos%4);

                // Refresh
                tb_present();

                
            }
            
            d_printCharBuffer(inputBuffer, 40, 9);
            tb_present();

            break;
        }
    }    
}

int main(){
	struct tb_event ev;

    int ret;

	ret = tb_init();
	if (ret) {
		fprintf(stderr, "tb_init() failed with error code %d\n", ret);
		return 1;
	}
	tb_select_output_mode(TB_OUTPUT_NORMAL);
    tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
    getInputLine();

    return 0;
}
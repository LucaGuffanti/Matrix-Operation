#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "../termbox/termbox.h"

#include "tools.h"

#define SEPARATOR_CHAR 'X'
#define EMPTY_INPUT_CHAR ' '
#define CURSOR_CHAR '_'


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
            tb_change_cell(x,y, 'O', TB_WHITE,TB_DEFAULT);
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

void fillCharBuffer(char *buffer, int len, char c){
    for(int i=0; i<len; i++){
        buffer[i] = c;
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

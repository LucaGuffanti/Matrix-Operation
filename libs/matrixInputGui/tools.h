#ifndef TOOLS_H_
#define TOOLS_H_


void draw_matrix_box(int , int );
int uint32_to_char(uint32_t);
void print_tb(const char *, int , int , uint16_t , uint16_t );
void printf_tb(int , int , uint16_t , uint16_t , const char *, ...);
void fillCharBuffer(char *, int , char);
void d_printCharBuffer(char *, int , int );
void d_printIntBuffer(int *, int,int,int);

#endif 
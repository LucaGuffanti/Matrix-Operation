#ifndef GUI_H_
#define GUI_H_

struct cursor {
    int x;
    int y;
};


int setCursorPosition(struct cursor *, int *, int, int, int, int);
void addToInputBuffer(char [], int , char , int );
void createEntriesBuffer(int [], char [], int , int );
void runInterface(int*);

#endif

#ifndef ARCHITECTURE_BIG_CH
#pragma once
#define ARCHITECTURE_BIG_CH
#include "myTerm.h"
int bc_printA(char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_getbigcharpos(int* big, int x, int y, bool *value);
int bc_printbigchar(int[2], int x, int y, enum colors color_text, enum colors color_back);
int bc_setbigcharpos(int* big, int x, int y, bool *value);
int bc_bigCharWrite(int fd, unsigned int * big, int count);
int bc_bigCharRead(int fd, unsigned int * big, int need_count, int * count);
#endif //ARCHITECTURE_BIG_CH


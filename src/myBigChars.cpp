#include <iostream>
#include <stdio.h>
#include "myTerm.h"
#define ll long long
using namespace std;
int bc_printA(char* str){
    cout << "\033(0" << str << "\033(B";
    return 0;
}
int bc_box(int x1, int y1, int x2, int y2){
    mt_gotoXY(x1,y1);
    bc_printA("l");
    for (int i=1;i<y2-1;++i){
        bc_printA("q");
    }
    bc_printA("k");
    mt_gotoXY(x1+x2-1,y1);
    bc_printA("m");
    for (int i=1;i<y2-1;++i){
        bc_printA("q");
    }
    bc_printA("j");
    for (int i=1;i<x2-1;++i){
        mt_gotoXY(x1+i,y1);
	bc_printA("x");
	mt_gotoXY(x1+i,y1+y2-1);
        bc_printA("x");
    }
    mt_gotoXY(x1+x2+1,y1+y2+1);
    return 0;
}
int bc_getbigcharpos(int* big, int x, int y, bool *value){
    if (x<0 || x>7)
        return -1;
    if (y<0 || y>7)
        return -1;
    ll it=0;
    if (x>4){
        it=1;
        x-=4;
    }
    ll col,row=x*2;
    *value=big[it]&(1<<(31-x*8-y));
    return 0;
}
int bc_setbigcharpos(int* big, int x, int y, bool *value){
    if ((x < 0) || (x > 7) || (y < 0) || (y > 7))
        return -1 ;
    if (value)
        big[int(y / 4)] |= (1 << (8 *(y % 4) + (7 - x))) ;
    else
        big[int(y / 4)] &= ~(1 << (8 *(y % 4) + (7 - x))) ;


    return 0 ;
}

int bc_printbigchar(int big[2], int x, int y, enum colors color_text, enum colors color_back){
    mt_setfgcolor(color_text);
    mt_setbgcolor(color_back);
    for (int i=0;i<8;++i){
        mt_gotoXY(x+i,y);
        for (int j=0;j<8;++j){
            bool value;
            bc_getbigcharpos(big, i, j, &value);
            if (value){
                 bc_printA("a");
            }
            else
                cout << ' ';

        }

    }
    mt_setDefaultColorSettings();


}
/*int bc_bigCharWrite(int fd, unsigned int * big, int count){
    if (write(fd, big,count * 2 * sizeof(unsigned int)))
        return -1 ;
    return 0 ;
}

int bc_bigCharRead(int fd, unsigned int * big, int need_count, int * count){
    *count = 0 ;
    for (int i = 0; i < need_count * 2; ++i){
        if (read(fd, &big[i], sizeof(unsigned int)) == -1)
            return -1 ;
        if (!((i + 1) % 2))
            (*count)++ ;
    }

    return 0 ;
}*/

//
// Created by ilya on 07.05.2021.
//
#include <iostream>
#include <vector>
#include "myBigChars.h"
#include "myTerm.h"
#include "printConsole.h"
#include "mySimpleComputer.h"
using namespace std;
extern const int mem_size;
extern int flag;
extern short memory[];
unsigned int big[][2]={
        {0xFFC3C3C3, 0xC3C3C3FF},
        {0x1838F818, 0x181818FF},
        {0xFFC30303, 0xFFC0C0FF},
        {0xFF0F3CF0, 0xFF0303FF},
        {0xC3C3C3FF, 0x03030303},
        {0xFFC0C0FF, 0x030303FF},
        {0xFFC0C0C0, 0xFFC3C3FF},
        {0xFF030F3C, 0x30FF3030},
        {0xFFC3C3FF, 0xFFC3C3FF},
        {0xFFC3C3C3, 0xFF0303FF},

        {0x3CFFC3C3, 0xC3FFC3C3},
        {0xFCC3C3FC, 0xC3C3C3FC},
        {0xFCC3C0C0, 0xC0C0C3FC},
        {0xFCC3C3C3, 0xC3C3C3FC},
        {0xFFC0C0C0, 0xFFC0C0FF},
        {0xFFC0C0FF, 0xC0C0C0C0},
        {0x003C3CFF, 0xFF3C3C00},
        {0x003C3C00, 0x003C3C00},
        {0x000000FF, 0xFF000000}
};
vector<int> getHex(short z){
    vector<int> ans(4);
    int i=3;
    while (z>=16){
        ans[i]=z%16;
        z/=16;
        --i;
    }
    ans[i]=z;
    return ans;
}
void printColorSquare(int x1,int y1,int x2,int y2){
    mt_setbgcolor(CYANIC);
    mt_gotoXY(x1,y1);
    for (int i=0;i<x2;++i) {
        mt_gotoXY(5+i,y1);
        for (int j = 0; j < y2; ++j) {
            cout << ' ';
        }
    }
}
void coutTwoChSmallHex(vector<int> z){
    /*cout << "##";
    for (auto v:z)
        cout << v << ' ';
    cout << "##";
    cout << endl;*/
    if (z[4]<10)
        cout << z[4];
    else
        cout << (char)(z[4]-10+'A');
    if (z[3]<10)
        cout << z[3];
    else
        cout << (char)(z[3]-10+'A');
    cout << ' ';
}
void coutSmallHex(vector<int> z, int cur){
    if (cur>=0)
        cout << '+';
    else
        cout << '-';
    for (int i=0;i<4;++i){
        if (z[i]<10)
            cout << z[i];
        else
            cout << (char)(z[i]-10+'A');
    }
    cout << ' ';
}
void coutBigHex(vector<int> cnt, int deltx, int delty, int cur){
    if (cur>=0)
        bc_printbigchar(big[16],18+deltx,6+delty,RED,WHITE);
    else
        bc_printbigchar(big[18],18+deltx,6+delty,RED,WHITE);
    bc_printbigchar(big[cnt[0]],18+deltx,15+delty,RED,WHITE);
    bc_printbigchar(big[cnt[1]],18+deltx,24+delty,RED,WHITE);
    bc_printbigchar(big[cnt[2]],18+deltx,33+delty,RED,WHITE);
    bc_printbigchar(big[cnt[3]],18+deltx,42+delty,RED,WHITE);
}
void coutMem(int deltx,int delty){
    for (int i=0;i<10;++i){
        mt_gotoXY(6+i+deltx,6+delty);
        for (int j=0;j<10;++j){
            if (i*10+j==instructioncounter) {
                mt_setbgcolor(BLACK);
                coutSmallHex(getHex(abs(memory[i*10+j])),memory[i*10+j]);
                mt_setbgcolor(CYANIC);
            }
            else
                coutSmallHex(getHex(abs(memory[i*10+j])),memory[i*10+j]);
            //cout << "+0000 ";
        }
    }
}
int printConsole(int deltx,int delty){
    my_clrscr();
    printColorSquare(5+deltx,5+delty,22+deltx,54+delty);
    bc_box(5+deltx,5+delty,12,62);
    mt_gotoXY(5+deltx,30+delty);
    cout << " Memory ";
    coutMem(deltx,delty);
    bc_box(5+deltx,67+delty,3,22);
    mt_gotoXY(5+deltx,71+delty);
    cout << " accumulator ";
    mt_gotoXY(6+deltx,75+delty);
    coutSmallHex(getHex(abs(accum)),accum);

    bc_box(8+deltx,67+delty,3,22);
    mt_gotoXY(8+deltx,68+delty);
    cout << " instructionCounter ";
    mt_gotoXY(9+deltx,75+delty);
    coutSmallHex(getHex(instructioncounter),instructioncounter);

    bc_box(11+deltx,67+delty,3,22);
    mt_gotoXY(11+deltx,73+delty);
    cout << " Operation ";
    mt_gotoXY(12+deltx,75+delty);
    int comm,arg;
    if (sc_commandDecode(memory[instructioncounter],&comm,&arg)==0) {
        cout << '+';
        //  coutTwoChSmallHex(getHex(comm));
        cout << comm;
        cout << ": ";
        cout << arg;
        //coutTwoChSmallHex(getHex(arg));
    }
    else{
        cout << "+00 : 00";
    }
    //cout << '+' << com[2] << com[3] << " : " << op[2] << op[3];

    bc_box(14+deltx,67+delty,3,22);
    mt_gotoXY(14+deltx,75+delty);
    cout << " Flags ";
    mt_gotoXY(15+deltx,74+delty);
    coutFlags(15+deltx,74+delty);

    bc_box(17+deltx,5+delty,10,46);
    bc_box(17+deltx,51+delty,10,38);

    mt_gotoXY(17+deltx,54+delty);
    cout << " Keys: ";
    mt_gotoXY(18+deltx,52+delty);
    cout << " l    -   load ";
    mt_gotoXY(19+deltx,52+delty);
    cout << " s    -   save ";
    mt_gotoXY(20+deltx,52+delty);
    cout << " r    -   run ";
    mt_gotoXY(21+deltx,52+delty);
    cout << " t    -   step ";
    mt_gotoXY(22+deltx,52+delty);
    cout << " i    -   reset ";
    mt_gotoXY(23+deltx,52+delty);
    cout << " F5    -   accumulator ";
    mt_gotoXY(24+deltx,52+delty);
    cout << " F6    -   instructionCounter ";

    coutBigHex(getHex(abs(memory[(int)instructioncounter])),deltx,delty,memory[(int)instructioncounter]);

    mt_gotoXY(30,0);
    cout << endl;
    return 0;
}


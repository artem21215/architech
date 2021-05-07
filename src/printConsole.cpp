//
// Created by artem on 07.05.2021.
//
#include <iostream>
#include "myBigChars.h"
#include "myTerm.h"
using namespace std;
extern const int mem_size;
extern int flag;
extern short memory[];
unsigned int big[][2]={
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF},
        {0xFFFFE0FF, 0xFF07FFFF}
};
int printConsole(){
    my_clrscr();
    bc_box(5,5,12,62);
    mt_gotoXY(5,30);
    cout << " Memory ";
    for (int i=0;i<10;++i){
        mt_gotoXY(6+i,6);
        for (int j=0;j<10;++j){
            cout << "+0000 ";
        }
    }
    bc_box(5,67,3,22);
    mt_gotoXY(5,71);
    cout << " accumulator ";
    mt_gotoXY(6,75);
    cout << "+0000";

    bc_box(8,67,3,22);
    mt_gotoXY(8,68);
    cout << " instructionCounter ";
    mt_gotoXY(9,75);
    cout << "+0000";

    bc_box(11,67,3,22);
    mt_gotoXY(11,73);
    cout << " Operation ";
    mt_gotoXY(12,75);
    cout << "+0000";

    bc_box(14,67,3,22);
    mt_gotoXY(14,75);
    cout << " Flags ";
    mt_gotoXY(15,75);
    cout << "+0000";

    bc_box(17,5,10,46);
    bc_box(17,51,10,38);

    mt_gotoXY(17,54);
    cout << " Keys: ";
    mt_gotoXY(18,52);
    cout << " l    -   load ";
    mt_gotoXY(19,52);
    cout << " s    -   save ";
    mt_gotoXY(20,52);
    cout << " r    -   run ";
    mt_gotoXY(21,52);
    cout << " t    -   step ";
    mt_gotoXY(22,52);
    cout << " i    -   reset ";
    mt_gotoXY(23,52);
    cout << " F5    -   accumulator ";
    mt_gotoXY(24,52);
    cout << " F6    -   instructionCounter ";


    mt_gotoXY(30,0);
    return 0;
}


//
// Created by ilya on 18.05.2021.
//
#include <iostream>
using namespace std;
#include "cu.h"
#include "mySimpleComputer.h"
#include "printConsole.h"
#include "timer.h"
#include "alu.h"
#include "myTerm.h"
int ariphmetic[]={};
int cu(){
    if (instructioncounter>=99){
        sc_regSet(M,1);
        return 1;
    }
    sc_regSet(M,0);
    int value,command;
    int zeroflag;
    sc_regGet(T,&zeroflag);
    if (sc_commandDecode(memory[instructioncounter],&command,&value)==0){
        alu(command,value);
        instructioncounter++;
        if (flag!=zeroflag) {
            stopHandler(0);
            sc_regSet(T, 1);
        }
    }
    else{
        stopHandler(0);
        sc_regSet(E,1);
        sc_regSet(T,1);
    }
    printConsole(deltx,delty);
    return 0;
}

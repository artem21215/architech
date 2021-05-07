//
// Created by artem on 27.04.2021.
//
#include <iostream>
#include <fstream>
#include "mySimpleComputer.h"
#define P 0
#define O 1
#define M 2
#define T 3
#define E 4
#define F 5
int all_com[]={10,11,20,21,30,31,32,33,40,41,42,43,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76};
int sc_regSet(int reg, int value);
int sc_memoryInit(){
    for (int i=0;i<mem_size;++i){
        memory[i]=0;
    }
    return 0;
}
int sc_memorySet(int address, int value){
    if (address>=0 && address<mem_size) {
        memory[address] = value;
        return 0;
    }
    else {
        sc_regSet(M,1);
        return 1;
    }
}
int sc_memoryGet(int address, int* value){
    if (address>=0 && address<mem_size) {
        *value=memory[address];
        return 0;
    }
    else {
        sc_regSet(M,1);
        return 1;
    }
}
int sc_memorySave (char * filename){
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()){
        sc_regSet(F,true);
        return 1;
    }
    for (int i=0;i<mem_size;++i){
        fout << memory[i] << ' ';
    }
    fout.close();
    return 0;
}
int sc_memoryLoad (char * filename){
    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open()){
        sc_regSet(F,true);
        return 1;
    }
    for (int i=0;i<mem_size;++i){
        fin >> memory[i];
    }
    return 0;
}
int sc_regInit (){
    flag=0;
    return 0;
}
int sc_regGet (int reg, int * value){
    if (reg<0 || reg>5)
        return 1;
    *value=flag&(1<<reg);
    return 0;
}
int sc_regSet(int reg, int value){
    if (reg>=0 && reg<=5 && value>=0 && value<=1){
        if (value){
            flag=flag|(1<<reg);
        }
        else
            flag=flag&(~(1<<reg));
        return 0;
    }
    else
        return 1;
}
int sc_commandEncode (int command, int operand, int * value){
    if (operand<0 || operand>127){
        sc_regSet(E,1);
        return 1;
    }
    int i;
    for (i=0;i<76;++i){
        if (command==all_com[i])
            break;
    }
    if (i==76) {
        sc_regSet(E,1);
        return 1;
    }
    if (command==10 || command==11 || command==20 || command==21)
    *value=0;
    for (int i=0;i<7;++i){
        int elem=operand&(1<<i);
        if (elem!=0){
            *value=*value|(1<<i);
        }
    }
    for (int i=0;i<7;++i){
        int elem=command&(1<<i);
        if (elem!=0){
            *value=*value|(1<<(i+7));
        }
    }
    //*value|=(1<<14);
    return 0;
}
int sc_commandDecode (int value, int * command, int * operand){
    *command=0;
    for (int i=0;i<7;++i){
        int elem;
        elem=value&(1<<(i+7));
        if (elem!=0)
            *command=*command|(1<<i);
    }
    *operand=0;
    for (int i=0;i<7;++i){
        int elem;
        elem=value&(1<<i);
        if (elem!=0)
            *operand=*operand|(1<<i);
    }
    if (*operand<0 || *operand>127){
        sc_regSet(E,1);
        return 1;
    }
    int i;
    for (i=0;i<76;++i){
        if (*command==all_com[i])
            break;
    }
    if (i==76) {
        sc_regSet(E,1);
        return 1;
    }
    return 0;
}


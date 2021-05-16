//
// Created by artem on 27.04.2021.
//

#ifndef ARCHITECTURE_MYSIMPLECOMPUTER_H
#define ARCHITECTURE_MYSIMPLECOMPUTER_H
#define P 0
#define O 1
#define M 2
#define T 3
#define E 4
#define F 5
extern const int mem_size;
extern int flag;
extern short memory[];
void coutFlags(int deltx, int delty);
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave (char * filename);
int sc_memoryLoad (char * filename);
int sc_regInit ();
int sc_regGet (int reg, int * value);
int sc_regSet (int reg, int value);
int sc_commandEncode (int command, int operand, int * value);
int sc_commandDecode (int value, int * command, int * operand);
#endif //ARCHITECTURE_MYSIMPLECOMPUTER_H

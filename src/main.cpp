#include <iostream>
#include "mySimpleComputer.h"
#include "myBigChars.h"
#include "myTerm.h"
#include "printConsole.h"
using namespace std;
#define ll long long
#define ld long double
int flag=0;
const int mem_size=100;
short memory[100];
short accum=8234;
char instructioncounter=30;
void print_mem(){
    for (int i : memory){
        cout << i << ' ';
    }
    cout << endl;
}
int main() {
    sc_memoryInit();
    sc_memorySet(30,1);
    int check;
    sc_memoryGet(30,&check);
    char str[10]="input.txt";
    sc_memorySave(str);
    sc_memoryLoad(str);
    printConsole(0,30);
    return 0;
}

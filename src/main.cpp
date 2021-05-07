#include <iostream>
#include "mySimpleComputer.h"
using namespace std;
#define ll long long
#define ld long double
int flag=0;
const int mem_size=100;
int memory[100];
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
    cout << check << endl;
    print_mem();
    int comand_coded=5;
    sc_commandEncode(12,15,&comand_coded);
    cout << comand_coded << endl;
    int command,oper;
    sc_commandDecode(comand_coded,&command,&oper);
    cout << command << ' ' << oper << endl;
    return 0;
}

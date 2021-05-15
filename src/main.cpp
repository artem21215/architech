#include <iostream>
#include <unistd.h>
#include "mySimpleComputer.h"
#include "myBigChars.h"
#include "myTerm.h"
#include "myReadkey.h"
#include "printConsole.h"

using namespace std;
#define ll long long
#define ld long double
int flag = 0;
const int mem_size = 100;
short memory[100];
short accum = 8234;
char instructioncounter = 30;

void print_mem() {
    for (int i : memory) {
        cout << i << ' ';
    }
    cout << endl;
}

int main() {
    keys ch = i;
    char str[10] = "input.txt";
    sc_memoryInit();
    while (ch != e) {
        bool br=false;
        printConsole(0,30);
        rk_readkey(ch);
        switch (ch) {
            case l:
                sc_memoryLoad(str);
                break;
            case s:
                sc_memoryLoad(str);
                break;
            case F5:
                cout << "input value of accumulator: ";
                short value;
                cin >> value;
                accum = value;
                break;
            case F6:
                cout << "input value of instructioncounter: ";
                int help;
                cin >> help;
                instructioncounter = help;
                break;
            case t:
                break;
            case i:
                break;
            case r:
                break;
            case e:
                br=true;
                break;
        }
        if (br)
            break;
    }
    return 0;
}

#include <iostream>
#include <unistd.h>
#include "mySimpleComputer.h"
#include "myBigChars.h"
#include "myTerm.h"
#include "myReadkey.h"
#include "printConsole.h"
#include "timer.h"
#include "cu.h"

using namespace std;
#define ll long long
#define ld long double
int flag = 0;
const int mem_size = 100;
short memory[100];
short accum = 0;
char instructioncounter = 0;
int deltx = 0, delty = 30;

void print_mem() {
    for (int i : memory) {
        cout << i << ' ';
    }
    cout << endl;
}

int main() {
    keys ch = l;
    char str[10] = "input.o";
    sc_memoryInit();
    reset();
    while (ch != e) {
        bool br = false;
        int val;
        sc_regSet(T, 1);
        printConsole(deltx, delty);
        rk_readkey(ch);
        switch (ch) {
            case l:
                sc_memoryLoad(str);
                break;
            case s:
                sc_memorySave(str);
                break;
            case F5:
                doAccum();
                break;
            case F6:
                doInstrCounter();
                break;
            case t:
                cu();
                break;
            case i:
                res_signal();
                break;
            case r:
                rk_mytermsave();
                rk_mytermregime(0, 0, 0, 0, 0);
                sc_regSet(T, 0);
                my_timer();
                while (true){
                    int exit;
                    sc_regGet(T,&exit);
                    if (exit!=0)
                        break;
                }
                stopHandler(0);
                sc_regSet(T, 0);
                printConsole(deltx, delty);
                rk_mytermrestore();
                break;
            case e:
                br = true;
                break;
        }
        if (br)
            break;
    }
    return 0;
}

//
// Created by artem on 17.05.2021.
//
using namespace std;
#include <iostream>
#include "myReadkey.h"
#include "mySimpleComputer.h"
#include "printConsole.h"
#include "timer.h"
int alu(int command,int operand){
    int val;
    int check;
    switch (command) {
        case 10:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            val=0;
            sc_regGet(T,&check);
            if (check==0)
                stopHandler(0);
            get_int_from_terminal(val);
            if (val>32767){
                sc_regSet(M,1);
                return 1;
            }
            memory[(int)operand]=val;
            sc_regGet(T,&check);
            if (check==0)
                my_timer();
            break;
        case 11:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            sc_regGet(T,&check);
            if (check==0)
                stopHandler(0);
            cout << "Output: " << memory[operand] << endl;
            char ch;
            cout << "press any button for continue...";
            rk_mytermsave();
            rk_mytermregime(0,1,1,0,1);
            cin.get(ch);
            cin.get(ch);
            rk_mytermrestore();
            sc_regGet(T,&check);
            if (check==0)
                my_timer();
            break;
        case 20:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            accum=memory[operand];
            break;
        case 21:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            memory[operand]=accum;
            break;
        case 30:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            if (memory[operand]>32767-accum){
                sc_regSet(P,1);
                return 1;
            }
            accum+=memory[operand];
            break;
        case 65:
            if (accum<0 || accum>=100){
                sc_regSet(M,1);
                return 1;
            }
            if (memory[operand]>32767-memory[accum]){
                sc_regSet(P,1);
                return 1;
            }
            accum=memory[accum]+memory[operand];
            break;
        case 31:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            if (memory[operand]<-32768+accum){
                sc_regSet(P,1);
                return 1;
            }
            accum-=memory[operand];
            break;
        case 32:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            if (memory[operand]==0){
                sc_regSet(O,1);
                return 1;
            }
            accum/=memory[operand];
            break;
        case 33:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            if (accum!=0 && abs(memory[operand])>32767/abs(accum)){
                sc_regSet(P,1);
                return 1;
            }
            accum*=memory[operand];
            break;
        case 40:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            instructioncounter=operand-1;
            break;
        case 41:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            if (accum<0)
                instructioncounter=operand-1;
            break;
        case 42:
            if (operand<0 || operand>=100){
                sc_regSet(M,1);
                return 1;
            }
            if (accum==0)
                instructioncounter=operand-1;
            break;
        case 43:
            stopHandler(0);
            instructioncounter--;
            sc_regSet(T,1);
            break;
    }
    return 0;
}

#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#define ll long long
using namespace std;
enum colors{
    BLACK=0,
    RED=1,
    GREEN=2,
    YELLOW=3,
    BLUE=4,
    PURPLE=5,
    CYANIC=6,
    WHITE=7
};
int my_clrscr(){
    cout << "\E[H\E[J";
    return 0;
}
int mt_gotoXY(int i, int j){
    cout <<"\E[" << i << ";" << j << "H";
    return 0;
}
int mt_setfgcolor(enum colors cur_col){
    cout <<"\E[3" << cur_col << "m";
    return 0;
}
int mt_setbgcolor(enum colors cur_col2){
    cout << "\E[4" <<  cur_col2 << "m";
    return 0;
}
int mt_getscreensize(int *rows, int *cols){
    winsize ws;
    *rows=ws.ws_row;
    *cols=ws.ws_col;
    if (!ioctl(1, TIOCGWINSZ, &ws)){
        return 0;
    }
    else
        return 1;
}

int mt_setDefaultColorSettings() {
    cout<<"\E[0m";
    return 0 ;
}



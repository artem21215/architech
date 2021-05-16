//
// Created by artem on 08.05.2021.
//
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include "myReadkey.h"
#include "printConsole.h"
#include "mySimpleComputer.h"
using namespace std;
int doTimer(){
    if (instructioncounter>=99){
        sc_regSet(M,1);
        return 1;
    }
    sc_regSet(M,0);
    instructioncounter++;
    return 0;
}
int doAccum(){
    cout << "input value of accumulator: ";
    int value;
    cin >> value;
    if (value<0 || value>32767){
        sc_regSet(M,1);
        return 1;
    }
    sc_regSet(M,0);
    accum = value;
    return 0;
}
int doInstrCounter(){
    cout << "input value of instructioncounter: ";
    int help;
    cin >> help;
    if (help<0 || help>99){
        sc_regSet(M,1);
        return 1;
    }
    sc_regSet(M,0);
    instructioncounter = help;
    return 0;
}
int rk_readkey(keys & keys){
    rk_mytermsave();
    rk_mytermregime(0,0,1,0,1);
    char ch_f5[]={27,91,49,53,126,0},
            ch_f6[]={27,91,49,55,126,0},
            ch_l[]={108,0},
            ch_s[]={115,0},
            ch_t[]={116,0},
            ch_i[]={105,0},
            ch_r[]={114,0};
    char buf[200]="";
    int readCh=read(0,buf,8);
    rk_mytermregime(1,0,0,1,1);
    if (strcmp(buf,ch_f5)==0){
        keys=F5;
        return 0;
    }
    if (strcmp(buf,ch_f6)==0){
        keys=F6;
        return 0;
    }
    if (strcmp(buf,ch_l)==0){
        keys=l;
        return 0;
    }
    if (strcmp(buf,ch_s)==0){
        keys=s;
        return 0;
    }
    if (strcmp(buf,ch_i)==0){
        keys=i;
        return 0;
    }
    if (strcmp(buf,ch_t)==0){
        keys=t;
        return 0;
    }
    if (strcmp(buf,ch_r)==0){
        keys=r;
        return 0;
    }
    if (readCh==0)
        return -1;
    keys=e;
    return 0;
}
int rk_mytermsave(){
    struct termios options;
    if (tcgetattr(STDIN_FILENO,&options)!=0){
        return -1;
    }
    FILE *save=fopen("setting","wb1246");
    if (save==NULL)
        return -1;
    fwrite(&options,sizeof(options),1,save);
    fclose(save);
    return 0;
}
int rk_mytermrestore(){
    struct termios options;
    FILE *reset=fopen("setting","rb");
    if (reset==NULL)
        return -1;
    if (fread(&options,sizeof(options),1,reset)>0){
        if (tcsetattr(STDIN_FILENO,TCSAFLUSH,&options)!=0)
            return -1;
    }
    else
        return -1;
    fclose(reset);
    return 0;
}
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint){
    struct termios options;
    if (tcgetattr(STDIN_FILENO,&options)!=0)
        return -1;
    if (regime==1)
        options.c_lflag|=ICANON;
    else if (regime==0)
        options.c_lflag&=~ICANON;
    else
        return -1;
    if (regime==0) {
        options.c_cc[VTIME] = vtime;
        options.c_cc[VMIN] = vmin;
    }
    if (echo == 1) {
        options.c_lflag |= ECHO;
    } else if (echo == 0)
        options.c_lflag &= (~ECHO);
    else
        return -1;
    if (sigint == 1)
        options.c_lflag |= ISIG;
    else if (sigint == 0)
        options.c_lflag &= ~ISIG;
    else
        return -1;
    if (tcsetattr(STDIN_FILENO,TCSANOW,&options)!=0)
        return -1;
    return 0;
}
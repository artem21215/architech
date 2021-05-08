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
#include "myReadkey.h"
using namespace std;
int rk_readkey(enum keys *){
    char buf[200];
    for (int i=0;i<200;++i)
        buf[i]=0;
    int readCh=read(0,buf,1);
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
    if (regime==0){
        options.c_cc[VTIME]=vtime;
        options.c_cc[VMIN]=vmin;
        if (echo==1){
            options.c_lflag|=ECHO;
        }
        else if (echo==0)
            options.c_lflag&=~ECHO;
        else
            return -1;
        if (sigint==1)
            options.c_lflag|=ISIG;
        else if (sigint==0)
            options.c_lflag&=~ISIG;
        else
            return -1;
    }
    if (tcsetattr(STDIN_FILENO,TCSANOW,&options)!=0)
        return -1;
    return 0;
}
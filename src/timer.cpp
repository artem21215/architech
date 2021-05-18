//
// Created by artem on 16.05.2021.
//
#include <sys/time.h>
#include "mySimpleComputer.h"
#include <signal.h>
#include "timer.h"
#include "printConsole.h"
#include "cu.h"
struct itimerval newTime, oldTime;
void res_signal(){
    raise(SIGUSR1);
}
void sighandler (int signo){
    sc_memoryInit();
    accum=0;
    instructioncounter=0;
    flag=0;
    printConsole(deltx,delty);
}
void reset(){
    signal(SIGUSR1, sighandler);
}
void stopHandler(int signaly){
    newTime.it_interval.tv_sec = 0;
    newTime.it_interval.tv_usec = 0;
    newTime.it_value.tv_sec = 0;
    newTime.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &newTime, &oldTime);
}
void handler(int signaly){
    cu();
}
void my_timer(){
    signal(SIGALRM, handler);
    newTime.it_interval.tv_sec = 0;
    newTime.it_interval.tv_usec = 500000;
    newTime.it_value.tv_sec = 0;
    newTime.it_value.tv_usec = 500000;
    setitimer(ITIMER_REAL, &newTime, &oldTime);
}

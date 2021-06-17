//
// Created by ilya on 08.05.2021.
//

#ifndef ARCHITECH_MYREADKEY_H
#define ARCHITECH_MYREADKEY_H
enum keys{
    l,
    s,
    t,
    i,
    r,
    F5,
    F6,
    e
};
int rk_readkey(keys & keys);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
int get_int_from_terminal(int &val);
int doInstrCounter();
int doAccum();
int doTimer();
#endif //ARCHITECH_MYREADKEY_H

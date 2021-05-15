//
// Created by artem on 08.05.2021.
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
#endif //ARCHITECH_MYREADKEY_H

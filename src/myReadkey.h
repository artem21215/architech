//
// Created by artem on 08.05.2021.
//

#ifndef ARCHITECH_MYREADKEY_H
#define ARCHITECH_MYREADKEY_H
enum keys{
    F5,
    F6
};
int rk_readkey(enum keys *);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
#endif //ARCHITECH_MYREADKEY_H

//
// Created by ilya on 15.03.2021.
//

#ifndef ARCHITECTURE_PSEVDO_H
#pragma once
#define ARCHITECTURE_PSEVDO_H
enum colors{
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYANIC,
    WHITE
};

int my_clrscr();
int mt_gotoXY(int i, int j);
int mt_setfgcolor(enum colors cur_col);
int mt_setbgcolor(enum colors cur_col2);
int mt_getscreensize(int *rows, int *cols);
int mt_setDefaultColorSettings();
#endif //ARCHITECTURE_PSEVDO_H


//
// Created by ilya on 19.05.2021.
//

#ifndef ARCHITECH_MYSIMPLEASSEBLER_H
#define ARCHITECH_MYSIMPLEASSEBLER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
using namespace std;
struct layers{
    string comb="";
    string val="";
    int num_mem=0;
};
vector<short> mem(100);
int pointer=0;
map<int,layers> prog;
vector<string> ans;
vector<string> myconst;
int calc_pos(string &help);
void parse_AC(string &spos, string &scom, string &sval);
int check_up(string spos, string scom, string sval);
int func_input(int prior);
int parse_basic(string spos, string scom, string sval);
int func_output(int prior);
int func_if_goto(int prior);
int SimpleBasic(string namebsk);
int sc_commandEncode (int command, int operand, int * value){
    *value=0;
    for (int i=0;i<7;++i){
        int elem=operand&(1<<i);
        if (elem!=0){
            *value=*value|(1<<i);
        }
    }
    for (int i=0;i<7;++i){
        int elem=command&(1<<i);
        if (elem!=0){
            *value=*value|(1<<(i+7));
        }
    }
    return 0;
}
#endif //ARCHITECH_MYSIMPLEASSEBLER_H

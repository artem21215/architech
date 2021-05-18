#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
vector<short> mem(100);
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
    //*value|=(1<<14);
    return 0;
}
void parse(string &spos, string &scom, string &sval){
    int pos=(spos[0]-'0')*10+spos[1]-'0';
    int val=(sval[0]-'0')*10+sval[1]-'0';
    int com=0;
    if (scom=="READ")
        com=10;
    else if (scom=="WRITE")
        com=11;
    else if (scom=="LOAD")
        com=20;
    else if (scom=="STORE")
        com=21;
    else if (scom=="")
        com=10;
    else if (scom=="ADD")
        com=30;
    else if (scom=="SUB")
        com=31;
    else if (scom=="DIVIDE")
        com=32;
    else if (scom=="MUL")
        com=33;
    else if (scom=="JUMP")
        com=40;
    else if (scom=="JNEG")
        com=41;
    else if (scom=="JZ")
        com=42;
    else if (scom=="HALT")
        com=43;
    else if (scom=="ADDC")
        com=65;
    else if (scom=="="){
        cout << endl;
        cout << sval << endl;
        int z=(sval[1]-'0')*16*16*16+(sval[2]-'0')*16*16+(sval[3]-'0')*16+(sval[4]-'0');
        if (sval[0]=='-'){
            mem[pos]=-z;
        }
        else
            mem[pos]=z;
        return;
    }
    int coded;
    //cout << pos << ' ' << com << ' ' << val << endl;
    if (sc_commandEncode(com,val,&coded)==0){
        mem[pos]=coded;
        //cout << mem[pos] << ' ' << com << ' ' << val << endl;
    }
    else{
        cout << "error code" << endl;
        return;
    }
}
void SimpleBasic();
int main(int argc, char *argv[]){
    //SimpleBasic();
    ifstream in(argv[1]);
    string line;
    string pos,com,val;
    cout << endl;
    string word;
    vector<string> help;
    while (getline(in,line)){
        for (int i=0;i<line.size();++i){
            if (line[i]!=' '){
                word+=line[i];
            }
            else
                if (word.size()!=0){
                    //cout << word << endl;
                    help.push_back(word);
                    word="";
                }
        }
        if (word.size()!=0){
            help.push_back(word);
            word="";
        }
        pos=help[0];
        com=help[1];
        val=help[2];
        help.clear();
        parse(pos,com,val);
    }
    in.close();
    for (auto v:mem)
        cout << v << ' ';

    ofstream out("../input.o");
    for (int i=0;i<mem.size();++i){
        out << mem[i] << ' ';
    }
    out.close();
   /* cout << endl;
    cout << "name file: ";
    cout << filename << endl;*/
    return 0;
}
/*void SimpleBasic(){

}*/


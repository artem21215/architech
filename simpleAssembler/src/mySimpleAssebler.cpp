#include "mySimpleAssebler.h"
void parse_AC(string &spos, string &scom, string &sval){
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
        int z=(sval[1]-'0')*16*16*16+(sval[2]-'0')*16*16+(sval[3]-'0')*16+(sval[4]-'0');
        if (sval[0]=='-'){
            mem[pos]=-z;
        }
        else
            mem[pos]=z;
        return;
    }
    int coded;
    if (sc_commandEncode(com,val,&coded)==0){
        mem[pos]=coded;
    }
    else{
        cout << "error code" << endl;
        return;
    }
}
int main(int argc, char *argv[]){
    string name_bsk;
    for (int i=0;;++i){
        if (argv[1][i]==0)
            break;
        name_bsk+=argv[1][i];
    }
    if (SimpleBasic(name_bsk)) {
        cout << "Error translation from basic to accembler" << endl;
        return 1;
    }
    ifstream in("myprog.sa");
    string line;
    string pos,com,val;
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
        parse_AC(pos,com,val);
    }
    in.close();

    ofstream out("../input.o");
    for (int i=0;i<mem.size();++i){
        out << mem[i] << ' ';
    }
    out.close();
    cout << "Compile accepted!" << endl;
    return 0;
}

int check_up(string spos, string scom, string sval){
    if (scom=="REM")
        return 0;
    for (auto &v:spos){
        if (v<'0' || v>'9') {
            return 1;
        }
    }
    for (auto &v:scom){
        if (v<'A' || v>'Z') {
            return 1;
        }
    }
    if (scom=="END")
        return 0;
    for (auto &v:sval){
        if (v>='a' && v<='z') {
            return 1;
        }
    }
    return 0;
}

int func_output(int prior){
    prog[prior].num_mem=pointer++;
    string buf;
    if (pointer<10)
        buf+='0';
    buf+=to_string(prog[prior].num_mem);
    buf+=' ';
    buf+="WRITE ";
    buf+=to_string(99-(prog[prior].val[0]-'A'));
    cout << buf << endl;
    ans.push_back(buf);
    return 0;
}

int func_input(int prior){
    prog[prior].num_mem=pointer++;
    string buf;
    if (pointer<10)
        buf+='0';
    buf+=to_string(prog[prior].num_mem);
    buf+=' ';
    buf+="READ ";
    buf+=to_string(99-(prog[prior].val[0]-'A'));
    cout << buf << endl;
    ans.push_back(buf);
    return 0;
}

int func_end(int prior){
    prog[prior].num_mem=pointer++;
    string buf;
    if (pointer<10)
        buf+='0';
    buf+=to_string(prog[prior].num_mem);
    buf+=' ';
    buf+="HALT ";
    cout << buf << endl;
    ans.push_back(buf);
    return 0;
}

int func_if_goto(int prior){
    string buf;
    prog[prior].num_mem=pointer++;
    if (pointer<10)
        buf+='0';
    buf+=to_string(pointer-1);
    buf+=" LOAD ";
    string sval=prog[prior].val;
    buf+=to_string(99-sval[0]+'A');
    cout << buf << endl;
    ans.push_back(buf);

    buf.clear();
    pointer++;
    int i=sval.size()-1;
    while (sval[i]>='0' && sval[i]<='9')
        --i;
    ++i;
    buf+="~";
    for (;i<sval.size();++i)
        buf+=sval[i];
    buf+='~';
    if (pointer<10)
        buf+='0';
    buf+=to_string(pointer-1);
    buf+=' ';
    if (sval[1]=='=')
        buf+="JZ ";
    else if (sval[1]=='<')
        buf+="JNEG";
    else
        return 1;
    cout << buf << endl;
    ans.push_back(buf);
    return 0;
}

int func_goto(int prior){
    prog[prior].num_mem=pointer++;
    string buf;
    buf+="~";
    buf+=prog[prior].val;
    buf+="~";
    if (pointer<10)
        buf+='0';
    buf+=to_string(prog[prior].num_mem);
    buf+=' ';
    buf+="JUMP ";
    cout << buf << endl;
    ans.push_back(buf);
    return 0;
}

int func_let(int prior){

    return 0;
}
int parse_basic() {
    for (auto &v:prog) {
        //cout <<"##" << v.first << ' ' << v.second.num_mem << ' ' << v.second.comb << ' ' << v.second.val << endl;
        if (v.second.comb == "INPUT") {
            func_input(v.first);
        }
        else if (v.second.comb=="OUTPUT"){
            func_output(v.first);
        }
        else if (v.second.comb=="IF"){
            func_if_goto(v.first);
        }
        else if (v.second.comb=="GOTO"){
            func_goto(v.first);
        }
        else if (v.second.comb=="END"){
            func_end(v.first);
        }
        else if (v.second.comb=="LET"){
            func_let(v.first);
        }
    }
    return 0;
}
int calc_pos(string &help){
    int pos=0;
    for (int i=0;i<help.size();++i){
        pos=pos*10+help[i]-'0';
    }
    return pos;
}
int SimpleBasic(string namebsk) {
    //cout << namebsk << endl;
    ifstream in(namebsk);
    string line;
    string pos, com, val;
    string word;
    vector<string> help;
    while (!in.eof()) {
        getline(in, line);
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] != ' ' || help.size() == 2 && !word.empty()) {
                word += line[i];
            } else if (word.size() != 0) {
                //cout << word << endl;
                help.push_back(word);
                word = "";
            }
        }
        if (word.size() != 0) {
            help.push_back(word);
            word = "";
        }
        pos = help[0];
        com = help[1];
        val = help[2];
        int position = calc_pos(help[0]);
        prog[position].comb = com;
        prog[position].val = val;
        help.clear();
        if (check_up(pos, com, val)) {
            in.close();
            return 1;
        }
    }
    cout << endl;
    parse_basic();
    return 0;
}


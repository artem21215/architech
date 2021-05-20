#include "mySimpleAssebler.h"
void parse_AC(string &spos, string &scom, string &sval){
    int pos=(spos[0]-'0')*10+spos[1]-'0';
    int val;
    if (sval.size()==1)
        val=sval[0]-'0';
    else
        val=(sval[0]-'0')*10+sval[1]-'0';
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
            cout << endl;
            return 1;
        }
    }
    return 0;
}

int func_output(int prior){
    prog[prior].num_mem=pointer++;
    string buf;
    if (pointer<10+1)
        buf+='0';
    buf+=to_string(prog[prior].num_mem);
    buf+=' ';
    buf+="WRITE ";
    buf+=to_string(99-(prog[prior].val[0]-'A'));
    ans.push_back(buf);
    return 0;
}

int func_input(int prior){
    prog[prior].num_mem=pointer++;
    string buf;
    if (pointer<10+1)
        buf+='0';
    buf+=to_string(prog[prior].num_mem);
    buf+=' ';
    buf+="READ ";
    buf+=to_string(99-(prog[prior].val[0]-'A'));
    ans.push_back(buf);
    return 0;
}

int func_end(int prior){
    prog[prior].num_mem=pointer++;
    string buf;
    if (pointer<10+1)
        buf+='0';
    buf+=to_string(prog[prior].num_mem);
    buf+=' ';
    buf+="HALT ";
    ans.push_back(buf);
    return 0;
}

int func_if_goto(int prior){
    string buf;
    prog[prior].num_mem=pointer++;
    if (pointer<10+1)
        buf+='0';
    buf+=to_string(pointer-1);
    buf+=" LOAD ";
    string sval=prog[prior].val;
    buf+=to_string(99-sval[0]+'A');
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
    if (pointer<10+1)
        buf+='0';
    buf+=to_string(pointer-1);
    buf+=' ';
    if (sval[1]=='=')
        buf+="JZ ";
    else if (sval[1]=='<')
        buf+="JNEG";
    else
        return 1;
    ans.push_back(buf);
    return 0;
}

int func_goto(int prior){
    prog[prior].num_mem=pointer++;
    string buf;
    buf+="~";
    buf+=prog[prior].val;
    buf+="~";
    if (pointer<10+1)
        buf+='0';
    buf+=to_string(prog[prior].num_mem);
    buf+=' ';
    buf+="JUMP ";
    ans.push_back(buf);
    return 0;
}
int do_polsk(char ch, stack<char> &oper, map<char,int> &prior_oper, string &polsk){
    if (ch>='A' && ch<='Z'){
        polsk+=ch;
    }
    else{
        if (oper.empty())
            oper.push(ch);
        else{
            char top=oper.top();
            while (prior_oper[top]<=prior_oper[ch] && ch!='('){
                oper.pop();
                polsk += top;
                if (oper.empty())
                    break;
                top=oper.top();
                if (top=='(')
                    break;
            }
            if (ch!=')')
                oper.push(ch);
            else
                oper.pop();
        }
    }
    return 0;
}

int cnt_var_let=0;
int calc_polsk(string polsk){
    if (polsk.size()==1){
        string buf;
        pointer++;
        if (pointer<10+1)
            buf+='0';
        buf+=to_string(pointer-1);
        buf+=' ';
        buf+="LOAD ";
        buf+=to_string(99-polsk[0]+'A');
        ans.push_back(buf);
        buf.clear();
    }
    stack<char> simb;
    string buf;
    for (auto v:polsk){
        if (v>='A' && v<='Z'){
            simb.push(v);
        }
        else{
            char v2=simb.top();
            simb.pop();
            char v1=simb.top();
            simb.pop();

            pointer++;
            if (pointer<10+1)
                buf+='0';
            buf+=to_string(pointer-1);
            buf+=' ';
            buf+="LOAD ";
            buf+=to_string(99-v1+'A');
            ans.push_back(buf);
            buf.clear();
            char ch=v;
            if (ch=='+'){
                pointer++;
                if (pointer<10+1)
                    buf+='0';
                buf+=to_string(pointer-1);
                buf+=' ';
                buf+="ADD ";
                buf+=to_string(99-v2+'A');
                ans.push_back(buf);
            }
            else if (ch=='-'){
                pointer++;
                if (pointer<10+1)
                    buf+='0';
                buf+=to_string(pointer-1);
                buf+=' ';
                buf+="SUB ";
                buf+=to_string(99-v2+'A');
                ans.push_back(buf);
            }
            else if (ch=='/'){
                pointer++;
                if (pointer<10+1)
                    buf+='0';
                buf+=to_string(pointer-1);
                buf+=' ';
                buf+="DIVIDE ";
                buf+=to_string(99-v2+'A');
                ans.push_back(buf);
            }
            else if (ch=='*'){
                pointer++;
                if (pointer<10+1)
                    buf+='0';
                buf+=to_string(pointer-1);
                buf+=' ';
                buf+="MUL ";
                buf+=to_string(99-v2+'A');
                ans.push_back(buf);
            }

            buf.clear();
            pointer++;
            simb.push('Z'+1+cnt_var_let);
            if (pointer<10+1)
                buf+='0';
            buf+=to_string(pointer-1);
            buf+=' ';
            buf+="STORE ";
            buf+=to_string(99-26-cnt_var_let);
            cnt_var_let++;
            ans.push_back(buf);
            buf.clear();
        }
    }
    return 0;
}

int assign_to_let_var(char var){
    pointer++;
    string buf;
    char rez=99-26-cnt_var_let;
    if (pointer<10+1)
        buf+='0';
    buf+=to_string(pointer-1);
    buf+=' ';
    buf+="STORE ";
    buf+=to_string(99-var+'A');
    ans.push_back(buf);
    return 0;
}
int func_let(int prior){
    prog[prior].num_mem=pointer;
    map<char,int> prior_oper;
    prior_oper['(']=3;
    prior_oper[')']=3;
    prior_oper['*']=1;
    prior_oper['/']=1;
    prior_oper['+']=2;
    prior_oper['-']=2;
    string polsk,sval=prog[prior].val;
    if (sval[2]>='0' && sval[2]<='9')
        return 0;
    stack<char> oper;
    for (int i=2;i<sval.size();++i){
        do_polsk(sval[i],oper,prior_oper,polsk);
    }
    while (!oper.empty()){
        char top=oper.top();
        polsk+=top;
        oper.pop();
    }
    calc_polsk(polsk);
    assign_to_let_var(prog[prior].val[0]);
    return 0;
}
int func_const(int prior){
    string buf;
    string sval=prog[prior].val;
    buf+=to_string(99-sval[0]+'A');
    buf+=" = +";
    string const_var;
    for (int i=2;i<sval.size();++i)
        const_var+=sval[i];

    for (int i=0;i<4-const_var.size();++i)
        buf+='0';
    buf+=const_var;
    myconst.push_back(buf);
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
            if (v.second.val[2]>='0' && v.second.val[2]<='9')
                func_const(v.first);
            else
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
int delete_space(string &sval){
    string help;
    for (auto v:sval){
        if (v!=' ')
            help+=v;
    }
    return 0;
}
void fix_translate(){
    for (auto &v:ans){
        if (v[0]=='~'){
            string fix;
            string to;
            int i;
            for (i=1;v[i]!='~';++i)
                to+=v[i];
            i++;
            for (;i<v.size();++i)
                fix += v[i];
            fix+=to_string(prog[calc_pos(to)].num_mem);
            v=fix;
        }
        else if (v[0]=='$'){
            string fix;
            if (pointer<10)
                fix+='0';
            fix+=to_string(pointer++);
            fix+=' ';
            for (int i=2;i<v.size();++i)
                fix+=v[i];
            v=fix;
        }
    }
}
void add_myconst(){
    for (auto &v:myconst)
        ans.push_back(v);
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
        delete_space(val);
        int position = calc_pos(help[0]);
        prog[position].comb = com;
        prog[position].val = val;
        help.clear();
        if (check_up(pos, com, val)) {
            in.close();
            return 1;
        }
    }
    parse_basic();
    add_myconst();
    fix_translate();

    ofstream out("myprog.sa");
    for (auto &v:ans)
        out << v << '\n';
    out.close();
    return 0;
}


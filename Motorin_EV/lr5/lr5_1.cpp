#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

#define forn(n, p) for(int n = 0; n < p; n++)

using namespace std;
const int k=5;
const string sym = "ACGTN";

struct numbers{
    numbers(int f, int s): first(f), second(s)
    {}
    int first;
    int second;
};
struct bohr_vrtx{
    int next_vrtx[k],pat_num,suff_link,auto_move[k],par,suff_flink;
    bool flag;
    int number;
    char symb;
};

vector<numbers> num;
vector<bohr_vrtx> bohr;
vector<string> pattern;

bohr_vrtx make_bohr_vrtx(int p,char c){
    bohr_vrtx v;
    memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
    memset(v.auto_move, 255, sizeof(v.auto_move));
    v.flag=false;
    v.suff_link=-1;
    v.par=p;
    v.symb=c;
    v.suff_flink=-1;
    return v;
}
void bohr_ini(){
    bohr.push_back(make_bohr_vrtx(-1,-1));
}
void add_string_to_bohr(string& s,int n){
    int num=0;
    for (int i=0; i<s.length(); i++){
        char ch = sym.find(s[i]);
        if (bohr[num].next_vrtx[ch]==-1){
            bohr.push_back(make_bohr_vrtx(num,ch));
            bohr[num].next_vrtx[ch]=bohr.size()-1;
        }
        num=bohr[num].next_vrtx[ch];
    }
    bohr[num].flag=true;
    bohr[num].number = n;
    pattern.push_back(s);
    bohr[num].pat_num=pattern.size()-1;
}
int get_auto_move(int v, char ch);
int get_suff_link(int v){
    if (bohr[v].suff_link==-1)
        if (v==0||bohr[v].par==0)
            bohr[v].suff_link=0;
        else
            bohr[v].suff_link=get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
    return bohr[v].suff_link;
}
int get_auto_move(int v, char ch){
    if (bohr[v].auto_move[ch]==-1)
        if (bohr[v].next_vrtx[ch]!=-1)
            bohr[v].auto_move[ch]=bohr[v].next_vrtx[ch];
        else
            if (v==0)
                bohr[v].auto_move[ch]=0;
            else
                bohr[v].auto_move[ch]=get_auto_move(get_suff_link(v), ch);
    return bohr[v].auto_move[ch];
}
int get_suff_flink(int v){
    if (bohr[v].suff_flink==-1){
        int u=get_suff_link(v);
        if (u==0)
            bohr[v].suff_flink=0;
        else
            bohr[v].suff_flink=(bohr[u].flag)?u:get_suff_flink(u);
    }
    return bohr[v].suff_flink;
}
void check(int v,int i){
    for(int u=v;u!=0;u=get_suff_flink(u)){
        if (bohr[u].flag)
            num.push_back(numbers(i-pattern[bohr[u].pat_num].length()+1,bohr[u].number));
    }
}
void find_all_pos(const string& s){
    int u=0;
    forn(i, s.length()){
        u=get_auto_move(u,sym.find(s[i]));
        check(u,i+1);
    }
}
int main(){
    string inp;
    int n;
    cin >> inp >> n;
    bohr_ini();
    forn (i, n){
        string line;
        cin >> line;
        add_string_to_bohr(line,i+1);
    }
    find_all_pos(inp);
    forn (i, num.size()){
        cout << num[i].first << " " << num[i].second << endl;
    }
}

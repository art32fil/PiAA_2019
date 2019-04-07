#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;
const string alphabet = "ACGTN";
const int k = 5;

struct bohr_vrtx{
   map<char, int> next_vrtx;//next_vrtx[i] — номер вершины, в которую мы придем по символу с номером i в алфавите
   int pat_num;// pat_num — номер строки-образца, обозначаемого этой вершиной
   int suff_link; //suff_link - суффиксная ссылка
   map<char, int> auto_move; //auto_move - запоминание перехода автомата
   int par; //par - вершина-отец в дереве
   int suff_flink; //suff_flink - "хорошая" суф. ссылка
   bool flag; //flag — бит, указывающий на то, является ли наша вершина исходной строкой
   char symb; //символ на ребре от par к этой вершине
   bohr_vrtx(int p,char c){
       for(int i=0;i<alphabet.size();i++){
           next_vrtx[i] = -1;
           auto_move[i] = -1;}
       flag=false;
       suff_link=-1;
       par=p;
       symb=c;
       suff_flink=-1;
   }
};


using namespace std;
class Acho_Corasick{

    vector<bohr_vrtx> bohr;
    vector<string> pattern;
    string text;
public:
    Acho_Corasick(string texts, vector<string> patterns) : text(texts){
    bohr.push_back(bohr_vrtx(-1,-1));
    for (int i=0;i<patterns.size();i++){
                add_string_to_bohr(patterns[i]);
        }
    }
    void find_all_pos(){
        int u=0;
        for(int i=0;i<text.length();i++){
            u=get_auto_move(u,alphabet.find(text[i]));
            check(u,i+1);
        }
    }
private:



    void add_string_to_bohr(string& s){
       int num=0;
       for (int i=0; i<s.length(); i++){
          char ch = alphabet.find(s[i]);
          if (bohr[num].next_vrtx[ch]==-1){
             bohr.push_back(bohr_vrtx(num,ch));
             bohr[num].next_vrtx[ch]=bohr.size()-1;
             }
          num=bohr[num].next_vrtx[ch];
       }
       bohr[num].flag=true;
       pattern.push_back(s);
       bohr[num].pat_num=pattern.size()-1;
    }


    int get_suff_link(int v){
       if (bohr[v].suff_link==-1)
          if (v==0||bohr[v].par==0){
             bohr[v].suff_link=0;}
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
            if (bohr[u].flag){
            cout<<i-pattern[bohr[u].pat_num].length()+1<<" "<<bohr[u].pat_num+1<<endl;}
        }
    }

};
//
// Created by 1 on 08.03.2019.
//

#ifndef AXOKARASIK_JOKER_H
#define AXOKARASIK_JOKER_H
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct FlagEnd{
    bool flag;
    vector<int> count_pattern;
};

struct Vertex{
    FlagEnd flagEnd;
    map<char,int> next;
    map<char,int> auto_move;
    int suffix_link;
    int parent;
    char symbol;

    Vertex(int parent,char symbol) {
        this->flagEnd.flag=false;
        this->suffix_link=-1;
        this->parent=parent;
        this->symbol=symbol;
    }
};

class AxoKarasikWithJoker{
public:
    AxoKarasikWithJoker(string strWithJoker){
        borh.push_back(Vertex(0,0));
        count=1;
        this->strWithJoker=strWithJoker;
    }

    void addPattern(const string &pattern,int index){
        int cur_ver=0;//стоим в корне
        this->patterns.push_back(pair<string,int>(pattern,index));
        for(char symbol:pattern){
            if(borh[cur_ver].next.find(symbol)==borh[cur_ver].next.end()){
                borh.push_back(Vertex(cur_ver,symbol));
                borh[cur_ver].next[symbol]=count++;
            }
            cur_ver=borh[cur_ver].next[symbol];
        }
        borh[cur_ver].flagEnd.flag=true;
        borh[cur_ver].flagEnd.count_pattern.push_back(this->patterns.size());
    }

    void searchString(const string& str){
        vector<int>C(str.size(),0);
        int cur_ver=0;
        for(int i=0;i<str.size();i++){
            cur_ver=get_auto_move(cur_ver,str[i]);
            for(int ver=cur_ver;ver!=0;ver=get_suffix_link(ver)){
                if(borh[ver].flagEnd.flag){
                    for(int index=0;index<borh[ver].flagEnd.count_pattern.size();index++) {
                        int count_pattern = borh[ver].flagEnd.count_pattern[index];
                        int position = i - patterns[count_pattern - 1].first.size() + 1;
                        if(position - patterns[count_pattern - 1].second>=0) {
                            if (count_pattern == 1) {
                                C[position - patterns[count_pattern - 1].second]++;
                            } else if (C[position - patterns[count_pattern - 1].second] != 0) {
                                C[position - patterns[count_pattern - 1].second]++;
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i<C.size();i++){
            if(C[i]==patterns.size()&&((i+strWithJoker.size()<=C.size()))){
                cout<<i+1<<endl;
            }
        }

    }


private:
    vector<Vertex> borh;
    vector<pair<string,int>> patterns;
    string strWithJoker;
    int count;

    int get_suffix_link(int vertex){
        if(borh[vertex].suffix_link==-1)
            if(vertex==0||borh[vertex].parent==0)
                borh[vertex].suffix_link=0;
            else
                borh[vertex].suffix_link=get_auto_move(get_suffix_link(borh[vertex].parent),borh[vertex].symbol);
        return borh[vertex].suffix_link;
    }

    int get_auto_move(int vertex,char symbol){
        if(borh[vertex].auto_move.find(symbol)==borh[vertex].auto_move.end())
            if(borh[vertex].next.find(symbol)!=borh[vertex].next.end())
                borh[vertex].auto_move[symbol]=borh[vertex].next[symbol];
            else
                borh[vertex].auto_move[symbol]= ((vertex==0) ? 0:get_auto_move(get_suffix_link(vertex),symbol));
        return borh[vertex].auto_move[symbol];
    }

};
#endif //AXOKARASIK_JOKER_H

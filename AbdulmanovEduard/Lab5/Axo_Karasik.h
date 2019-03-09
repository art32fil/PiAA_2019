//
// Created by 1 on 08.03.2019.
//

#ifndef AXOKARASIK_AXO_KARASIK_H
#define AXOKARASIK_AXO_KARASIK_H
#include <map>
#include <vector>
#include <iostream>

using namespace std;

struct FlagEnd{
    bool flag;
    int count_pattern;
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
        this->flagEnd.count_pattern=0;
        this->suffix_link=-1;
        this->parent=parent;
        this->symbol=symbol;
    }
};

class AxoKarasik{
public:
    AxoKarasik(){
        borh.push_back(Vertex(0,0));
        count=1;
    }

    void addPattern(const string &pattern){
        int cur_ver=0;//стоим в корне
        this->pattern.push_back(pattern);
        for(char symbol:pattern){
            if(borh[cur_ver].next.find(symbol)==borh[cur_ver].next.end()){
                borh.push_back(Vertex(cur_ver,symbol));
                borh[cur_ver].next[symbol]=count++;
            }
            cur_ver=borh[cur_ver].next[symbol];
        }
        borh[cur_ver].flagEnd.flag=true;
        borh[cur_ver].flagEnd.count_pattern=this->pattern.size();
    }

    void searchString(const string& str){
        int cur_ver=0;
        for(int i=0;i<str.size();i++){
            cur_ver=get_auto_move(cur_ver,str[i]);
            for(int ver=cur_ver;ver!=0;ver=get_suffix_link(ver)){
                if(borh[ver].flagEnd.flag){
                    int count_pattern=borh[ver].flagEnd.count_pattern;
                    int position=i-pattern[count_pattern-1].size()+2;
                    cout<<position<<" "<<count_pattern<<endl;
                }
            }
        }
    }


private:
    vector<Vertex> borh;
    vector<string> pattern;
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
#endif //AXOKARASIK_AXO_KARASIK_H

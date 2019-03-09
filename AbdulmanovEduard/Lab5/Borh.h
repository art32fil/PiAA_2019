//
// Created by 1 on 07.03.2019.
//

#ifndef AXOKARASIK_BORH_H
#define AXOKARASIK_BORH_H

#include <map>
#include <vector>

using namespace std;

struct Vertex{
    bool flag;
    map<char,int> next;
    Vertex() { this->flag=false;}
};

class SearchInBor{
public:
    SearchInBor(){
        borh.push_back(Vertex());
        count=1;
    }

    void addPattern(const string &pattern){
        int cur_ver=0;//стоим в корне
        for(char symbol:pattern){
            if(borh[cur_ver].next.find(symbol)==borh[cur_ver].next.end()){
                borh.push_back(Vertex());
                borh[cur_ver].next[symbol]=count++;
            }
            cur_ver=borh[cur_ver].next[symbol];
        }
        borh[cur_ver].flag=true;
    }

    bool searchString(const string& str){
        int cur_ver=0;
        for(char symbol:str){
            if(borh[cur_ver].next.find(symbol)==borh[cur_ver].next.end())
                return false;
            cur_ver=borh[cur_ver].next[symbol];
        }
        if(borh[cur_ver].flag)
            return true;
        return false;
    }

private:
    vector<Vertex> borh;
    int count;
};
#endif //AXOKARASIK_BORH_H

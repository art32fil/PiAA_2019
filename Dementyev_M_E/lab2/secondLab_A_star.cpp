//
//  main.cpp
//  AStar
//
//  Created by Михаил Дементьев on 25/02/2019.
//  Copyright © 2019 Михаил Дементьев. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct finishWay {
    char start;
    char finish;
}start_finish;

struct ways {
    char stPos;
    char finPos;
    double len;
};

struct newWay {
    vector<char> way;
    double len;
};

bool customer_sorter(ways const& lhs, ways const& rhs) { //Сортировка по возрастанию близости к конечной вершине
    
    return ((int)(lhs.finPos) - start_finish.finish) < ((int)(rhs.finPos) - start_finish.finish);
}

int main() {
    
    vector<struct newWay> answerWays;
    int countOfWays = 0;
    answerWays.resize(100);
    vector<ways> ways;
    vector<char> bestWay;
    bool endFlag = false;
    
    cin >> start_finish.start >> start_finish.finish;
    
    int flagCount = 0;
    while (1){
        struct ways way;
        
        if(way.finPos == start_finish.finish)
            flagCount++;
        if(flagCount>1) break;
        
        if(!(cin >> way.stPos)){
            break;
        }
        if(!(cin >> way.finPos)){
            break;
        }
        if(!(cin >> way.len)){
            break;
        }
        ways.push_back(way);
    }
    
    sort(ways.begin(), ways.end(), &customer_sorter);
    
    answerWays[countOfWays].way.push_back(start_finish.start);
    answerWays[countOfWays].len = 0;
    countOfWays++;
    
    while(!endFlag){
        vector<struct ways>tempWay;
        for(int i = 0; i < countOfWays; i++){
            for(int j = 0; j < ways.size(); j++){
                if(answerWays[i].way[answerWays[i].way.size()-1] == ways[j].stPos){
                    tempWay.push_back({ways[j].stPos, ways[j].finPos, answerWays[i].len+ways[j].len});
                    //ways.erase(ways.begin()+j);
                }
            }
        }
        
        struct ways bestTempWay;
        bestTempWay.len = 500;
        for(int i = 0; i < tempWay.size(); i++){
            if(tempWay[i].len < bestTempWay.len){
                bestTempWay = tempWay[i];
            } else if (tempWay[i].len == bestTempWay.len){
                if(tempWay[i].finPos > bestTempWay.finPos){
                    bestTempWay = tempWay[i];
                }
                if(tempWay[i].stPos > bestTempWay.stPos){
                    bestTempWay = tempWay[i];
                }
            }
        }
        
        for(int i = 0; i < ways.size(); i++){
            if(ways[i].stPos == bestTempWay.stPos && ways[i].finPos == bestTempWay.finPos){
                ways.erase(ways.begin()+i);
            }
        }
        
        for(int i = 0; i < countOfWays; i++){
            if(answerWays[i].way[answerWays[i].way.size()-1] == bestTempWay.stPos){
                if(tempWay.size() > 1){
                    answerWays[countOfWays] = answerWays[i];
                    countOfWays++;
                }
                answerWays[i].way.push_back(bestTempWay.finPos);
                answerWays[i].len = bestTempWay.len;
                if(bestTempWay.finPos == start_finish.finish){
                    for(int i = 0; i < countOfWays; i++){
                        if(answerWays[i].way[answerWays[i].way.size()-1] == bestTempWay.stPos){
                            answerWays[i].way.push_back(bestTempWay.finPos);
                            answerWays[i].len = bestTempWay.len;
                        }
                    }
                }
                break;
            }
        }
        
        tempWay.erase(tempWay.begin(), tempWay.end());
        tempWay.clear();
        
        vector<char>tempBest;
        
        for(int i = 0; i < countOfWays; i++){
            if(answerWays[i].way[answerWays[i].way.size()-1] == start_finish.finish){
                if(!endFlag){
                    bestWay = answerWays[i].way;
                    endFlag = true;
                } else {
                    for(int j = 0; j < min(answerWays.size(), bestWay.size()); j++){
                        if(answerWays[i].way[j] > bestWay[j]){
                            bestWay = answerWays[i].way;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < bestWay.size(); i++){
        cout << bestWay[i];
    }
    
    return 0;
}


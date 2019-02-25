//
//  main.cpp
//  SecondLab2
//
//  Created by Михаил Дементьев on 24/02/2019.
//  Copyright © 2019 Михаил Дементьев. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
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

struct fork {
    char symbol;
    unsigned long ind;
    double len;
};

struct answer{
    vector<char> ans;
    vector<int> lenMass;
    double len;
};

bool customer_sorter(ways const& lhs, ways const& rhs) { //Сортировка по возрастанию близости к конечной вершине
    
    return ((int)(lhs.finPos) - start_finish.finish) < ((int)(rhs.finPos) - start_finish.finish);
}

int main() {
    
    vector<ways> ways;
    struct answer answer;           //Массив временных ответов
    struct answer realAnswer;       //Массив минимального ответа
    answer.len = 0;
    realAnswer.len = 1000;
    vector<fork> massOfForks;
    int indInForks = 0;
    
    //bool firstFlag = true;
    
    cin >> start_finish.start >> start_finish.finish;
    
    string data;
    //char* charData = new char[100];
    
    //struct ways way;
    
    int flagCount = 0;
    
    while (1){
        struct ways way;
        
        if(way.finPos == start_finish.finish)
            flagCount++;
        if(flagCount>0) break;
        
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
    /*
     for (int i = 0; i < ways.size(); i++){
     cout << ways[i].finPos;
     }
     */
    /*
     while (getline(cin, data)){
     if(firstFlag){
     
     start_finish.start = data[0];
     start_finish.finish = data[2];
     
     } else {
     struct ways way;
     
     charData = strdup(data.c_str());
     
     char* pch;
     pch = strtok(charData, " ");
     way.stPos = pch[0];
     
     pch = strtok(NULL, " ");
     way.finPos = pch[0];
     
     pch = strtok(NULL, " ");
     way.len = atof(pch);
     
     ways.push_back(way);
     }
     
     firstFlag = false;
     }
     */
    
    answer.ans.push_back(start_finish.start);
    answer.lenMass.push_back(0);
    
    while(1){       //Бесконечный цикл с условие выхода внутри
        struct ways ansWay;
        bool firstFlag = true;
        for (int i = 0; i < ways.size(); i++){  //Отличается от прошлого тем, что в массиве ответов помимо самих вершин мы сохраняем длину пути
            if(ways[i].stPos == answer.ans[answer.ans.size()-1]){
                if (firstFlag) {
                    ansWay = ways[i];
                    firstFlag = false;
                } else {
                    massOfForks.push_back({ways[i].finPos, answer.ans.size(), ways[i].len});
                    if((int)(ansWay.finPos) - (int)(start_finish.finish) < (int)(ways[i].finPos) - (int)(start_finish.finish)){
                        massOfForks[indInForks] = {ansWay.finPos, answer.ans.size(), ansWay.len};
                        ansWay = ways[i];
                    }
                    indInForks++;
                }
            }
        }
        if(firstFlag || answer.ans[answer.ans.size()-1] == start_finish.finish){ //Если не было найдено пути или мы в конечной точке
            if(massOfForks.size() == 0) //Если массив развилок пуст, заканчиваем работу алгоритма
                break;
            if(answer.ans[answer.ans.size()-1] == start_finish.finish){ //Если мы в конечной точке
                if(answer.len < realAnswer.len){    //Если временный ответ меньше минимального, присваиваем минимальному временный
                    realAnswer = answer;
                }
                for (unsigned long i = massOfForks[indInForks-1].ind; i < answer.lenMass.size(); i++){  //Во время очистки массива ответов вполоть до первой развилки, уменьшаем длинну пути.
                    answer.len -= answer.lenMass[i];
                }   //Продолжаем путь с первой развилки, обрезая справа массив ответов и удаляю последнюю развилку из массива непосещенных вершин
                answer.ans.erase(answer.ans.begin() + massOfForks[indInForks-1].ind, answer.ans.begin() + answer.ans.size());
                answer.lenMass.erase(answer.lenMass.begin() + massOfForks[indInForks-1].ind, answer.lenMass.begin() + answer.lenMass.size());
                answer.ans.push_back(massOfForks[indInForks-1].symbol);
                answer.lenMass.push_back(massOfForks[indInForks-1].len);
                answer.len += massOfForks[indInForks-1].len;
                massOfForks.erase(massOfForks.begin() + (massOfForks.size()-1));
                indInForks--;
            } else {    //Если мы не в конечной вершине
                for (unsigned long i = massOfForks[indInForks-1].ind; i < answer.lenMass.size(); i++){ //Во время очистки массива ответов вполоть до первой развилки, уменьшаем длинну пути.
                    answer.len -= answer.lenMass[i];
                } //Продолжаем путь с первой развилки, обрезая справа массив ответов и удаляю последнюю развилку из массива непосещенных вершин
                answer.ans.erase(answer.ans.begin() + massOfForks[indInForks-1].ind, answer.ans.begin() + answer.ans.size());
                answer.lenMass.erase(answer.lenMass.begin() + massOfForks[indInForks-1].ind, answer.lenMass.begin() + answer.lenMass.size());
                answer.ans.push_back(massOfForks[indInForks-1].symbol);
                answer.lenMass.push_back(massOfForks[indInForks-1].len);
                answer.len += massOfForks[indInForks-1].len;
                massOfForks.erase(massOfForks.begin() + (massOfForks.size()-1));
                indInForks--;
            }
        } else { //Если был найден путь, заносим его в массив ответов, увеличив при этом значение длинны
            answer.ans.push_back(ansWay.finPos);
            answer.lenMass.push_back(ansWay.len);
            answer.len += ansWay.len;
            firstFlag = true;
        }
    }
    
    for (int i = 0; i < realAnswer.ans.size(); i++){ //Выводим на экран массив ответов.
        cout << realAnswer.ans[i];
    }
    cout << endl;
    return 0;
}



//
//  main.cpp
//  SecondLab1
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
};

struct ways {
    char stPos;
    char finPos;
    double len;
};

struct fork {
    char symbol;
    unsigned long ind;
};

bool customer_sorter(ways const& lhs, ways const& rhs) { //Сортировка по убыванию длинн вершин
    
    return lhs.len > rhs.len;
}

int main() {
    
    finishWay start_finish;     //Переменная с стартовым и финальным значением
    vector<ways> ways;          //Массив путей
    vector<char> answer;        //Массив ответов
    vector<fork> massOfForks;   //Массив развилок (непосещенных вершин)
    int indInForks = 0;         //Индекс в массиве развилок
    
    //bool firstFlag = true;
    
    cin >> start_finish.start >> start_finish.finish; //Считывание стартового и финального положения
    
    string data;
    //char* charData = new char[100];
    
    int flagCount = 0;
    
    while (1){                  //Заполнение массива путей
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
    
    answer.push_back(start_finish.start);       //Помещение стартовой позиции в массив ответов
    
    while(answer[answer.size()-1] != start_finish.finish){   //Пока не окажемся в финальной позиции
        struct ways ansWay;
        bool firstFlag = true;              //Флаг для нахождения развилок
        for (int i = 0; i < ways.size(); i++){  //Ищем необходимую стартовую вершину в списке путей
            if(ways[i].stPos == answer[answer.size()-1]){   //Если данная вершина найдена
                if (firstFlag) {                            //Первая развилка
                    ansWay = ways[i];
                    firstFlag = false;
                } else {              //Если для данной стартовой позиции уже было записано значение в ответ, заносим данное состояние в массив непосещенных вершин
                    massOfForks.push_back({ways[i].finPos, answer.size()});
                    if(ansWay.len > ways[i].len){ //Если данная вершина имеет меньшую длинну, чем первая посещенная, меняем ее местами с вершиной из ответа
                        massOfForks[indInForks] = {ansWay.finPos, answer.size()};
                        ansWay = ways[i];
                    }
                    indInForks++; //Увеличиваем индекс массива непосещенных вершин
                }
            }
        }
        if(firstFlag){ //Если не было найдено ни одного возможного пути, возвращаемся к первой развилке и убираем ее из массива непосещенных вершин, продолжая путь с нее
            answer.erase(answer.begin() + massOfForks[indInForks-1].ind, answer.begin() + answer.size());
            answer.push_back(massOfForks[indInForks-1].symbol);
            massOfForks.erase(massOfForks.begin() + (massOfForks.size()-1));
            indInForks--;
        } else { //Если был найден путь, заносим его в массив ответов
            answer.push_back(ansWay.finPos);
            firstFlag = true;
        }
    }
    
    for (int i = 0; i < answer.size(); i++){ //Выводим содержимое массива ответов
        cout << answer[i];
    }
    cout << endl;
    
    return 0;
}


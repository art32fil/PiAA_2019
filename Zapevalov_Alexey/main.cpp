#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <queue>
#include "limits.h"
#include "math.h"

using namespace std;

struct node;

struct edge //Структура для хранения ребра и его веса
{
    edge(char n, float w) : name(n), weight(w) {}
    char name;
    float weight;
    int next = -1;
};

struct node //Структура для хранения вершины и исходящих ребер
{
    node(char n, edge dest = edge(' ', 0)) : name(n)
    {
        if( dest.name != ' ' )
            ways = {dest};
    }
    char name;
    int prev = -1;
    int relaxedweight = INT_MAX;
    vector<edge> ways; //Пути из вершины
};

typedef struct queueElem //элемент очереди с приоритетом
{
    queueElem(int f, int h, int i) : function(f), heur(h), index(i){}
    int function, heur, index;
}fhi;

int operator > (fhi pair1, fhi pair2) //сравнение элементов очереди по длине пути и эвристике
{
    if (pair1.function == pair2.function)
        return pair1.heur > pair2.heur;
    return pair1.function > pair2.function;
}

int find( char name, const vector<node>& nodes ) //поиск узла с нужным именем
{
    for(node& n : nodes)
        if( name == n.name )
            return &n - &nodes[0]; //возврат номера в массиве с нужным именем
    return -1; //если такого нет, то -1
}

int main(void) //ввод
{
    ifstream fin("input.txt");
    char begin, end;
    fin >> begin >> end;
    //cin >> begin >> end;
    char dest, source;
    float weight;
    vector<node> nodes;
    int index = 0;
    while( fin >> source >> dest >> weight ) //добавление пары узлов и их ребра
    {
        //while( cin >> source >> dest >> weight )
        //{
        index = find(source, nodes);
        if( index != -1 )
            nodes[index].ways.push_back(edge(dest, weight)); //добавление ребра при существующем первом узле
        else
        {
            nodes.push_back(node(source, edge(dest,weight))); //добавление ребра при отсутствующем первом узле
            index = &nodes.back() - &nodes[0];
        }
        if( find(dest, nodes) == -1 ) //добавление второго узла если он отсутствует
        {
            nodes.push_back(node(dest));
            nodes[index].ways.back().next = nodes.size() - 1;
        }
        else //если он существует
            nodes[index].ways.back().next = find(dest, nodes);
    }
    fin.close();
    priority_queue <fhi, vector<fhi>, greater<fhi> > q; //очередь индексов узлов по возрастанию веса и эвристики
    nodes[find(begin, nodes)].relaxedweight = 0;
    q.push(fhi(abs(end - begin), abs(end - begin), find(begin, nodes))); //добавление в очередь начального узла
    int curEnd = find(end, nodes);
    while (!q.empty())
    {
        fhi top = q.top();
        q.pop();
        for (auto& way : nodes[top.index].ways) //для всех исходящих ребер

            if (way.weight + nodes[top.index].relaxedweight < nodes[way.next].relaxedweight //релаксирует ли текущий путь узел
                    && way.weight + nodes[top.index].relaxedweight < nodes[curEnd].relaxedweight) //и меньше ли он лучшего результата
            {
                nodes[way.next].prev = top.index;
                nodes[way.next].relaxedweight = way.weight + nodes[top.index].relaxedweight;
                q.push(fhi(nodes[way.next].relaxedweight + end - way.name, end - way.name, way.next));
            }
    }
    string resultString; //вывод результата
    do {
        resultString += nodes[curEnd].name;
        curEnd = nodes[curEnd].prev;
    } while (curEnd != -1);
    reverse(resultString.begin(), resultString.end());
    cout << resultString << endl;
    return 0;
}

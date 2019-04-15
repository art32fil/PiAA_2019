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

typedef struct queueElem
{
    queueElem(int f, int h, int i) : function(f), heur(h), index(i){}
    int function, heur, index;
}fhi;

int operator > (fhi pair1, fhi pair2)
{
    if (pair1.function == pair2.function)
        return pair1.heur > pair2.heur;
    return pair1.function > pair2.function;
}

int find( char name, vector<node> nodes ) //поиск узла с нужным именем
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
    while( fin >> source >> dest >> weight )
    {
        //while( cin >> source >> dest >> weight )
        //{
        index = find(source, nodes);
        if( index != -1 )
            nodes[index].ways.push_back(edge(dest, weight));
        else
        {
            nodes.push_back(node(source, edge(dest,weight)));
            index = &nodes.back() - &nodes[0];
        }
        if( find(dest, nodes) == -1 )
        {
            nodes.push_back(node(dest));
            nodes[index].ways.back().next = nodes.size() - 1;
        }
        else
            nodes[index].ways.back().next = find(dest, nodes);
    }
    fin.close();
    priority_queue <fhi, vector<fhi>, greater<fhi> > q;
    nodes[find(begin, nodes)].relaxedweight = 0;
    q.push(fhi(abs(end - begin), abs(end - begin), find(begin, nodes)));
    int curEnd = find(end, nodes);
    while (!q.empty())
    {
        fhi top = q.top();
        q.pop();
        for (auto& way : nodes[top.index].ways)

            if (way.weight + nodes[top.index].relaxedweight < nodes[way.next].relaxedweight
                    && way.weight + nodes[top.index].relaxedweight < nodes[curEnd].relaxedweight)
            {
                nodes[way.next].prev = top.index;
                nodes[way.next].relaxedweight = way.weight + nodes[top.index].relaxedweight;
                q.push(fhi(nodes[way.next].relaxedweight + end - way.name, end - way.name, way.next));
            }
    }
    string resultString;
    do {
        resultString += nodes[curEnd].name;
        curEnd = nodes[curEnd].prev;
    } while (curEnd != -1);
    reverse(resultString.begin(), resultString.end());
    cout << resultString << endl;
    return 0;
}

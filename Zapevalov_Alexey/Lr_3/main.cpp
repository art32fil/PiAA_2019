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
    bool direction = true;
    int weight;
    int result;
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
    edge* prevedge = NULL;
    int min = 0;
    bool flag = NULL;
    vector<edge> ways; //Пути из вершины
};

typedef struct queueElem
{
    queueElem(int f, int i) : function(f), index(i){}
    int function, index;
}fhi;

typedef struct resultList
{
    resultList(char a, char b, int w) : first(a), second(b), weight(w){}
    char first, second;
    int weight;
} reslist;

int operator < (fhi pair1, fhi pair2)
{
    return pair1.function < pair2.function;
}

int operator > (reslist a, reslist b)
{
    if (a.first == b.first)
        return a.second > b.second;
    return a.first > b.first;
}

void clear( std::priority_queue <fhi> &q )
{
   std::priority_queue<fhi> empty;
   std::swap( q, empty );
}

int find(char name, vector<node> nodes) //поиск узла с нужным именем
{
    for(node& n : nodes)
        if(name == n.name)
            return &n - &nodes[0]; //возврат номера в массиве с нужным именем
    return -1; //если такого нет, то -1
}

int findedge (char name, vector<edge> ways)
{
    for (edge& n: ways)
        if (name == n.name)
            return &n - &ways[0]; //индекс в массиве
    return -1;
}

void forward(vector <node>& nodes, priority_queue <fhi>& q, fhi& top, int& max, char begin, char end)
{
    for (auto& way : nodes[top.index].ways)
        if (!nodes[way.next].flag && way.weight > 0)
        {
            nodes[way.next].prev = top.index;
            nodes[way.next].prevedge = &way;
            nodes[way.next].prevedge->direction = true;
            nodes[way.next].min = min(way.weight, nodes[top.index].min);
            q.push(fhi(nodes[way.next].min, way.next));
            nodes[way.next].flag = true;
            if (nodes[way.next].name == end)
            {
                max += nodes[way.next].min;
                node* shuttle = &nodes[way.next];
                while (shuttle->name != begin)
                {
                    if (shuttle->prevedge->direction)
                    {
                        shuttle->prevedge->weight -= shuttle->min;
                        shuttle->prevedge->result += shuttle->min;
                    }
                    else
                    {
                        shuttle->prevedge->weight += shuttle->min;
                        shuttle->prevedge->result -= shuttle->min;
                    }
                    nodes[shuttle->prev].min = shuttle->min;
                    shuttle = &nodes[shuttle->prev];
                }
                for (auto& n : nodes)
                    n.flag = false;
                clear(q);
                nodes[find(begin, nodes)].min = INT_MAX;
                nodes[find(begin, nodes)].flag = true;
                q.push(fhi(INT_MAX, find(begin, nodes)));
                break;
            }
        }
}

/*void backward(vector <node>& nodes, priority_queue <fhi>& q, fhi& top)
{
    if (nodes[top.index].prev != -1 && !nodes[nodes[top.index].prev].flag)
    {
        nodes[nodes[top.index].prev].prev = top.index;
        nodes[nodes[top.index].prev].prevedge = &nodes[nodes[top.index].prev].ways[findedge(nodes[top.index].name, nodes[nodes[top.index].prev].ways)];
        nodes[nodes[top.index].prev].prevedge->direction = false;
        nodes[nodes[top.index].prev].min = min(nodes[nodes[top.index].prev].prevedge->result, nodes[top.index].min);
        q.push(fhi(nodes[nodes[top.index].prev].min, nodes[top.index].prev));
        nodes[nodes[top.index].prev].flag = true;
    }
}*/

void fixresult(priority_queue <reslist, vector<reslist>, greater<reslist> >& answer, vector <node>& nodes)
{
    for (auto &n : nodes)
    {
        for (auto &e : n.ways)
        {
            answer.push(reslist(n.name, e.name, e.result));
        }
    }
}

int main() //ввод
{
    ifstream fin("input.txt");
    char begin, end;
    int n;
    int max = 0;
    fin >> n >> begin >> end;
    //cin >> n >> begin >> end;
    char dest, source;
    float weight;
    vector<node> nodes;
    int index = 0;
    while( fin >> source >> dest >> weight )
    {
    //    while( cin >> source >> dest >> weight )
      //  {
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


    priority_queue <fhi> q;
    nodes[find(begin, nodes)].min = INT_MAX;
    nodes[find(begin, nodes)].flag = true;
    q.push(fhi(INT_MAX, find(begin, nodes)));
    while (!q.empty())
    {
        fhi top = q.top();
        q.pop();
        forward(nodes, q, top, max, begin, end);
        /*if (q.top().index != 0)
            backward(nodes, q, top);*/
    }

    priority_queue <reslist, std::vector<reslist>, std::greater<reslist>> answer;
    fixresult(answer, nodes);
    cout << max << endl;
    while(!answer.empty())
    {
        cout << answer.top().first << ' ' << answer.top().second << ' ' << answer.top().weight << endl;
        answer.pop();
    }
    return 0;
}

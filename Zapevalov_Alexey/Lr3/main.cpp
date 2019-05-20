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

typedef struct queueElem //элемент очереди по убыванию
{
    queueElem(int f, int i) : function(f), index(i){}
    int function, index;
}fhi;

typedef struct resultList //список ребер в результате
{
    resultList(char a, char b, int w) : first(a), second(b), weight(w){}
    char first, second;
    int weight;
} reslist;

int operator < (fhi pair1, fhi pair2) //сравнение потоков
{
    return pair1.function < pair2.function;
}

int operator > (reslist a, reslist b) //сравнение символов в узлах
{
    if (a.first == b.first)
        return a.second > b.second;
    return a.first > b.first;
}

void clear( std::priority_queue <fhi> &q ) //очистка очереди
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

int findedge (char name, vector<edge> ways) //находим ребро по имени
{
    for (edge& n: ways)
        if (name == n.name)
            return &n - &ways[0]; //индекс в массиве
    return -1;
}

void forward(vector <node>& nodes, priority_queue <fhi>& q, fhi& top, int& max, char begin, char end)
{
    for (auto& way : nodes[top.index].ways) //для каждого исходящего ребра
        if (!nodes[way.next].flag && way.weight > 0) //если поток еще не заполнен и узел не пройден
        {
            nodes[way.next].prev = top.index; //добавление узла в очередь
            nodes[way.next].prevedge = &way;
            nodes[way.next].prevedge->direction = true;
            nodes[way.next].min = min(way.weight, nodes[top.index].min);
            q.push(fhi(nodes[way.next].min, way.next)); //в очереди хранятся допустимые потоки на узлах и их индексы
            nodes[way.next].flag = true;
            if (nodes[way.next].name == end) //дошли до конца
            {
                max += nodes[way.next].min;
                node* shuttle = &nodes[way.next]; //возврат в начало и по пути добавление в результирующий поток ребер максимально допустимого потока
                while (shuttle->name != begin)
                {
                    if (shuttle->prevedge->direction)
                    {
                        shuttle->prevedge->weight -= shuttle->min; //добавляем в результирующий поток и отнимаем из оставшегося
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
                nodes[find(begin, nodes)].min = INT_MAX; //снова добавляем исток в начало очереди
                nodes[find(begin, nodes)].flag = true; //это происходит только при успешном нахождении потока,
                q.push(fhi(INT_MAX, find(begin, nodes))); //бесконечного зацикливания нет
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

void fixresult(priority_queue <reslist, vector<reslist>, greater<reslist> >& answer, vector <node>& nodes) //заполнение результирующей структуры
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
        index = find(source, nodes); //добавление ребра/узла и ребра
        if( index != -1 )
            nodes[index].ways.push_back(edge(dest, weight));
        else
        {
            nodes.push_back(node(source, edge(dest,weight)));
            index = &nodes.back() - &nodes[0];
        }
        if( find(dest, nodes) == -1 ) //добавление узла/индекса узла
        {
            nodes.push_back(node(dest));
            nodes[index].ways.back().next = nodes.size() - 1;
        }
        else
            nodes[index].ways.back().next = find(dest, nodes);
    }
    fin.close();


    priority_queue <fhi> q;
    nodes[find(begin, nodes)].min = INT_MAX; //поток в истоке бесконечен
    nodes[find(begin, nodes)].flag = true;
    q.push(fhi(INT_MAX, find(begin, nodes))); //добавление истока в очередь
    while (!q.empty())
    {
        fhi top = q.top();
        q.pop();
        forward(nodes, q, top, max, begin, end); //выбор следующего узла и вызов функции
        /*if (q.top().index != 0)
            backward(nodes, q, top);*/
    }

    priority_queue <reslist, std::vector<reslist>, std::greater<reslist>> answer; //вывод в алфавитном порядке
    fixresult(answer, nodes);
    cout << max << endl;
    while(!answer.empty())
    {
        cout << answer.top().first << ' ' << answer.top().second << ' ' << answer.top().weight << endl;
        answer.pop();
    }
    return 0;
}

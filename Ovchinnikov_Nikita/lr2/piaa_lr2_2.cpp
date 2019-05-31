#include <QCoreApplication>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <ctype.h>
#include <vector>
#include <math.h>

#define EPS 0.000001

using namespace std;

class Edge
{
public:
    double weight;
    char to;
};

class Vertices
{
public:
    char name;
    double costFromBegin = numeric_limits<double>::max();   //стоимость пути от начала до этой точки
    double heuristic = 0;   //значение эвристической функции
    vector<Edge> edges;
    Vertices *parent = nullptr;
};

class Graph
{
public:
    vector<Vertices> vertices;
    vector<char> resultPath;
    char from;
    char to;

    Graph(char from, char to)
    {
        this->from = from;
        this->to = to;
        char tmp = 'a';
        for(int i=0; i < 26; i++, tmp++)
        {
            Vertices tmpVertex;
            tmpVertex.name = tmp;
            vertices.push_back(tmpVertex);
        }

        double weight;
        char one, two = '\0';
        int index;
        while(1)
        {
            if(cin >> one && cin >> two && cin >> weight){
                Edge tmpEdge;
                tmpEdge.to = two;
                tmpEdge.weight = weight;
                index = static_cast<int>(one) - static_cast<int>('a');
                Vertices *tmpVertex = &(vertices.at(index));
                tmpVertex->edges.push_back(tmpEdge);
            }
            else
                break;
        }
    }

    double h(char from) //эвристическая функция
    {
        return abs(static_cast<int>(this->to) - static_cast<int>(from));
    }

    int min_Q(vector<Vertices> Q)
    {
        if(Q.size() == 1)
            return 0;
        unsigned int i = 1;
        int min = 0;
        Vertices tmp1;
        Vertices tmp2;
        while(i < Q.size())
        {
            tmp1 = Q.at(i-1);
            tmp2 = Q.at(i);
            if(tmp1.heuristic < tmp2.heuristic || fabs(tmp1.heuristic - tmp2.heuristic)<EPS)
                min = i-1;
            else
                min = i;
            i++;
        }
        return min;
    }

    bool belongToVector(vector<Vertices> &A, Vertices &a) const
    {
        Vertices tmp;
        for(unsigned int i=0; i<A.size(); i++)
        {
            tmp = A.at(i);
            if(tmp.name == a.name && tmp.costFromBegin == a.costFromBegin && tmp.heuristic == a.heuristic)
                return true;
        }
        return false;
    }

    bool aStar(char from, char to)
    {
        Edge tmpEdge;
        Vertices *tmpVertex;
        vector<Vertices> Q; //мн-во вершин,которые требуется рассмотреть
        vector<Vertices> U; //мн-во рассмотренных вершин
        vector<Vertices>::iterator itQ;
        int tentativeScore = 0;
        int index = static_cast<int>(from) - static_cast<int>('a');
        tmpVertex = &(vertices.at(index));
        tmpVertex->costFromBegin = 0;
        tmpVertex->heuristic = tmpVertex->costFromBegin + h(from);
        Q.push_back(vertices.at(index));
        while(Q.size() != 0)
        {
            int min = min_Q(Q);
            Vertices current = Q.at(min);//*(itQ + min);
            if(current.name == to)
            {
                return true;
            }
            U.push_back(current);
            itQ = Q.begin();
            itQ = itQ + min;
            Q.erase(itQ);
            for(unsigned int i=0; i<current.edges.size(); i++)
            {
                tmpEdge = current.edges[i];
                tentativeScore = current.costFromBegin + tmpEdge.weight;
                index = static_cast<int>(tmpEdge.to) - static_cast<int>('a');
                tmpVertex = &(vertices[index]);
                if(belongToVector(U, *tmpVertex) && tentativeScore >= tmpVertex->costFromBegin)
                    continue;
                if(!belongToVector(U, *tmpVertex) || tentativeScore < tmpVertex->costFromBegin)
                {
                    tmpVertex->costFromBegin = tentativeScore;
                    tmpVertex->heuristic = tmpVertex->costFromBegin + h(tmpVertex->name);
                    tmpVertex->parent = &vertices.at(static_cast<int>(current.name) - static_cast<int>('a'));
                    if(!belongToVector(Q, *tmpVertex))
                        Q.push_back(*tmpVertex);
                }
            }
        }
        return false;
    }

    void print()
    {
        Vertices *tmpVertex = &(vertices.at(static_cast<int>(this->to) - static_cast<int>('a')));
        vector<char>::iterator it = resultPath.begin();
        do
        {
            it = resultPath.begin();
            resultPath.insert(it, tmpVertex->name);
            tmpVertex = tmpVertex->parent;
        }
        while(tmpVertex != nullptr);
        for(it = resultPath.begin(); it != resultPath.end(); it++)
            cout << *it;
        cout << endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char from, to;
    scanf("%c %c", &from, &to);
    Graph go(from, to);
    go.aStar(go.from, go.to);
    go.print();

    return a.exec();
}

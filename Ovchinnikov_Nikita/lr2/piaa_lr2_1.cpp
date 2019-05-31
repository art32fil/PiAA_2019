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

class Edge;
bool comp(Edge &a, Edge &b);

class Path
{
public:
    char from;
    char to;
    char *path;
};

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
    int visitedEdgesCounter = 0;
    vector<Edge> edges;
};

class Graph
{
public:
    vector<Vertices> vertices;
    int size;
    Path path;

    Graph(char from, char to)
    {
        path.from = from;
        path.to = to;
        size = 26;
        path.path = new char[size*2];
        char tmp = 'a';
        for(int i=0; i < size; i++, tmp++)
        {
            Vertices tmpVertex;
            tmpVertex.name = tmp;
            vertices.push_back(tmpVertex);
            path.path[0] = '\0';
        }
    }

    ~Graph()
    {
        delete path.path;
        path.path = NULL;
    }

    void greed()
    {
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

        for(int i=0; i<size; i++)
        {
            Vertices *tmpVertex = &(vertices.at(i));
            tmpVertex->edges.shrink_to_fit();
            if(tmpVertex->edges.empty() == false)
                sort(tmpVertex->edges.begin(), tmpVertex->edges.end(), comp);
        }

        int k=0;
        one = path.from;
        for(; one != path.to; k++)
        {
            path.path[k] = one;
            index = static_cast<int>(one) - static_cast<int>('a');
            Vertices *tmpVertex = &(vertices.at(index));
            if(tmpVertex->edges.empty())
            {
                //cout << "Vector reber u vershini  " << index << " pust\n";
                path.path[k--] = '\0';
                index = static_cast<int>(path.path[k]) - static_cast<int>('a');
                tmpVertex = &(vertices.at(index));
            }
            Edge tmpEdge = tmpVertex->edges.at(tmpVertex->visitedEdgesCounter++);
            one = tmpEdge.to;
        }

        for(; k<size*2; k++)
            path.path[k] = '\0';
        cout << path.path << path.to << endl;
     }
};

bool comp(Edge &a, Edge &b)
{
    if(fabs(a.weight - b.weight) < EPS)
    {
        return a.to < b.to;
    }
    return a.weight < b.weight;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char from, to;
    scanf("%c %c", &from, &to);
    Graph go(from, to);
    go.greed();

    return a.exec();
}

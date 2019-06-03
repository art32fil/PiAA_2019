#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <stdio.h>
#include <cstdlib>

#define SIZE 128
#define DIGIT 0

using namespace std;

int comp(const void *aa, const void *bb);

class Pair
{
public:
    unsigned char from;
    unsigned char to;
};

class Edge
{
public:
    int capacity = 0;
    int stream = 0;
};

class FordFulkerson
{
private:
    Edge **graph;
    unsigned char source;
    unsigned char stock;
    unsigned int edgeCount;
    vector<unsigned char> tmpForWays;
    vector<unsigned char> blocked;
    int maxStream = 0;
    int minStreamInWay;
    Pair *result;

public:
    FordFulkerson()
    {
        graph = new Edge* [SIZE];
        for(size_t i=0; i<SIZE; i++)
            graph[i] = new Edge [SIZE];

        cin >> edgeCount >> source >> stock;

        result = new Pair[edgeCount];

        Pair tmp;
        for(size_t i=0; i<edgeCount; i++)
        {
            cin >> tmp.from >> tmp.to;
            cin >> graph[tmp.from-DIGIT][tmp.to-DIGIT].capacity;
            result[i] = tmp;
        }

        qsort(result, edgeCount, sizeof(Pair), comp);
    }

    ~FordFulkerson()
    {
        delete result;

        for(size_t i = 0; i<SIZE; i++)
            delete graph[i];
        delete graph;
    }

    bool inVector(unsigned char &v, vector<unsigned char> &vec)
    {
        for(vector<unsigned char>::iterator it = vec.begin(); it != vec.end(); it++)
        {
            if(*it == v)
                return true;
        }
        return false;
    }

    bool searchOneWay(unsigned char v)
    {
        if(v == stock)
        {
            tmpForWays.push_back(v);
            return true;
        }

        unsigned char next = 0;
        for(unsigned char i=DIGIT; i<SIZE+DIGIT; i++)
        {
            if(((graph[v-DIGIT][i-DIGIT].capacity != 0 && graph[v-DIGIT][i-DIGIT].capacity > graph[v-DIGIT][i-DIGIT].stream)
                || (graph[i-DIGIT][v-DIGIT].capacity != 0 && graph[i-DIGIT][v-DIGIT].stream > 0 && graph[i-DIGIT][v-DIGIT].capacity > graph[i-DIGIT][v-DIGIT].stream))
                    && !inVector(i, blocked) && !inVector(i, tmpForWays))
            {
                next = i;
                break;
            }
        }

        if(next == 0)
        {
            if(v == source)
                return false;
            blocked.push_back(v);
            return searchOneWay(tmpForWays.back());
        }

        if(!inVector(v, tmpForWays))
            tmpForWays.push_back(v);

        return searchOneWay(next);
    }

    void changeStream()
    {
        minStreamInWay = INT_MAX;
        for(vector<unsigned char>::iterator it = tmpForWays.begin()+1; it != tmpForWays.end(); it++)
        {
            if(graph[*(it-1) - DIGIT][*it - DIGIT].capacity != 0)
                minStreamInWay = min(minStreamInWay, graph[*(it-1) - DIGIT][*it - DIGIT].capacity - graph[*(it-1) - DIGIT][*it - DIGIT].stream);
            else
                minStreamInWay = min(minStreamInWay, min(graph[*it - DIGIT][*(it-1) - DIGIT].capacity - graph[*it - DIGIT][*(it-1) - DIGIT].stream, graph[*it - DIGIT][*(it-1) - DIGIT].stream));
        }
        for(vector<unsigned char>::iterator it = tmpForWays.begin()+1; it != tmpForWays.end(); it++)
        {
            graph[*(it-1) - DIGIT][*it - DIGIT].stream += minStreamInWay;
            graph[*it - DIGIT][*(it-1) - DIGIT].stream -= minStreamInWay;
        }
        maxStream += minStreamInWay;
    }

    void setStreams()
    {
        if(source == stock)
        {
            printResults();
            return;
        }
        while(searchOneWay(source))
        {
            changeStream();
            tmpForWays.clear();
            blocked.clear();
        }
        printResults();
    }

    void printResults()
    {
        cout << maxStream << endl;
        for(size_t i=0; i<edgeCount; i++)
        {
            printf("%c %c %d\n", result[i].from, result[i].to, graph[result[i].from-DIGIT][result[i].to-DIGIT].stream);
        }
    }
};

int comp(const void *aa, const void *bb)
{
    Pair a = *(Pair*)aa;
    Pair b = *(Pair*)bb;
    if(a.from == b.from)
    {
        return a.to - b.to;
    }
    return a.from - b.from;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FordFulkerson G;
    G.setStreams();

    return a.exec();
}

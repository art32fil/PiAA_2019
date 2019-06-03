#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge
{
    char beg;
    char end;
    double heft;
};

bool compare(edge first, edge second)
{
    return first.heft < second.heft;
}

class Graph
{
private:
    vector <edge> graph;
    vector <char> result;
    vector <char> viewingpoint;
    char source;
    char estuary;

public:
    Graph()
    {
         cin >> source >> estuary;
         char temp;
         while(cin >> temp)
         {
             edge element;
             element.beg = temp;
             if(!(cin >> element.end))
                 break;
             if(!(cin >> element.heft))
                 break;
             graph.push_back(element);
         }
         sort(graph.begin(), graph.end(), compare);
    }

    bool isViewing(char value)
    {
        for(size_t i = 0; i < viewingpoint.size(); i++)
            if(viewingpoint.at(i) == value)
                return true;
        return false;
    }

    void initSearch()
    {
        if(source != estuary)
            Search(source);
    }

    bool Search(char value)
    {
        if(value == estuary)
        {
            result.push_back(value);
            return true;
        }
        viewingpoint.push_back(value);
        for(size_t i(0); i < graph.size(); i++)
        {
            if(value == graph.at(i).beg)
            {
                if(isViewing(graph.at(i).end))
                    continue;
                result.push_back(graph.at(i).beg);
                bool flag = Search(graph.at(i).end);
                if(flag)
                   return true;
                result.pop_back();
            }
        }
        return false;
    }

    void Print()
    {
        for(size_t i(0); i < result.size(); i++)
            cout << result.at(i);
    }
};

int main()
{
    Graph element;
    element.initSearch();
    element.Print();
    return 0;
}

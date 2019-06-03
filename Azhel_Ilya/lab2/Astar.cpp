#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct edge     //ребро графа
{
    char beg;
    char end;
    double heft;
};

struct step     //возможные пути
{
    string path;
    double length;
};

class Graph
{
private:
    vector <edge> graph;
    vector <step> result;
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
             cin >> element.end;
             cin >> element.heft;
             graph.push_back(element);
         }
         string buf = "";
         buf += source;
         for(size_t i(0); i < graph.size(); i++)
         {
             if(graph.at(i).beg == source)
             {
                 buf += graph.at(i).end;
                 result.push_back({buf, graph.at(i).heft});
                 buf.resize(1);
             }
         }
         viewingpoint.push_back(source);
    }

    size_t MinSearch() //возвращает индекс минимального элемента из непросмотренных
    {
        double min = 9999;
        size_t temp;
        for(size_t i(0); i < result.size(); i++)
        {
            if(result.at(i).length + abs(estuary - result.at(i).path.back()) < min)
            {
                if(isViewing(result.at(i).path.back()))
                {
                    result.erase(result.begin() + i);
                }
                else
                {
                    min = result.at(i).length + abs(estuary - result.at(i).path.back());
                    temp = i;
                }
            }
        }
        return temp;
    }

    bool isViewing(char value)
    {
        for(size_t i = 0; i < viewingpoint.size(); i++)
            if(viewingpoint.at(i) == value)
                return true;
        return false;
    }

    void Search()
    {
        while(true)
        {
            size_t min = MinSearch();
            if(result.at(min).path.back() == estuary)
            {
                cout << result.at(min).path;
                return;
            }
            for(size_t i(0); i < graph.size(); i++)
            {
                if(graph.at(i).beg == result.at(min).path.back())
                {
                    string buf = result.at(min).path;
                    buf += graph.at(i).end;
                    result.push_back({buf, graph.at(i).heft + result.at(min).length});
                }
            }
            viewingpoint.push_back(result.at(min).path.back());
            result.erase(result.begin() + min);
        }
    }
};

int main()
{
    Graph element;
    element.Search();
    return 0;
}

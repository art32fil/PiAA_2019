#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge
{
    char beg;
    char end;
    int heft;
    int forward;
    int back;
    bool doubl;
};

bool compare(edge first, edge second)
{
    if(first.beg == second.beg)
        return first.end < second.end;
    return first.beg < second.beg;
}

class Graph
{
private:
    vector <edge> graph;
    char source;
    char estuary;
    int N;
    vector <char> viewingpoint;
    vector <char> result;

public:
    Graph()
    {
        cin >> N;
        cin >> source >> estuary;
        for(int i = 0; i < N; i++)
        {
            edge element;
            cin >> element.beg >> element.end >> element.heft;
            element.forward = element.heft;
            element.back = 0;
            element.doubl = false;
            bool flag = true;
            for(int i = 0; i < graph.size(); i++)
            {
                if(graph.at(i).beg == element.end && graph.at(i).end == element.beg)
                {
                    graph.at(i).back += element.forward;
                    flag = false;
                    graph.at(i).doubl = true;
                    break;
                }
            }
            if(!flag)
                continue;
            graph.push_back(element);
        }
    }

    bool isViewing(char value)
    {
        for(size_t i = 0; i < viewingpoint.size(); i++)
            if(viewingpoint.at(i) == value)
                return true;
        return false;
    }

    bool Search(char value, int& min)
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
                if(isViewing(graph.at(i).end) || graph.at(i).forward == 0)
                    continue;
                result.push_back(graph.at(i).beg);
                bool flag = Search(graph.at(i).end, min);
                if(flag)
                {
                   if(graph.at(i).forward < min)
                       min = graph.at(i).forward;
                   return true;
                }
                result.pop_back();
            }
            if(value == graph.at(i).end)
            {
                if(isViewing(graph.at(i).beg) || graph.at(i).back == 0)
                    continue;
                result.push_back(graph.at(i).end);
                bool flag = Search(graph.at(i).beg, min);
                if(flag)
                {
                   if(graph.at(i).back < min)
                        min = graph.at(i).back;
                   return true;
                }
                result.pop_back();
            }
        }
        return false;
    }


    void FordFalk()
    {
        int res = 0;
        int min = 9999;

        while(Search(source, min))
        {
            for(int i = 1; i < result.size(); i++)
            {
                for(int j = 0; j < graph.size(); j++)
                {
                    if(graph.at(j).beg == result.at(i-1) && graph.at(j).end == result.at(i))
                    {
                        graph.at(j).forward -= min;
                        graph.at(j).back += min;
                    }
                    if(graph.at(j).end == result.at(i-1) && graph.at(j).beg == result.at(i))
                    {
                        graph.at(j).forward += min;
                        graph.at(j).back -= min;
                    }
                }
            }
            res += min;
            viewingpoint.clear();
            result.clear();
            min = 9999;
        }

        sort(graph.begin(), graph.end(), compare);
        cout << res << endl;
        for(int i = 0; i < graph.size(); i++)
        {
            int value = max(graph.at(i).heft - graph.at(i).forward, 0 - graph.at(i).back);
            if(graph.at(i).doubl == true)
            {
                if(value < 0)
                    value = 0;
                cout << graph.at(i).beg << " " << graph.at(i).end << " " << value << endl;
                swap(graph.at(i).beg, graph.at(i).end);
                swap(graph.at(i).back, graph.at(i).forward);
                graph.at(i).doubl = false;
                sort(graph.begin(), graph.end(), compare);
                i--;
            }
            else
            {
                cout << graph.at(i).beg << " " << graph.at(i).end << " " << value << endl;
            }
        }
    }
};

int main()
{
    Graph element;
    element.FordFalk();
    return 0;
}

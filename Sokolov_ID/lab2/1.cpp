#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Edge
{
    char startOfEdge;
    char endOfEdge;
    double length;

public:

    char getEndOfEdge()
    {
        return endOfEdge;
    }

    double getlength()
    {
        return length;
    }

    Edge(char startOfEdge, char endOfEdge, double length) : startOfEdge(startOfEdge), endOfEdge(endOfEdge), length(length) {}

};

bool isTopInList(vector<char> tops, char startOfEdge)
{
    for (int i = 0; i < tops.size(); i++)
    {
        if (tops[i] == startOfEdge) return true;
    }
    return false;
}

int getIndex(vector<char> tops, char startOfEdge)
{
    for (int i = 0; i < tops.size(); i++)
    {
        if (tops[i] == startOfEdge)
            return i;
    }

}

void printStack(stack <char> stack)
{
    char m = stack.top();
    stack.pop();
    if (!stack.empty())
    {
        printStack(stack);
    }
    cout << m;
}

bool way = false;

void findWay(vector<char> tops, vector<vector<Edge> > edges, int startIndex, char end, stack <char> stack)
{
    if (!edges[startIndex].empty())
    {
        char endLocal = edges[startIndex][0].getEndOfEdge();
        stack.push(endLocal);
        if (endLocal != end)
        {
            edges[startIndex].erase(edges[startIndex].begin());
            findWay(tops, edges, getIndex(tops, endLocal), end, stack);
            stack.pop();
            if (way == false)
            {
                findWay(tops, edges, startIndex, end, stack);
            }
        }
        else
        {
            printStack(stack);
            cout << endl;
            way = true;
        }
    }
}

int main()
{

    char start;
    char end;

    cin >> start;
    cin >> end;

    char startOfEdge;
    char endOfEdge;
    double length;

    vector<char> tops;
    vector<vector<Edge> > edges;

    while (cin >> startOfEdge && cin >> endOfEdge && cin >> length)
    {
        if(startOfEdge=='.')break;//delete kogda zakonch
        if (!isTopInList(tops, startOfEdge))
        {
            tops.push_back(startOfEdge);
            vector<Edge> a;
            edges.push_back(a);

        }

        if (!isTopInList(tops, endOfEdge))
        {
            tops.push_back(endOfEdge);
            vector<Edge> a;
            edges.push_back(a);
        }

        edges[getIndex(tops, startOfEdge)].push_back(Edge(startOfEdge, endOfEdge, length));
    }

    stack <char> stack;
    stack.push(start);

    if (edges.size() > 1)
        for (int i = 0; i < edges.size(); i++)
            if (edges[i].size() > 1)
                for (int j = 1; j < edges[i].size(); j++)
                    if (edges[i][j].getlength() < edges[i][j - 1].getlength())
                        swap(edges[i][j],edges[i][j-1]);

    findWay(tops, edges, getIndex(tops, start), end, stack);
    return 0;
}

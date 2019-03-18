#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <climits>

using namespace std;
using Vertex = char;


//find path from source to end
map<Vertex, pair<Vertex, int>> Dfs(map<Vertex, map<Vertex, int>> graph, Vertex source, Vertex end)
{
    map<Vertex, pair<Vertex, int>> path;
    map<Vertex, bool> visited_vertex;
    vector<Vertex> stack;

    for(map<Vertex, map<Vertex, int>>::iterator it = graph.begin(); it!= graph.end(); ++it)
        visited_vertex[it->first] = false;

    map<Vertex, map<Vertex, int>>::iterator cur = graph.find(source);
    visited_vertex[source] = true;
    stack.push_back(source);

    while(cur->first!= end && stack.size()!= 0)
    {
        bool append_new = false;
        for (map<Vertex, int>::iterator it = cur->second.begin(); it!= cur->second.end(); ++it)
            if(!visited_vertex[it->first] && it->second!= 0)
            {
                path[cur->first] = pair<Vertex, int>(it->first, it->second);
                cur = graph.find(it->first);
                visited_vertex[cur->first] = true;
                stack.push_back(cur->first);
                append_new = true;
                break;
            }

        //deadlock
        if(!append_new)
        {
            append_new = false;
            path.erase(stack.back());
            stack.pop_back();
            cur = graph.find(stack.back());
        }
    }

    return path;
}


int min_capacity(map<Vertex, pair<Vertex, int>> path)
{
    int min = INT_MAX;

    for(map<Vertex, pair<Vertex, int>>::iterator it = path.begin(); it!= path.end(); ++it)
        if(it->second.second < min && it->second.second > 0)
            min = it->second.second;
    return min;
}


void MaxFlow(map<Vertex, map<Vertex, int>> &network, int &max_flow, Vertex source, Vertex end)
{
    map<Vertex, pair<Vertex, int>> path = Dfs(network, source, end);

    for(/* do nothing */; path.size()!= 0; /* do nothing */)
    {
        int min = min_capacity(path);
        max_flow += min;
        for(map<Vertex, pair<Vertex, int>>::iterator it = path.begin(); it!= path.end(); ++it)
        {
            network[it->first][it->second.first] -= min;
            network[it->second.first][it->first] += min;
        }
        path = Dfs(network, source, end);
    }
}


int main()
{
    map<Vertex, map<Vertex, int>> graph;
    map<Vertex, map<Vertex, int>> straight_line_graph;
    Vertex source, destination;
    int count_edges;

    cin >> count_edges >> source >> destination;

    Vertex u, v;
    int c;

    for (int i = 0; i < count_edges; ++i)
    {
        cin >> u >> v >> c;
        graph[u][v] = c; //straight line edge
        straight_line_graph[u][v] = c;
        graph[v][v] = 0;
        //create reverse edge
        if(graph[v].find(u) == graph[v].end())
            graph[v][u] = 0;
    }

    map<Vertex, map<Vertex, int>> network = graph;
    int max_flow = 0;

    MaxFlow(network, max_flow, source, destination);
    cout << endl;

    cout << max_flow << endl;
    for(map<Vertex, map<Vertex, int>>::iterator it = straight_line_graph.begin(); it!= straight_line_graph.end();++it)
        for(map<Vertex, int>::iterator it2 = it->second.begin(); it2!= it->second.end(); ++it2)
            if(it2->second - network[it->first][it2->first] >= 0)
                cout << it->first << " " << it2->first << " " << it2->second - network[it->first][it2->first] << endl;
            else
                cout << it->first << " " << it2->first << " " << 0 << endl;

    return 0;
}

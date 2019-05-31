#include <iostream>
#include <map>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

bool bfs(map<char,map<char,int>>rgraph, char start, char end, map<char,char>& path){
    map<char,bool>visited;
    queue<char>q;
    q.push(start);
    visited[start] = true;
    while (!q.empty())
    {
        char u = q.front();
        q.pop();
        for (auto const &sub : rgraph[u]){
            if (sub.second > 0 && visited[sub.first] == false) {
                            q.push(sub.first);
                            visited[sub.first] = true;
                            path[sub.first] = u;
            }
        }
    }
    return (visited[end] == true);
}



int FordFulkerson(map<char,map<char,int>>&graph, map<char,map<char,int>>&rgraph, char start, char finish){
    char u,v;
    map<char,char>path;
    for (auto const &main: graph)
        for (auto const &sub: graph[main.first])
            rgraph[main.first][sub.first] = sub.second;
    int max_flow = 0;
    while (bfs(rgraph,start,finish,path))
    {
        int path_flow = numeric_limits<int>::max();
        for (v = finish; v != start; v = path[v])
        {
            u = path[v];
            path_flow = min(path_flow, rgraph[u][v]);
        }
        for (v = finish; v != start; v = path[v])
        {
            u = path[v];
            rgraph[u][v] -= path_flow;
            rgraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int get_flow(map<char,map<char,int>>graph,char from, char to, int current) {
        if (current - graph[from][to] < 0) return 0;
        else return current - graph[from][to];
}

int main()
{
    int n,cost;
    char begin,end,start,finish;
    map <char,map<char,int>>graph,rgraph;
    cin >> n >> start >> finish;
    cost = numeric_limits<int>::max();
    for (int i=0;i<n;i++){
        cin >> begin >> end >> cost;
        graph[begin][end] = cost;
    }
    int res = FordFulkerson(graph,rgraph,start,finish);
    cout << res << endl;
    for (auto const &main: graph)
        for (auto const &tmp: graph[main.first])
             cout << main.first << " " << tmp.first << " " << get_flow(rgraph,main.first, tmp.first, tmp.second)<< endl;
    return 0;
}
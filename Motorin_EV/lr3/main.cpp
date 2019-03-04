#include <iostream>
#include <queue>
#include <map>
#include <climits>

#define GRAPH map<char, map<char, int>>
using namespace std;

struct WAY {char from; char to; int capacity;};

class FF {
public:
    FF(GRAPH g, int mf): rGraph(g), maxFlow(mf){}
    
    friend ostream &operator << (ostream &out, FF &f) {
        out << f.maxFlow << endl;
        for (auto const &main: f.defaultGraph)
            for (auto const &sub: f.defaultGraph.at(main.first))
                cout << main.first << " " << sub.first << " " << f.FF::getFlowForWay(main.first, sub.first, sub.second)<< endl;
        return out;
    }
    
    void setDefaultGraph(GRAPH df) {defaultGraph = df;}
    
private:
    GRAPH rGraph;
    int maxFlow;
    GRAPH defaultGraph;
    
    int getFlowForWay(char from, char to, int current) {
        if (current - rGraph[from][to] < 0) return 0;
        else return current - rGraph[from][to];
    }
};

bool bfs(GRAPH rGraph, WAY task, map<char, char>& path) {
    map<char, bool> visited;
    queue <char> q;
    q.push(task.from);
    visited[task.from] = true;
    
    while (!q.empty()) {
        char u = q.front();
        q.pop();
        
        for (auto const &sub: rGraph[u])
            if (sub.second > 0 && visited[sub.first] == false) {
                q.push(sub.first);
                visited[sub.first] = true;
                path[sub.first] = u;
            }
    }
    
    return (visited[task.to] == true);
}

FF fordFulkerson(GRAPH& graph, WAY task) {
    char u, v;
    GRAPH rGraph;
    map<char, char> path;
    
    for (auto const &main: graph)
        for (auto const &sub: graph[main.first])
            rGraph[main.first][sub.first] = sub.second;
    
    int maxFlow = 0;
    while (bfs(rGraph, task, path)) {
        int pathFlow = INT_MAX;
        
        for (v = task.to; v != task.from; v = path[v]) {
            u = path[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }
        
        for (v = task.to; v != task.from; v = path[v]) {
            u = path[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
        
        maxFlow += pathFlow;
    }
    return FF(rGraph, maxFlow);
}
int main() {
    GRAPH graph;
    WAY task, ptr;
    int count;
    
    cin >> count >> task.from >> task.to;
    for (int i = 0; i < count; i++) {
        cin >> ptr.from >> ptr.to >> ptr.capacity;
        graph[ptr.from][ptr.to] = ptr.capacity;
    }
    
    FF res =  fordFulkerson(graph, task);
    res.setDefaultGraph(graph);
    cout << res;
    return 0;
}

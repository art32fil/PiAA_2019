#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <climits>

using namespace std;

using Vertex = char;
using Graph = map<Vertex, map<Vertex, long long int>>;
using Path = map<Vertex, Vertex>;

bool findWay_BFS(Graph &graph, Vertex source, Vertex stock, Path &stock_path)
{
    vector<Vertex> visited_vertexes = {source};
    queue<Vertex> bfs_queue;
    Path come_from;
    Vertex current_vertex;

    bfs_queue.push(source);
    while(!bfs_queue.empty())
    {
        current_vertex = bfs_queue.front();
        bfs_queue.pop();

        for (auto const &neighbor : graph[current_vertex])
        {
            if (neighbor.second > 0 &&
                    find(visited_vertexes.begin(), visited_vertexes.end(), neighbor.first) == visited_vertexes.end())
            {
                visited_vertexes.push_back(neighbor.first);
                bfs_queue.push(neighbor.first);
                come_from[neighbor.first] = current_vertex;
            }
        }
    }
    stock_path = come_from;
    return find(visited_vertexes.begin(), visited_vertexes.end(), stock) != visited_vertexes.end();
}

long long int findMaxFlow_EdmondsKarp(Graph &graph, Vertex source, Vertex stock)
{
    Path stock_path;
    long long int max_flow = 0;
    Vertex from, where;

    while (findWay_BFS(graph, source, stock, stock_path))
    {
        long long int max_way_flow = LLONG_MAX;
        where = stock;
        while (where != source)
        {
            max_way_flow = min(max_way_flow, graph[stock_path[where]][where]);
            where = stock_path[where];
        }

        max_flow += max_way_flow;
        where = stock;
        while (where != source)
        {
            from = stock_path[where];
            graph[from][where] -= max_way_flow;
            graph[where][from] += max_way_flow;
            where = stock_path[where];
        }
    }
    return max_flow;
}

int main()
{
    Graph graph, residual_graph;
    Vertex source, stock, from, where;
    long long int edge_number, bandwidth, max_flow;

    cin >> edge_number >> source >> stock;
    while ((edge_number--) && (cin >> from >> where >> bandwidth))
        graph[from][where] = bandwidth;

    residual_graph = graph;
    max_flow = findMaxFlow_EdmondsKarp(residual_graph, source, stock);

    cout << max_flow << endl;
    for (auto const &current : graph)
        for (auto const &neighbor : graph[current.first])
            cout << current.first << " " << neighbor.first << " "
                 << (int(neighbor.second - residual_graph[current.first][neighbor.first]) < 0 ? 0 :
                     int(neighbor.second - residual_graph[current.first][neighbor.first])) << endl;
    return 0;
}

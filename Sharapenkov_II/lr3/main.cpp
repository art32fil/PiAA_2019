#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <deque>
#include <climits>


using Vertex = char;
using Graph = std::map<Vertex, std::map<Vertex, long long int>>;


bool BFS(Graph &graph, Vertex start, Vertex end, std::map<Vertex, Vertex> &path) {
    std::vector<Vertex> closed_set = {start};
    std::deque<Vertex> open_set = {start};
    std::map<Vertex, Vertex> came_from;
    Vertex current;

    while (!open_set.empty()) {
        current = open_set.front();
        open_set.pop_front();

        for (auto const &neighbor: graph[current])
            if (neighbor.second > 0 &&
                !(std::find(closed_set.begin(), closed_set.end(), neighbor.first) != closed_set.end())) {
                open_set.push_back(neighbor.first);
                closed_set.push_back(neighbor.first);
                came_from[neighbor.first] = current;
            }

    }

    path = came_from;
    return std::find(closed_set.begin(), closed_set.end(), end) != closed_set.end();
}


long long int FFA(Graph &graph, Vertex start, Vertex end) {
    std::map<Vertex, Vertex> path;
    long long int max_flow = 0, path_flow;
    Vertex s, v, u;

    while (BFS(graph, start, end, path)) {
        path_flow = LLONG_MAX;

        s = end;
        while (s != start) {
            path_flow = std::min(path_flow, graph[path[s]][s]);
            s = path[s];
        }

        max_flow += path_flow;

        v = end;
        while (v != start) {
            u = path[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
            v = path[v];
        }
    }
    return max_flow;
}


int main() {
    Graph graph, residual_graph;
    Vertex start, end, v1, v2;
    long long int cost, N, max_val;

    std::cin >> N >> start >> end;

    while (N-- && std::cin >> v1 >> v2 >> cost)
        graph[v1][v2] = cost;

    residual_graph = graph;
    max_val = FFA(residual_graph, start, end);

    std::cout << max_val << std::endl;

    for (auto const &current: graph)
        for (auto const &neighbor: graph[current.first])
            std::cout << current.first << " " << neighbor.first << " "
                      << (int(neighbor.second - residual_graph[current.first][neighbor.first]) < 0 ? 0 :
                          int(neighbor.second - residual_graph[current.first][neighbor.first])) << std::endl;


    return 0;
}
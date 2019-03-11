#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cfloat>


using Vertex = char;
using Edge =  struct Edge {
    Vertex next;
    float cost;

    explicit Edge(Vertex n, float c) : next(n), cost(c) {};
};
using Graph = std::map<Vertex, std::vector<Edge>>;


float heuristic(Vertex v1, Vertex v2) {
    return abs(v1 - v2);
}


std::vector<Vertex> reconstruct(std::map<Vertex, Vertex> came_from, Vertex current) {
    std::vector<Vertex> total_path = { current };
    while(came_from.find(current) != came_from.end()) {
        current = came_from[current];
        total_path.insert(total_path.begin(), current);
    }
    return total_path;
}

using DefInfFloat = struct {
    float val = FLT_MAX;
};

std::vector<Vertex> greedy(Graph &graph, Vertex start, Vertex end) {
    std::vector<Vertex> closed_set, open_set = {start};
    std::map<Vertex, Vertex> came_from;
    std::map<Vertex, DefInfFloat> f_score;

    f_score[start].val = 0;
    while (!open_set.empty()) {
        Vertex current = *std::min_element(open_set.begin(), open_set.end(), [&f_score, current, &graph](Vertex const &a, Vertex const &b) {
            if(std::find_if(graph[current].begin(), graph[current].end(), [a](Edge const &e) {
                return e.next == a;
            }) != graph[current].end() && std::find_if(graph[current].begin(), graph[current].end(), [b](Edge const &e) {
                    return e.next == b;
            }) == graph[current].end()) {
                return true;
            }
            return f_score[a].val < f_score[b].val;
        });

        if(current == end)
            return reconstruct(came_from, current);

        open_set.erase(std::remove(open_set.begin(), open_set.end(), current), open_set.end());
        closed_set.push_back(current);

        for (auto const &neighbor: graph[current]) {
            if(std::find(closed_set.begin(), closed_set.end(), neighbor.next) != closed_set.end())
                continue;

            if(!(std::find(open_set.begin(), open_set.end(), neighbor.next) != open_set.end()))
                open_set.push_back(neighbor.next);
            else if(neighbor.cost >= f_score[neighbor.next].val)
                continue;

            came_from[neighbor.next] = current;
            f_score[neighbor.next].val = neighbor.cost;

        }
    }
}


std::vector<Vertex> astar(Graph &graph, Vertex start, Vertex end) {
    std::vector<Vertex> closed_set, open_set = {start};
    std::map<Vertex, Vertex> came_from;
    std::map<Vertex, DefInfFloat> g_score, f_score;

    g_score[start].val = 0;
    f_score[start].val = heuristic(start, end);
    while (!open_set.empty()) {
        Vertex current = *std::min_element(open_set.begin(), open_set.end(), [&f_score, end](Vertex const &a, Vertex const &b) {
            if(f_score[a].val == f_score[b].val) return  heuristic(a, end) < heuristic(b, end);
            return f_score[a].val < f_score[b].val;
        });

        if(current == end)
            return reconstruct(came_from, current);

        open_set.erase(std::remove(open_set.begin(), open_set.end(), current), open_set.end());
        closed_set.push_back(current);

        for (auto const &neighbor: graph[current]) {
            if(std::find(closed_set.begin(), closed_set.end(), neighbor.next) != closed_set.end())
                continue;

            float tentative_g_score = g_score[current].val + neighbor.cost;

            if(!(std::find(open_set.begin(), open_set.end(), neighbor.next) != open_set.end()))
                open_set.push_back(neighbor.next);
            else if(tentative_g_score >= g_score[neighbor.next].val)
                continue;

            came_from[neighbor.next] = current;
            g_score[neighbor.next].val = tentative_g_score;
            f_score[neighbor.next].val = g_score[neighbor.next].val + heuristic(neighbor.next, end);

        }
    }

}



int main() {
    Graph graph;
    Vertex start, end, v1, v2;
    float cost;

    std::cin >> start >> end;

    while (std::cin >> v1 >> v2 >> cost)
        graph[v1].push_back(Edge(v2, cost));

    std::vector<Vertex> path = astar(graph, start, end);

    for (auto const &vertex: path) {
        std::cout << vertex;
    }

    return 0;
}
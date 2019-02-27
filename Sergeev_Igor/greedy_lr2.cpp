#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

class Peak {
public:
    char name;
    Peak *cameFrom = nullptr;
    bool visited;
    vector<Peak*> neighbors;
    Peak(char name) {
        this->name = name;
        this->visited = false;
    }
    bool operator ==(const Peak& p) {
        return this->name == p.name;
    }
};



class Edge {
public:
    Edge(Peak *from, Peak *to, double cost) {
        this->start = from;
        this->end = to;
        this->cost = cost;
    }
    Peak *start;
    Peak *end;
    double cost;
};


string reconstruct(Peak *end) {
    Peak *current = end;
    string path = "";
    path += current->name;
    while (current->cameFrom != nullptr) {
        current = current->cameFrom;
        path = current->name + path;
    }
    return path;
}


double distBetween(Peak *current, Peak *neighbor, std::vector<Edge*> &edges) {
    for (Edge *e : edges) {
    if (e->start == current && e->end == neighbor) {
        return e->cost;
}
    }
    return 10000.0;
}

void greed(vector<Edge*> &edges, Peak *start, Peak *goal) {
    start->visited = true;
    if (start->name == goal->name) return;
    for (int i = 0; i < start->neighbors.size();i++) {
        double min_w = 10000.0;
        Peak *next = nullptr;
        for (Peak *p : start->neighbors) {
            if (distBetween(start, p, edges) < min_w && p->visited == false) {
                min_w = distBetween(start, p, edges);
                next = p;
            }
    }
        if (next != nullptr) {
            next->cameFrom = start;
            greed(edges, next, goal);
        }
        else return;
    }
    return;
}


int main()
{
    vector<Edge*> edges;
    vector<Peak*> peaks;
    Peak *startPeak = nullptr;
    Peak *goalPeak = nullptr;
    char start, end;
    cin >> start >> end;
    string line;
    while (getline(cin, line)) {
        char from;
        char to;
        double cost;
        stringstream ss(line);
        ss >> from >> to >> cost;
        Peak *p_from = nullptr;
        Peak *p_to = nullptr;
        for (Peak *p : peaks) {
            if (p->name == from) p_from = p;
            if (p->name == to) p_to = p;
        }
        if (p_from == nullptr) {
            p_from = new Peak(from);
            peaks.push_back(p_from);
        }
        if (p_to == nullptr) {
            p_to = new Peak(to);
            peaks.push_back(p_to);
        }
        if (p_from->name == start) startPeak = p_from;
        if (p_to->name == end) goalPeak = p_to;
        (p_from->neighbors).push_back(p_to);
        edges.push_back(new Edge(p_from, p_to, cost));
    }
    greed(edges, startPeak, goalPeak);
    cout << reconstruct(goalPeak) << endl;
    return 0;
}
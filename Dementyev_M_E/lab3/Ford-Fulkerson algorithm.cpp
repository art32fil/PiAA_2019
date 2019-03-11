//
//  main.cpp
//  F_F
//
//  Created by Михаил Дементьев on 04/03/2019.
//  Copyright © 2019 Михаил Дементьев. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Corner {
    char from;
    char to;
    int capacity;
    
    Corner(char _from, char _to, int _capacity) : from(_from), to(_to), capacity(_capacity) {}
};

struct Graph {
    
    vector<Corner> corners;
    
    void add(char from, char to, int additionalCapacity) {
        for (auto &edge : corners) {
            if (edge.from == from && edge.to == to) {
                edge.capacity += additionalCapacity;
                return;
            }
        }

        Corner e(from, to, additionalCapacity);
        corners.push_back(e);
    }
    
    vector<Corner> depthSearch(char from, char to) {
        set<char> visited;
        return depthSearch(from, to, visited);
    }
    
    int degree(char from) {
        int degree = 0;
        for (auto &edge : corners) {
            if (edge.from == from) {
                degree += edge.capacity;
            }
        }
        return degree;
    }
    
    void print() {
        sort(corners.begin(), corners.end(), [](const Corner &a, const Corner b) {
            return a.from != b.from ?
            a.from < b.from :
            a.to < b.to;
        });
        
        for (auto &edge: corners) {
            cout << edge.from << " " << edge.to << " " << edge.capacity << endl;
        }
    }
    
    vector<Corner> findCycle() {
        for (auto &edge: corners) {
            set<char> visited;
            auto cycle = findCycle(edge.from, edge.from, visited);
            if (!cycle.empty()) return cycle;
        }
        vector<Corner> no_cycle;
        return no_cycle;
    }
    
    void clearNulls() {
        corners.erase(remove_if(corners.begin(), corners.end(), [](const Corner edge) {
            return edge.capacity == 0;
        }), corners.end());
    }
    
private:
    
    vector<Corner> findCycle(char root, char from, set<char> &visited) {
        visited.insert(from);
        for (auto &edge:corners) {
            if (edge.from == from && edge.capacity != 0) {
                if (visited.find(edge.to) != visited.end()) {
                    if (edge.to == root) {
                        vector<Corner> cycle;
                        cycle.push_back(edge);
                        return cycle;
                    }
                } else {
                    auto cycle = findCycle(root, edge.to, visited);
                    if (!cycle.empty()) {
                        cycle.push_back(edge);
                        return cycle;
                    }
                }
            }
        }

        vector<Corner> no_cycle;
        return no_cycle;
    }
    
    vector<Corner> depthSearch(char from, char to, set<char> &visited) {
        visited.insert(from);
        for (auto &edge:corners) {
            if (edge.from == from && edge.capacity != 0) {
                if (edge.to == to) {
                    visited.insert(edge.to);
                    vector<Corner> path;
                    path.push_back(edge);
                    return path;
                }
                if (visited.find(edge.to) == visited.end()) {
                    visited.insert(edge.to);
                    auto path = depthSearch(edge.to, to, visited);
                    if (!path.empty()) {
                        path.push_back(edge);
                        return path;
                    }
                }
            }
        }
        
       
        vector<Corner> path;
        return path;
    }
    
};


void dropCycles(Graph &graph) {
    for (auto cycle = graph.findCycle(); !cycle.empty(); cycle = graph.findCycle()) {
        int capacityMin = 1000000000;
        for (auto &edge : cycle) if (capacityMin > edge.capacity) capacityMin = edge.capacity;
        for (auto &edge : cycle) graph.add(edge.from, edge.to, -capacityMin);
    }
}


void zeroCapacityCopy(const Graph &from, Graph &where) {
    for (auto &edge: from.corners) {
        where.add(edge.from, edge.to, 0);
    }
}

int main() {
    int N;
    cin >> N;
    
    char source;
    cin >> source;
    
    char stock;
    cin >> stock;
    
    Graph graph;
    
    for (int i = 0, capacity; i < N; ++i) {
        char from, to;
        cin >> from >> to >> capacity;
        graph.add(from, to, capacity);
    }
    
    Graph real;
    
    zeroCapacityCopy(graph, real);
    
    for (auto path = graph.depthSearch(source, stock); !path.empty(); path = graph.depthSearch(source, stock)) {
        
        int capacityMin = 1000000000;
        for (auto &edge : path) if (capacityMin > edge.capacity) capacityMin = edge.capacity;
        
        for (auto &edge : path) {
            graph.add(edge.from, edge.to, -capacityMin);
            real.add(edge.from, edge.to, capacityMin);
        }
    }
    
    dropCycles(real);
    
    cout << real.degree(source) << endl;
    
    real.print();
    
}

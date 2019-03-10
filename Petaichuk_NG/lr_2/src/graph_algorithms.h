#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef char Vertex;
struct Edge
{
    Vertex where;
    double length;

    Edge(Vertex end, double length) : where(end), length(length) {}
};

typedef vector<Vertex> Vertex_List;
typedef map<Vertex, vector<Edge>> Graph;
typedef Graph::iterator graph_iterator;

string findWay_Greedy(Graph &field, Vertex start, Vertex end);

string findWay_AStar(Graph &field, Vertex start, Vertex end);

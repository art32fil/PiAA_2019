#include <iostream>
#include "graph_algorithms.h"

int main()
{
    Graph field;
    Vertex start, finish, start_vertex, finish_vertex;
    double length;

    cin >> start >> finish;
    while (cin >> start_vertex >> finish_vertex >> length)
        field[start_vertex].push_back(Edge(finish_vertex, length));

    cout << "A* algorithm:" << endl;
    cout << findWay_AStar(field, start, finish) << endl;
    cout << "Greedy algorithm:" << endl;
    cout << findWay_Greedy(field, start, finish) << endl;

    return 0;
}

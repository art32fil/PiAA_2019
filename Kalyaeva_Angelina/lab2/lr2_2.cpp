#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Vertex {
public:
	char name_of_vertex;
	bool viewing;
	int heuristic;
	double priority;
	vector<Vertex*> neighbour;
	vector<double> weight;
	Vertex* from;
	Vertex(char name) :name_of_vertex(name), viewing(false), heuristic(0),priority(0.0), from(NULL) {}
};

void creation_of_graph(char from, char to, char end, double weight, vector<Vertex*>& graph) {
	int index1 = -1;
	int index2 = -1;
	for (size_t i = 0; i < graph.size(); i++) {
		if (from == graph[i]->name_of_vertex) {
			index1 = i;
		}
		if (to == graph[i]->name_of_vertex) {
			index2 = i;
		}
	}
	if (index1 == -1) {
		Vertex *tmp1 = new Vertex(from);
		graph.push_back(tmp1);
		index1 = graph.size() - 1;
	}
	if (index2 == -1) {
		Vertex *tmp2 = new Vertex(to);
		graph.push_back(tmp2);
		index2 = graph.size() - 1;
	}
	graph[index1]->neighbour.push_back(graph[index2]);
	graph[index1]->weight.push_back(weight);
	graph[index1]->heuristic = abs(end - from);
}

void print_graph(vector<Vertex*> graph) {
	for (size_t i = 0; i < graph.size(); i++) {
		cout << graph[i]->name_of_vertex << " " << graph[i]->viewing << " " << graph[i]->heuristic << endl;
		for (size_t j = 0; j < graph[i]->neighbour.size(); j++) {
			cout << graph[i]->neighbour[j]->name_of_vertex << " " << graph[i]->weight[j] << endl;
		}
		cout << "___________________" << endl;
	}
}

bool cmp(const Vertex* a, const Vertex* b) {
	return a->priority > b->priority;
}

void creation_priority_list(Vertex* vertex, vector<Vertex*>& list) {
	bool flag = false;
	double current_path = vertex->priority - vertex->heuristic;
	for (size_t i = 0; i < vertex->neighbour.size(); i++) {
		if (vertex->neighbour[i]->viewing == false) {
			if ((vertex->neighbour[i]->priority == 0) || (current_path + vertex->weight[i] + vertex->neighbour[i]->heuristic < vertex->neighbour[i]->priority)) {
				vertex->neighbour[i]->priority = current_path + vertex->weight[i] + vertex->neighbour[i]->heuristic;
				vertex->neighbour[i]->from = vertex;
				flag = false;
				for (size_t j = 0; j < list.size(); j++) {
					if (list[j]->name_of_vertex == vertex->neighbour[i]->name_of_vertex)
						flag = true;
				}
				if (flag == false) {
					list.push_back(vertex->neighbour[i]);
				}
			}
		}
	}
}

void Astar(Vertex* start, Vertex* end, vector<char>& way) {
	vector<Vertex*> priority_list;
	bool exit_flag = false;
	Vertex* new_start = start;
	new_start->priority = new_start->heuristic;
	while (exit_flag==false) {
		if (new_start->name_of_vertex == end->name_of_vertex) {
			exit_flag = true;
		}
		else {
			new_start->viewing = true;
			creation_priority_list(new_start, priority_list);
			sort(priority_list.begin(), priority_list.end(), cmp);
			new_start = priority_list[priority_list.size() - 1];
			priority_list.pop_back();
		}
	}
	while (new_start != NULL) {
		way.push_back(new_start->name_of_vertex);
		new_start = new_start->from;
	}
}

int main() {
	char start;
	char end;
	int number_start;
	int number_end;
	char from;
	char to;
	double weight;
	vector<Vertex*> graph;
	vector<char> way;
	cin >> start >> end;
	while (true) {
		if ((cin >> from) && (cin >> to) && (cin >> weight)) {
			creation_of_graph(from, to, end, weight, graph);
		}
		else {
			break;
		}
	}
	//print_graph(graph);
	for (size_t i = 0; i < graph.size(); i++) {
		if (graph[i]->name_of_vertex == start) {
			number_start = i;
		}
		if (graph[i]->name_of_vertex == end) {
			number_end = i;
		}
	}
	Astar(graph[number_start], graph[number_end], way);
	for (int i = way.size()-1; i >=0; i--) {
		cout << way[i];
	}
	cout << endl;
	system("pause");
	return 0;
}
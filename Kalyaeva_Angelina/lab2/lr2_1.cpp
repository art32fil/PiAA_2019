#include <iostream>
#include <vector>

#define MAX 1000000000.0

using namespace std;

class Vertex {
public:
	char name_of_vertex;
	bool viewing;
	vector<Vertex*> neighbour;
	vector<double> weight;
	Vertex(char name):name_of_vertex(name), viewing(false){}
};

void creation_of_graph(char from, char to, double weight, vector<Vertex*>& graph){
	int index1 = -1;
	int index2 = -1;
	for (size_t i = 0; i < graph.size(); i++) {
		if (from==graph[i]->name_of_vertex) {
			index1 = i;
		}
		if (to == graph[i]->name_of_vertex) {
			index2 = i;
		}
	}
	if (index1 == -1) {
		Vertex *tmp1= new Vertex(from);
		graph.push_back(tmp1);
		index1 = graph.size() - 1;
	}
	if (index2 == -1) {
		Vertex *tmp2=new Vertex(to);
		graph.push_back(tmp2);
		index2 = graph.size() - 1;
	}
	graph[index1]->neighbour.push_back(graph[index2]);
	graph[index1]->weight.push_back(weight);
}

void print_graph(vector<Vertex*> graph) {
	for (size_t i = 0; i < graph.size(); i++) {
		cout << graph[i]->name_of_vertex << " " << graph[i]->viewing << endl;
		for (size_t j = 0; j < graph[i]->neighbour.size(); j++) {
			cout << graph[i]->neighbour[j]->name_of_vertex << " " << graph[i]->weight[j] << endl;
		}
		cout<< "___________________" << endl;
	}
}

bool find_by_weight(vector<Vertex*> neighbour, vector<double> weight, Vertex*& new_start) {
	double min = MAX;
	int index = -1;
	if (neighbour.size() == 0) {
		return false;
	}
	for (size_t i = 0; i < neighbour.size(); i++) {
		if (neighbour[i]->viewing == false && weight[i] < min) {
			min = weight[i];
			index = i;
		}
	}
	if (index >= 0) {
		new_start=neighbour[index];
		return true;
	}
	else {
		return false;
	}
}
bool greedy_search(Vertex* start, Vertex* end, vector<char>& way) {
	way.push_back(start->name_of_vertex);
	start->viewing = true;
	if (start->name_of_vertex == end->name_of_vertex) {
		return true;
	}
	else {
		Vertex *new_start=NULL;
		while (find_by_weight(start->neighbour, start->weight, new_start)) {
			if (greedy_search(new_start, end, way)) {
				return true;
			}
		}
		way.pop_back();
		return false;
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
			creation_of_graph(from, to, weight, graph);
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
	if (greedy_search(graph[number_start], graph[number_end], way)) {
		for (size_t i = 0; i < way.size(); i++) {
			cout << way[i];
		}
	}
	system("pause");
	return 0;
}
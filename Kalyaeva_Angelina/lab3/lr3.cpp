#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

#define MAX 10000000
#define COUNT 26

using namespace std;

class Ford_Falkerson {
	int size;
	char source;
	char stock;
	char from;
	char to;
	int cost;
	int delta = 0;
	vector<vector<int>> graph;
	vector<vector<int>> flows;
	vector<bool>visited;
	vector<int> way;
public:
	Ford_Falkerson(int digit, char symbol) :size(digit), source(symbol), stock(symbol), from(symbol), to(symbol), cost(digit), delta(digit), graph(COUNT, vector<int>(COUNT, 0)), flows(COUNT, vector<int>(COUNT, 0)), 
					  visited(COUNT, false), way(COUNT, 0){}
	void print_graph() {
		for (int i = 0; i < COUNT; i++) {
			for (int j = 0; j < COUNT; j++) {
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}
	}
	void creation_graph() {
		cin >> size >> source >> stock;
		if (isalpha(source)) {
			delta = 97;
		}
		else {
			delta = 49;
		}
		for (int i = 0; i < size; i++)
		{
			cin >> from >> to >> cost;
			graph[from - delta][to - delta] = cost;
		}
	}

	void clear() {
		for (size_t i = 0; i < COUNT; i++) {
			way[i] = 0;
		}
	}

	void DFS(int vertex) {
		visited[vertex - delta] = true;
		for (size_t i = 0; i < visited.size(); i++) {
			if (!visited[i] && (graph[vertex - delta][i] - flows[vertex - delta][i] > 0 && graph[vertex - delta][i] != 0 || flows[vertex - delta][i] < 0 && graph[i][vertex - delta] != 0)) {
				way[i] = vertex;
				DFS(i + delta);
			}
		}
	}

	bool get_way() {
		DFS(source);
		for (size_t i = 0; i < visited.size(); i++) {
			visited[i] = false;
		}
		return (way[stock - delta] != 0);
	}

	int FF() {
		int max_flow = 0;
		while (get_way()) {
			int tmp = MAX;
			for (int v = stock - delta; 0 <= way[v] - delta; v = way[v] - delta) {
				tmp = min(tmp, graph[way[v] - delta][v] - flows[way[v] - delta][v]);
			}
			for (int v = stock - delta; 0 <= way[v] - delta; v = way[v] - delta) {
				flows[way[v] - delta][v] += tmp;
				flows[v][way[v] - delta] -= tmp;
			}
			max_flow += tmp;
			clear();
		}
		return max_flow;
	}

	void print_result() {
		for (int i = 0; i < COUNT; i++) {
			for (int j = 0; j < COUNT; j++) {
				if (flows[i][j] != 0 && flows[i][j] < 0)
					flows[i][j] = 0;
				if (graph[i][j] > 0)
					cout << (char)(i + delta) << " " << (char)(j + delta) << " " << flows[i][j] << endl;
			}
		}
	}
};


int main() {
	Ford_Falkerson A(0, '\0');
	A.creation_graph();
	cout <<A.FF()<< endl;
	A.print_result();
	system("pause");
	return 0;
}
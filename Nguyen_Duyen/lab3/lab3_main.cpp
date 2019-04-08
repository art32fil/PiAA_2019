#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph(26, vector<int>(26, 0));
vector<vector<int>> flow(26, vector<int>(26, 0));
vector<bool> visited(26, false);
vector<int> trace(26, 0);
int delta;

void DFS(int cur) {
	int v = cur - delta;
	visited[v] = true;
	for (size_t i = 0; i < visited.size(); i++) {
		if (!visited[i] && (graph[v][i] - flow[v][i] > 0 && graph[v][i]!=0 || flow[v][i] < 0 && graph[i][v] != 0)) {
			trace[i] = cur;
			DFS(i + delta);
		}
	}
}

bool buildPath(char start, char end) {
	DFS(start);
	for (size_t i = 0; i < visited.size(); i++) {
		visited[i] = false;
	}
	return trace[end - delta] != 0;
}

int FordFulkerson(char start, char end) {
	int max_flow = 0;
	while (buildPath(start, end)) {
		int path_flow = 100000;
		for (int v = end - delta; trace[v] - delta >= 0; v = trace[v] - delta) {
			int u = trace[v] - delta;
			path_flow = min(path_flow, graph[u][v] - flow[u][v]);
		}
		for (int v = end - delta; trace[v] - delta >= 0; v = trace[v] - delta) {
			int u = trace[v] - delta;
			flow[u][v] += path_flow;
			flow[v][u] -= path_flow;
		}
		max_flow += path_flow;
		for (size_t i = 0; i < trace.size(); i++) {
			trace[i] = 0;
		}
	}
	return max_flow;
}

int main()
{
	int n;
	char start, end, from, to;
	int cost;

	cin >> n >> start >> end;

	delta = isalpha(start) ? 97 : 49;

	for(int i = 0; i < n; i++) {
		cin >> from >> to >> cost;
		int u = from - delta;
		int v = to - delta;
		graph[u][v] = cost;
	}
	cout << FordFulkerson(start, end) << endl;

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (flow[i][j] != 0 && flow[i][j] < 0)
				flow[i][j] = 0;
			if (graph[i][j] > 0)
				cout << (char)(i + delta) << " " << (char)(j + delta) << " " << flow[i][j] << endl;
		}
	}

	system("pause");
	return 0;
}

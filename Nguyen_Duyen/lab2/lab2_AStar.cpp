#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Vertex {
public:
	char name;
	double gScore, fScore;
	Vertex *cameFrom = nullptr;
	vector < Vertex*> neighbors;
	Vertex(char name) {
		this->name = name;
		this->gScore = 10000.0;
		this->fScore = 10000.0;
	}
};

class Path {
public:
	Vertex *start, *end;
	double weight;
	Path() {};
	Path(Vertex *s, Vertex *e, double w) {
		this->start = s;
		this->end = e;
		this->weight = w;
	}
	~Path() {
		delete start;
		delete end;
	}
};

double dist_between(Vertex *current, Vertex *neighbor, vector<Path*> &path) {
	for (size_t i = 0; i < path.size(); i++) {
		if (path[i]->start == current && path[i]->end == neighbor)
			return path[i]->weight;
	}
	return 10000.0;
}

string reconstruct(Vertex *current) {
	string total_path = { current->name };
	while (current->cameFrom != nullptr) {
		current = current->cameFrom;
		total_path = current->name + total_path;
	}
	return total_path;
}

double heuristic(char a, char b) {
	return abs(a - b);
}

string AStar(vector<Path*> &path, Vertex *start, Vertex *end) {
	vector<Vertex*> closedSet;
	vector<Vertex*> openSet ;
	openSet.push_back(start);

	start->gScore = 0;
	start->fScore = heuristic(start->name, end->name);

	while (openSet.size() != 0) {
		Vertex* current = openSet.at(0);
		int index = 0;
		for (size_t i = 0; i < openSet.size(); i++) {
			if (openSet[i]->fScore < current->fScore) {
				current = openSet[i];
				index = i;
			}
		}

		if (current->name == end->name)
			return reconstruct(current);

		openSet.erase(openSet.begin() + index);
		closedSet.push_back(current);

		for (size_t i = 0; i < current->neighbors.size(); i++) {
			if (find(closedSet.begin(), closedSet.end(), current->neighbors[i]) != closedSet.end()) 
				continue;

			double tentative_gScore = current->gScore + dist_between(current, current->neighbors[i], path);

			if (find(openSet.begin(), openSet.end(), current->neighbors[i]) != openSet.end()) {
				if (tentative_gScore >= current->neighbors[i]->gScore)
					continue;
			}

			else 
				openSet.push_back(current->neighbors[i]);

			current->neighbors[i]->cameFrom = current;
			current->neighbors[i]->gScore = tentative_gScore;
			current->neighbors[i]->fScore = current->neighbors[i]->gScore + heuristic(current->neighbors[i]->name, end->name);
		}
	}
	return "";
}

int main()
{
	vector<Path*> path;
	char start_way, end_way;
	cin >> start_way >> end_way;

	Vertex *start = nullptr;
	Vertex *end = nullptr;

	while (true) {
		char s, e;
		double w;
		if ((cin >> s) && (cin >> e) && (cin >> w)) {
			Vertex *s_ver = new Vertex(s);
			Vertex *e_ver = new Vertex(e);

			for (size_t i = 0; i < path.size(); i++) {
				if (path[i]->start->name == s) 
					s_ver = path[i]->start;
				
				if (path[i]->start->name == e) 
					e_ver = path[i]->start;
				
				if (path[i]->end->name == s) 
					s_ver = path[i]->end;
				
				if (path[i]->end->name == e) 
					e_ver = path[i]->end;
			}

			if (s_ver->name == start_way)
				start = s_ver;
			if (e_ver->name == end_way)
				end = e_ver;

			s_ver->neighbors.push_back(e_ver);

			Path *p = new Path(s_ver, e_ver, w);
			path.push_back(p);
		}
		else	break;
	}

	cout << AStar(path, start, end) << endl;
	
	system("pause");
	return 0;
}

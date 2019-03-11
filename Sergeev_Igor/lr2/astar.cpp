#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector> 
#include <limits>
#include <cmath>

using namespace std;

class Peak {
public:
	char name;
	double gScore;
	double fScore;
	Peak *cameFrom = nullptr;
	std::vector<Peak*> neighbors;

	Peak(char name) {
		this->name = name;
		this->gScore = 10000.0;
		this->fScore = 10000.0;
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


double calHeuristic(Peak *a, Peak *b) {
	return abs(a->name - b->name);
}

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
double distBetween(Peak *current, Peak *neighbor, vector<Edge*> &edges) {
	for (Edge *e : edges) {
		if (e->start == current && e->end == neighbor) {
			return e->cost;
		}
	}
	return 10000.0;
}

std::string A_Star(vector<Edge*> &edges, Peak *start, Peak *goal) {
	vector<Peak*> closedSet;
	vector<Peak*> openSet;
	openSet.push_back(start);
	start->gScore = 0;
	start->fScore = calHeuristic(start, goal);
	while (openSet.size() != 0) {
		Peak *current = openSet.at(0);
		int current_index = 0;
		for (int i = 0; i < openSet.size(); i++) {
			if (openSet[i]->fScore < current->fScore) {
				current = openSet[i];
				current_index = i;
			}
		}
		if (current == goal) {
			return reconstruct(current);
		}
		openSet.erase(openSet.begin() + current_index);
		closedSet.push_back(current);
		for (Peak *neighbor : current->neighbors) {
			if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
				continue;
			}
			double tentative_gScore = current->gScore + distBetween(current, neighbor, edges);
			if (std::find(openSet.begin(), openSet.end(), neighbor) != openSet.end()) {
				if (tentative_gScore >= neighbor->gScore)
					continue;
			}
			else {
				openSet.push_back(neighbor); 
			}
			neighbor->cameFrom = current;
			neighbor->gScore = tentative_gScore;
			neighbor->fScore = neighbor->gScore + calHeuristic(neighbor, goal);
		}
	}
	return "";
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
	cout << A_Star(edges, startPeak, goalPeak) << endl;
	for (Edge *e : edges) {
		delete e;
	}
	for (Peak *p : peaks) {
		delete p;
	}
    return 0;
}
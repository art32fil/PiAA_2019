// lr2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector> 
#include <limits>
#include <cmath>
class Peak {
public:
	char name;
	double gScore;
	double fScore;
	Peak *cameFrom = nullptr;
	std::vector<Peak*> neighbors;

	Peak(char name) {
		this->name = name;
		this->gScore = std::numeric_limits<double>::max();
		this->fScore = std::numeric_limits<double>::max();
	}
	bool operator ==(const Peak& p) {
		return this->name == p.name;
	}
};
class Edge {
public:
	Edge(Peak *s, Peak *e, double w) {
		this->start = s;
		this->end = e;
		this->weight = w;
	}
	Peak *start;
	Peak *end;
	double weight;
};
double calHeuristic(Peak *a, Peak *b) {
	return abs(a->name - b->name);
}

std::string reconstruct(Peak *end) {
	Peak *current = end;
	std::string path = "";
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
			return e->weight;
		}
	}
	return std::numeric_limits<double>::max();
}

std::string A_Star(std::vector<Edge*> &edges, Peak *start, Peak *goal) {
	// The set of nodes already evaluated
	std::vector<Peak*> closedSet;

	// The set of currently discovered nodes that are not evaluated yet.
	// Initially, only the start node is known.
	std::vector<Peak*> openSet;
	openSet.push_back(start);

	// The cost of going from start to start is zero.
	start->gScore = 0;

	// For each node, the total cost of getting from the start node to the goal
    // by passing by that node. That value is partly known, partly heuristic.
	// For the first node, that value is completely heuristic.
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
			// reconstruct path
			return reconstruct(current);
		}

		openSet.erase(openSet.begin() + current_index);
		closedSet.push_back(current);
		for (Peak *neighbor : current->neighbors) {
			if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
				/* contains */
				// Ignore the neighbor which is already evaluated.
				continue;
			}

			// The distance from start to a neighbor
			double tentative_gScore = current->gScore + distBetween(current, neighbor, edges);

			if (std::find(openSet.begin(), openSet.end(), neighbor) != openSet.end()) {
				if (tentative_gScore >= neighbor->gScore)
					continue;
			}
			else {
				// Not contained in open set -> Discovered a new node
				openSet.push_back(neighbor); 
			}

			// Record the path (best until now)
			neighbor->cameFrom = current;
			neighbor->gScore = tentative_gScore;
			neighbor->fScore = neighbor->gScore + calHeuristic(neighbor, goal);
		}
	}
	return "";
}
int main()
{
	std::vector<Edge*> edges;
	std::vector<Peak*> peaks;
	Peak *startPeak = nullptr;
	Peak *goalPeak = nullptr;
	
	// Input
	char start, end;
	std::cin >> start >> end;
	while (getchar() != '\n');

	std::string line;
	while (std::getline(std::cin, line)) {
		char s;
		char e;
		double w;
		std::stringstream ss(line);
		ss >> s >> e >> w;

		Peak *p_s = nullptr;
		Peak *p_e = nullptr;
		for (Peak *p : peaks) {
			if (p->name == s) p_s = p;
			if (p->name == e) p_e = p;
		}
		if (p_s == nullptr) {
			p_s = new Peak(s);
			peaks.push_back(p_s);
		}
		if (p_e == nullptr) {
			p_e = new Peak(e);
			peaks.push_back(p_e);
		}
		if (p_s->name == start) startPeak = p_s;
		if (p_e->name == end) goalPeak = p_e;
		(p_s->neighbors).push_back(p_e);
		edges.push_back(new Edge(p_s, p_e, w));

	}

	// Print out the path
	std::cout << A_Star(edges, startPeak, goalPeak) << std::endl;
	getchar();

	// Clean up
	for (Edge *e : edges) {
		delete e;
	}
	for (Peak *p : peaks) {
		delete p;
	}

	return 0;
}
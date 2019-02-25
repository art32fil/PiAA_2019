//// lr2.cpp : Defines the entry point for the console application.
////
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
	Peak *cameFrom = nullptr;
	bool visited;
	std::vector<Peak*> neighbors;

	Peak(char name) {
		this->name = name;
		this->visited = false;
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
void Greedy(std::vector<Edge*> &edges, Peak *start, Peak *goal) {
	start->visited = true;
	//std::cout << "visited " << start->name<<std::endl;
	if (start->name == goal->name) return;

	for (int i = 0; i < start->neighbors.size();i++) {
		double min_w = std::numeric_limits<double>::max();
		//std::cout << "trying " << p->name << std::endl;

		Peak *next = nullptr;
		for (Peak *p : start->neighbors) {
			if (distBetween(start, p, edges) < min_w && p->visited == false) {
				min_w = distBetween(start, p, edges);
				next = p;
			}
			//std::cout << "   trying " << p2->name << " " << distBetween(start, p2, edges) << " " << next << std::endl;
		}
		if (next != nullptr) {
			next->cameFrom = start;
			Greedy(edges, next, goal);
		}
		else return;
	}
	return;
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
	Greedy(edges, startPeak, goalPeak);
	std::cout << reconstruct(goalPeak) << std::endl;
	std::cin.clear();
	getchar();

	return 0;
}
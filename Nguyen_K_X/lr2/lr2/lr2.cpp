// lr2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector> 
class Edge {
public:
	Edge(char s, char e, double w) {
		this->start = s;
		this->end = e;
		this->weight = w;
		this->travelled = false;
	}
	char start;
	char end;
	double weight;
	bool travelled;
};
bool compare(Edge a, Edge b) {
	//Problem is here, if I put '<' (ascending order for endpoint), -> #1 wrong answer
	// If I put '>' -> #3 wrong answer 
	if (a.weight == b.weight) return a.end < b.end;
	else
		return a.weight < b.weight;
}
int main()
{
	char startPeak, endPeak;
	std::cin >> startPeak >> endPeak;
	while (getchar() != '\n');
	std::string s;
	std::stringstream path;
	std::vector<Edge> edges;
	// Input
	while (std::getline(std::cin, s)) {
		char a;
		char b;
		double w;
		std::stringstream ss(s);
		ss >> a >> b >> w;
		Edge e(a, b, w);
		edges.push_back(e);
	}
	//Sort edges by weight, if similar weight then sort them by end-point in alphabet order
	std::sort(edges.begin(), edges.end(), compare);

	char current = startPeak; // Start (Step 1)
	path << startPeak;
	while (current != endPeak) {
		Edge *min = nullptr;
		// Search for nodes, which we can go to from current (Step 2)
		for (int i = 0; i < edges.size(); i++) {
			if (edges[i].start == current && !edges[i].travelled) {
				min = &(edges[i]);
				// Because we sorted the edges' list, choose the first one (Step 3)
				break;
			}
		}
		if (min == nullptr) {
			break;
		}
		// Move to that point (Step 1)
		path << min->end;
		current = min->end;
		min->travelled = true;
	}
	// Print out the path
	std::cout << path.str() << std::endl;
	getchar();
	return 0;
}
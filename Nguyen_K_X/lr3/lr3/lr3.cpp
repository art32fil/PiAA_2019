// lr3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector> 
#include <limits>
#include <cmath>
#include <deque>
class Peak;
class Edge;
class Peak {
public:
	char name;
	Edge *cameFrom = nullptr;
	std::vector<Edge*> *linked_edges;

	Peak(char name) {
		this->name = name;
		linked_edges = new std::vector < Edge*>();
	}
	~Peak() {
		delete linked_edges;
	}
	bool operator ==(const Peak& p) {
		return this->name == p.name;
	}
};
class Edge {
public:
	Edge(Peak *s, Peak *e, int c) {
		this->start = s;
		this->end = e;
		this->c = c;
		this->f = 0;
	}
	Peak *start;
	Peak *end;
	int f;
	int c;
	int cf(Peak *from) const {
		if (from == start)
			return c - f;
		else
			return f;
		//return c - f;
	}
	friend std::ostream& operator <<(std::ostream& stream, const Edge&  edge) {
		return stream << edge.start->name << " " << edge.end->name<<" "<<edge.f<< std::endl;
		//return stream << edge.start->name << " " << edge.end->name << "   " << edge.f << "/" << edge.c << std::endl;
	}
};

bool compare(Edge *a, Edge *b) {

	if (a->start->name == b->start->name) return a->end->name < b->end->name;
	else
		return a->start->name < b->start->name;
}
int main()
{
	std::vector<Edge*> edges;
	std::vector<Peak*> peaks;
	Peak *sourcePeak = nullptr;
	Peak *sinkPeak = nullptr;
	// Input

	int N;
	char source, sink;
	std::cin >> N >> source >> sink;

	for (int i = 0; i < N; i++) {
		char u;
		char v;
		int c;
		std::cin >> u >> v >> c;

		Peak *p_u = nullptr;
		Peak *p_v = nullptr;
		for (Peak *p : peaks) {
			if (p->name == u) p_u = p;
			if (p->name == v) p_v = p;
		}
		if (p_u == nullptr) {
			p_u = new Peak(u);
			peaks.push_back(p_u);
		}
		if (p_v == nullptr) {
			p_v = new Peak(v);
			peaks.push_back(p_v);
		}
		if (p_u->name == source) sourcePeak = p_u;
		if (p_v->name == sink) sinkPeak = p_v;
		Edge *e = new Edge(p_u, p_v, c);
		(p_u->linked_edges)->push_back(e);
		(p_v->linked_edges)->push_back(e);
		edges.push_back(e);
	}

	while (true) {
		std::deque<Peak*> open_set;
		std::vector<Peak*> closed_set;
		open_set.push_back(sourcePeak);
		while (!open_set.empty()) {
			Peak* current = open_set.back();
			open_set.pop_back();
			
			//std::cout << "processing " << current->name << std::endl;
			if (current == sinkPeak) {
				// found the path
				break;
			}
			for (Edge *e : *(current->linked_edges)) {
				if (e->cf(current) > 0) {
					Peak *other = e->end == current ? e->start : e->end;

					if (std::find(closed_set.begin(), closed_set.end(), other) != closed_set.end()) {
						// Already processed (in closed set)
						continue;
					}

					if (std::find(open_set.begin(), open_set.end(), other) == open_set.end()) {
						// not in open set
						open_set.push_back(other);
						other->cameFrom = e;
					}
				}
			}
			closed_set.push_back(current);
		}
		std::deque<Edge*> path;
		int cf_min = std::numeric_limits<int>::max();
		//Trace back from sink to get the path (in reverse order);
		{
			Peak *current = sinkPeak;
			while (current->cameFrom != nullptr) {
				Peak *back = current->cameFrom->start == current ? current->cameFrom->end : current->cameFrom->start;

				path.push_front(current->cameFrom);

				int cfp = current->cameFrom->cf(back);
				cf_min = cf_min > cfp ? cfp : cf_min;

				// clear came from field for next loop
				current->cameFrom = nullptr;
				current = back;

			}
		}
		// cannot find a path from source to sink, algorithm stop;
		if (path.empty()) break;

		////print before
		//std::cout << "Before: " << cf_min<< std::endl;
		//for (Edge *e : path) {
		//	std::cout << *e;
		//}
		////end print
		{
			Peak *current = sourcePeak;
			for (Edge *e : path) {
				if (e->start == current) {
					// f(u,v)
					e->f += cf_min;
					current = e->end;
				}
				else {
					//f(v,u)
					e->f -= cf_min;
					current = e->end;
				}
			}
		}
		//// print after
		//std::cout << "After: " << std::endl;
		//for (Edge *e : path) {
		//	std::cout << *e;
		//}
		//// end print

	}
	int total_flow = 0;

	for (Edge *e : *(sourcePeak->linked_edges)) {
		total_flow += e->f;
	}
	//std::cout << "Final result: " << std::endl;
	std::sort(edges.begin(), edges.end(), compare);
	std::cout << total_flow << std::endl;
	for (Edge *e : edges) {
		std::cout << *e;
	}

	// clean up
	for (Peak *p : peaks) {
		delete p;
	}
	for (Edge *e : edges) {
		delete e;
	}

	char c;
	std::cin >> c;
	return 0;
}
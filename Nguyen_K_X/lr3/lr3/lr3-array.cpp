// lr3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include <iostream>
//#include <string>
//#include <sstream>
//#include <algorithm>
//#include <vector> 
//#include <limits>
//#include <cmath>
//#include <queue> 
//using namespace std;
//
//
///* Returns true if there is a path from source 's' to sink 't' in
//residual graph. Also fills parent[] to store the path */
//bool bfs(int *rGraph, int s, int t, int *parent, int size)
//{
//	// Create a visited array and mark all vertices as not visited 
//	bool *visited = new bool[size];
//	for (int i = 0; i < size; i++) visited[i] = false;
//	// Create a queue, enqueue source vertex and mark source vertex 
//	// as visited 
//	deque <int> q;
//	q.push_back(s);
//	visited[s] = true;
//	parent[s] = -1;
//
//	// Standard BFS Loop 
//	while (!q.empty())
//	{
//		int u = q.back();
//		q.pop_back();
//
//		for (int v = 0; v<size; v++)
//		{
//			if (visited[v] == false && rGraph[u*size+v] > 0)
//			{
//				q.push_back(v);
//				parent[v] = u;
//				visited[v] = true;
//			}
//		}
//	}
//
//	// If we reached sink in BFS starting from source, then return 
//	// true, else false 
//	return (visited[t] == true);
//}
//
//// Returns the maximum flow from s to t in the given graph 
//int fordFulkerson(int *graph, int s, int t,int size, int **result)
//{
//	int u, v;
//
//	// Create a residual graph and fill the residual graph with 
//	// given capacities in the original graph as residual capacities 
//	// in residual graph 
//	int *rGraph = new int[size*size]; // Residual graph where rGraph[i][j] indicates  
//					  // residual capacity of edge from i to j (if there 
//					  // is an edge. If rGraph[i][j] is 0, then there is not)   
//	for (u = 0; u < size; u++)
//		for (v = 0; v < size; v++)
//			rGraph[u*size+v] = graph[u*size+v];
//
//	int *parent= new int[size];  // This array is filled by BFS and to store path 
//
//	int max_flow = 0;  // There is no flow initially 
//
//					   // Augment the flow while tere is path from source to sink 
//	while (bfs(rGraph, s, t, parent,size))
//	{
//		// Find minimum residual capacity of the edges along the 
//		// path filled by BFS. Or we can say find the maximum flow 
//		// through the path found. 
//		int path_flow = 9999999;
//		for (v = t; v != s; v = parent[v])
//		{
//			u = parent[v];
//			path_flow = min(path_flow, rGraph[u*size+v]);
//		}
//
//		// update residual capacities of the edges and reverse edges 
//		// along the path 
//		for (v = t; v != s; v = parent[v])
//		{
//			u = parent[v];
//			rGraph[u*size+v] -= path_flow;
//			rGraph[v*size+u] += path_flow;
//		}
//		
//		// Add path flow to overall flow 
//		max_flow += path_flow;
//	}
//	*result = rGraph;
//	//std::cout << std::endl;
//	//for (int i = 0; i < size; i++) {
//	//	for (int j = 0; j < size; j++) {
//	//		std::cout << rGraph[i*size + j] << " ";
//	//	}
//	//	std::cout << std::endl;
//	//}
//	// Return the overall flow 
//	return max_flow;
//}
//
//int main()
//{
//	// Input
//
//	int N;
//	unsigned char source, sink;
//
//	std::cin >> N >> source >> sink;
//	int *graph = new int[N*N];
//	for (int i = 0; i < N*N; i++) graph[i] = 0;
//	unsigned int *edges = new unsigned int[N * 2];
//	for (int i = 0; i < N; i++) {
//		unsigned char u;
//		unsigned char v;
//		int c;
//		std::cin >> u >> v >> c;
//		u = u - 97;
//		v = v - 97;
//		edges[i] = u;
//		edges[N+i] = v;
//		graph[u*N + v] = c;
//
//	}
//	int *result = nullptr;
//	cout << fordFulkerson(graph, source-97, sink-97,N,&result)<<std::endl;
//	/*std::cout << std::endl;
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			std::cout << graph[i*N + j]<<" ";
//		}
//		std::cout << std::endl;
//	}*/
//
//	for (int i = 0; i < N; i++) {
//		std::cout << (unsigned char)(edges[i] + 97) << " " << (unsigned char)(edges[N + i] + 97) <<" "<< result[edges[N+i] * N + edges[ i]] << std::endl;
//	}
//	char c;
//	std::cin >> c;
//	return 0;
//}
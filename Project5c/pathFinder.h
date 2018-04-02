//Patrick Hanbury and John Kang
//Algorithsm
//Project5a
//pathFinder.h headers

#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <stack>
#include "heapV.h"
#include "maze.h"
#include "graph.h"

#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

//Global Variables
Graph::vertex_descriptor noPred = NULL;


typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

// typedef property<edge_weight_t, int> EdgeProperty;

//relax function that relaxes the edge between nodes u and v in a graph
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v);

//Determines the shortest path from node s to every node in g. Node weights must
//be positive. returns tru if path exists to every node, and false if no
bool dijkstra(Graph &g, Graph::vertex_descriptor s);

//Determines shortest path from node s to every other node in g, where graph can have
//negative weights. Returns false if negative cycle is reachable, and true otherwise
bool bellmanFord(Graph &g, Graph::vertex_descriptor s);


void findShortestPathBFS(Graph & g, stack<Graph::vertex_descriptor> &s) {
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> startToEnd = vertices(g);
	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> currentMoves;
	std::queue<Graph::vertex_descriptor> search;
	Graph::vertex_descriptor current;
	search.push(*startToEnd.first);
	while (!search.empty()) {
		current = search.front();
		search.pop();
		if (current == *startToEnd.second - 1) {
			while (current) {
				s.push(current);
				current = g[current].pred;
			}
			s.push(*startToEnd.first);
			return;
		}
		if (!g[current].visited) {
			g[current].visited = true;
			currentMoves = adjacent_vertices(current, g);
			for (Graph::adjacency_iterator adjacent = currentMoves.first; adjacent != currentMoves.second; ++adjacent) {
				if (!g[*adjacent].visited) {
					search.push(*adjacent);
					g[*adjacent].pred = current;
				}
			}
		}
	}
}

void findPathDFSStack(Graph & g, stack<Graph::vertex_descriptor> &s) {
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> startToEnd = vertices(g);
	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> currentMoves;
	std::stack<Graph::vertex_descriptor> search;
	Graph::vertex_descriptor current;
	search.push(*startToEnd.first);

	while (!search.empty()) {
		current = search.top();
		search.pop();
		if (current == *startToEnd.second - 1) {
			while (current) {
				s.push(current);
				current = g[current].pred;
			}
			s.push(*startToEnd.first);
			return;
		}
		if (!g[current].visited) {
			g[current].visited = true;
			currentMoves = adjacent_vertices(current, g);

			for (Graph::adjacency_iterator adjacent = currentMoves.first; adjacent != currentMoves.second; ++adjacent) {
				if (!g[*adjacent].visited) {
					search.push(*adjacent);
					g[*adjacent].pred = current;
				}
			}
		}
	}
}

bool findPathDFSRecursive(Graph & g, Graph::vertex_descriptor v, stack<Graph::vertex_descriptor> &s) {
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> startToEnd = vertices(g);
	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> legalMoves = adjacent_vertices(v, g);
	g[v].visited = true;
	if (v == *startToEnd.second - 1) {
		s.push(v);
		return true;
	}
	for (Graph::adjacency_iterator vItr = legalMoves.first; vItr != legalMoves.second; ++vItr) {
		if (!g[*vItr].visited) {
			g[*vItr].visited = true;
			if (findPathDFSRecursive(g, *vItr, s)) {
				s.push(v);
				return true;
			}
		}
	}
	return false;
}

std::stack<Graph::vertex_descriptor> findShortestPathDFS(Graph g, Graph::vertex_descriptor v) {

	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> startToEnd = vertices(g);
	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> legalMoves = adjacent_vertices(v, g);
	std::stack<Graph::vertex_descriptor> partialPath, path;
	g[v].visited = true;
	if (v == *startToEnd.second - 1) {
		partialPath.push(v);
		return partialPath;
	}
	for (Graph::adjacency_iterator vItr = legalMoves.first; vItr != legalMoves.second; ++vItr) {
		if (!g[*vItr].visited) {
			g[*vItr].visited = true;
			partialPath = findShortestPathDFS(g, *vItr);
			if (partialPath.size()) {
				partialPath.push(v);
				if (partialPath.size() < path.size() || path.size() == 0) {
					path = partialPath;
				}
				for (int k = 0; k < partialPath.size(); k++)
					partialPath.pop();
			}
		}
	}
	return path;
}

//relax function that relaxes the edge between nodes u and v in a graph
void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v) {

	//CODE


}

void initSingleSource(Graph &g, Graph::vertex_descriptor source) {
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		g[*vItr].weight = LargeValue;
		g[*vItr].visited = false;
		g[*vItr].pred = noPred;
	}
	g[source].weight = 0;
}

//Determines the shortest path from node s to every node in g. Node weights must
//be positive. returns tru if path exists to every node, and false if no
bool dijkstra(Graph &g, Graph::vertex_descriptor s) {
	initSingleSource(g, s);
	int weight;
	heapV<Graph::vertex_descriptor, Graph> minQueue;
	Graph::vertex_descriptor u, v;
	std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	std::pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRangeA;
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		minQueue.minHeapInsert(*vItr, g);
	}
	while (!minQueue.isEmpty()) {
		u = minQueue.extractMinHeapMinimum(g);
		g[u].visited = true;
		vItrRangeA = adjacent_vertices(u, g);
		for (Graph::adjacency_iterator vItr = vItrRangeA.first; vItr != vItrRangeA.second; ++vItr) {
			v = *vItr;
			if (!g[v].visited) {
				weight = g[v].weight;
				relax(g, edge(u, v, g).first);
				if (weight != g[v].weight)
					minQueue.minHeapDecreaseKey(minQueue.getIndex(v), g);
			}
		}
	}
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		if (g[*vItr].pred == noPred && *vItr != s)
			return false;
	}
	return true;
}

//Determines shortest path from node s to every other node in g, where graph can have
//negative weights. Returns false if negative cycle is reachable, and true otherwise
bool bellmanFord(Graph &g, Graph::vertex_descriptor s) {
	std::pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
	initSingleSource(g, s);
	for (int i = 1; i < num_vertices(g); i++) {
		for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) {
			relax(g, *eItr);
		}
	}
	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) {
		if (g[target(*eItr, g)].weight > g[source(*eItr, g)].weight + g[*eItr].weight) {
			return false;
		}
	}
	return true;
}


#endif

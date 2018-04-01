#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <stack>
#include "maze.h"
#include "graph.h"
#include "pathFinder.h"

#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;


typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

// typedef property<edge_weight_t, int> EdgeProperty;

#define LargeValue 99999999

int main()
{
	try
	{
		ifstream fin;

		// Read the maze from the file.
		string fileName = "maze-files/maze-files/maze1.txt";

		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			system("pause");
			exit(1);
		}

		maze m(fin);
		fin.close();
		

		//declare graph structure that will hold the maze
		Graph g;
		m.mapMazeToGraph(g);
		pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
		Graph::vertex_descriptor endNode = *vItrRange.first;

		//solve shortest path using DFS
		cout << "Shortest Path using DFS: " << endl;
		stack<Graph::vertex_descriptor> pathStackShortestDFS = findShortestPathDFS(g, *vItrRange.first);
		m.printPath(endNode, pathStackShortestDFS, g);
		
		
		//solve shortest path using BFS
		cout << "Shortest Path using BFS:" << endl;
		stack<Graph::vertex_descriptor> pathStackShortestBFS;
		findShortestPathBFS(g, pathStackShortestBFS);
		m.printPath(endNode, pathStackShortestBFS, g);
		

		//solve graph using DFS stack
		cout << "Solved Graph using DFS Stack: " << endl;
		stack<Graph::vertex_descriptor> pathStackDFS;
		findPathDFSStack(g, pathStackDFS);
		//print graph with path
		m.printPath(endNode, pathStackDFS, g);

		//solve graph using DFS recursive
		cout << "Solved graph using DFS Recursive: " << endl;
		stack<Graph::vertex_descriptor> pathStackDFSRecursive;
		findPathDFSRecursive(g, *vItrRange.first, pathStackDFSRecursive);
		m.printPath(endNode, pathStackDFSRecursive, g);

		system("pause");
	}

	catch(...){
		cout << "TRY Clause in main function failed" << endl;
		exit(1);
	}

}

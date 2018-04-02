//P Hanbury and J Kang
//Algorithms
//Project5c
//
//The pupose of this program is to find the shortest path in a maze using Dijksta's
//Algorithm and the Bellman-Ford Algorithm.

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

bool checkNegativeWeights(Graph &g);

#define LargeValue 99999999

int main()
{
	ifstream fin;

	// Read the maze from the file.
	string fileName = "maze-files/maze-files/maze1.txt";
		
	fin.open(fileName.c_str());
	if (!fin){
		cerr << "Cannot open " << fileName << endl;
		system("pause");
		exit(1);
	}

	//initialize maze and input data from file using maze constructor
	maze m(fin);
	fin.close();
	
	//declare graph structure that will hold the maze
	Graph g;
	m.mapMazeToGraph(g);
	//get the range of the graph
	pair<Graph::vertex_descriptor, Graph::vertex_descriptor> vItrRange = vertices(g);


			/*dijkstra algorithm run */
	//Check to make sure no negative weights exists
	if (!checkNegativeWeights(g)) {
		cout << "Negative Weights found in Graph. Dijkstra's Alorithm not used." << endl;
	}
	else {

	}


	return 0;
}

bool checkNegativeWeights(Graph & g)
{
	//CODE

	return false;
}

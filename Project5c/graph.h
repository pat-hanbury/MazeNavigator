//Patrick Hanbury and John Kang
//Algorithsm
//Project5a
//Graph.h headers




#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

//structs for the properties for the Vertex and Edge node
struct VertexProperties; 
struct EdgeProperties; 

//customize adjacency list with a vector for nodes and a vector for edges, as well as custom properties
typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

#define LargeValue 99999999



//overloaded print operator for custom graph type
inline std::ostream & operator << (std::ostream & ostr, const Graph & g) {
	//hold iterators for beginning and end of node vector
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g); 
	//hold iterators for beginning and end of edge vector
	pair <Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g); 
	//iterate over entire node vector
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; vItr++) {
		//print the properties of the nodes
		ostr << "node: " << *vItr << std::endl;
		ostr << "	cell: " << g[*vItr].cell.first << "," << g[*vItr].cell.second << std::endl;
		ostr << "	weight: " << g[*vItr].weight << std::endl;
		ostr << "	visited: " << g[*vItr].visited << std::endl;
		ostr << "	marked: " << g[*vItr].marked << std::endl;
	}
	//iterate over edge vector, print out edge descriptor
	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; eItr++) {
		ostr << "edge: " << source(*eItr, g) << "," << target(*eItr, g) << std::endl;
	}
	return ostr;
}

#endif

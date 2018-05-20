// Ismail Kheir //
// Assignment 5 Part 2 Driver //

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>
#include <map>
#include "vertex.h"
#include "graph.h"
using namespace std;

int main (int argc, char **argv) {
	if (argc != 3) {
		cout << "Enter a graph and a starting vertex to run program" << endl;
		return 0;
	}

	Graph graph;
	string graph_filename = argv[1];
	string vertex_input = argv[2];
	int start_vertexID = stoi (vertex_input);
	
	// Parsing //
	graph.ParseVertices (graph_filename);

	// Find Shortest Path //
	graph.ShortestPath (start_vertexID);
	
	return 0;
}

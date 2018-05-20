// Ismail Kheir //
// Assignment 5 Part 1 Driver //

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "vertex.h"
#include "graph.h"
using namespace std;

int main (int argc, char **argv) {
	if (argc != 3) {
		cout << "Enter a graph file and adjacency file to run program." << endl;
		return 0;
	}
	string graph_filename = argv[1];
	string adjqueries_filename = argv[2];

	Graph graph;
	graph.ParseVertices (graph_filename);
	graph.TestQueries (adjqueries_filename);
	
	return 0;
}

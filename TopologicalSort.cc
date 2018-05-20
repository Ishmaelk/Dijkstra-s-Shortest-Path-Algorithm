// Ismail Kheir //
// Assignment 5 Part 3 Driver //

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include "vertex.h"
#include "graph.h"
using namespace std;

int main (int argc, char ** argv) {
	if (argc != 2) {
		cout << "Enter a single graph file to run program." << endl;
		return 0;
	}
	// Process Input //
	string file_name = argv[1];
	Graph graph;
	
	// Process file input //
	graph.ParseVertices (file_name);
	// Do Topological Sort //	
	graph.TopologicalSort ();
	return 0;
}

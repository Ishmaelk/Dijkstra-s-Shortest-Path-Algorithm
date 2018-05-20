// Ismail Kheir //
// Graph Struct Class Header & Implementation //

#ifndef __GRAPH__
#define __GRAPH__
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include "vertex.h"

struct Graph {
	
	std::vector<Vertex*> vertices_;
	std::map<int, Vertex*> vertex_map_; // links vertexID's to the original vertex node containing them
	// Sorts vertices by their distance relative to a starting vertex, see ShortestPath
	std::priority_queue<Vertex*, std::vector<Vertex*>, Vertex::CompareVertices> p_queue_;
	// Links vertexID's to a list of adjacent vertices // 
	std::map<int, std::list<Vertex*>> adjacency_list_;	
	
	// Takes in a filename and populates all graph class's containers //
	std::vector<Vertex*> ParseVertices (const std::string &graph_filename) {
		std::ifstream graph_data;
		graph_data.open (graph_filename.c_str());
		std::string str = "";
		bool skip = true;
        	// Iterate through file to populate vertex_map_ with original vertices //
        	while (std::getline (graph_data, str)) {
                	if (str == "" || skip == true)
                        { skip = false; continue; }
                	std::stringstream ss (str);
                	std::vector<std::string> tokens;
                	while (std::getline (ss, str, ' '))
                        	tokens.push_back (str);
                	int vertexID = std::stoi (tokens[0]);
                	Vertex * vertex = new Vertex {vertexID};
			vertices_.push_back (vertex);
                	vertex_map_[vertexID] = vertex;
			std::list <Vertex*> adj_list;
			adjacency_list_[vertexID] = adj_list;
        	}
		// Reset File Parsing  to get adjacent vertices//
		skip = true; graph_data.clear (); graph_data.seekg (0, graph_data.beg);
        	while (getline (graph_data, str)) { // split by each line
                	if (str == "" || skip == true)
			{ skip = false; continue; }
			std::stringstream ss (str);
                	std::vector<std::string> tokens;
                	while (getline (ss, str, ' ')) // split each line on ' '
                        	tokens.push_back(str);
                	int id = std::stoi (tokens[0]);
                	for (unsigned int i = 0; i < tokens.size(); i++) {
                        	if (i % 2 == 1) { // vertices fall on odd indices
                                	int adj_vertexID = std::stoi (tokens[i]);
                                	float adj_weight = std::stof (tokens[i+1]);
                                	Vertex * adj_vertex = new Vertex {adj_vertexID, adj_weight};
                                	vertex_map_[id]->adj_vert_.push (adj_vertex);
					adjacency_list_[id].push_back (adj_vertex);
                        	}
                	}
        	}
		graph_data.close ();
		return vertices_;
	}

	// Tests if there is a connection between any two vertices, the commented out code
	// considers the connection going from vertex2 to vertex1 
	float TestConnection (const int vertex1, const int vertex2) {
		for (auto v : vertices_) {
			if (v->ID == vertex1) {
				auto &list = adjacency_list_[v->ID];
				for (auto itr = list.begin (); itr != list.end (); itr++) {
					Vertex *a = *itr;
					if (a->ID == vertex2)
						return a->distance;
				}
			} 
			
			/*else if (v->ID == vertex2) {
				auto &list = adjacency_list_[v->ID];
				for (auto itr = list.begin (); itr != list.end (); itr++) {
					Vertex *a = *itr;
					if (a->ID == vertex1)
						return a->distance;
				}
			}*/
		}
		return -1.0;
	}
	// Takes in a query filename and tests connections between the first vertex to the second vertex
	// by calling TestConnection Method 
	void TestQueries (std::string &query_filename) {
		std::string str = "";
		std::ifstream query_data;
		query_data.open (query_filename.c_str());
		while (std::getline(query_data, str)) {
			std::stringstream ss (str);
			std::vector<std::string> tokens;
			while (std::getline(ss, str, ' '))
				tokens.push_back (str);
			int vertex1 = std::stoi (tokens[0]);
			int vertex2 = std::stoi (tokens[1]);
			std::cout << vertex1 << " " << vertex2 << ": ";
			float weight_of_edge = TestConnection (vertex1, vertex2);
			if (weight_of_edge == -1.0)
				std::cout << "Not Connected" << std::endl;
			else
				std::cout << "Connected, weight of edge is " << weight_of_edge << std::endl;
		}
		query_data.close ();
	}

	// (Dijkstras) start_id is the id of the vertex you are starting at
	// This Method Finds the shortest path to all other nodes from the starting vertex
	void ShortestPath (int start_id) {
		vertex_map_[start_id]->distance = 0;
		// Populate priority queue //
		for (auto v : vertices_)
			p_queue_.push (v);
		// Calculate Shortest Paths //
		while (p_queue_.empty () != true) {
			Vertex *v = p_queue_.top ();
			while (v->adj_vert_.empty () != true) {
				Vertex *a = v->adj_vert_.top ();
				if (!a->known) {
					float cost = a->distance;
					if (vertex_map_[v->ID]->distance + cost < vertex_map_[a->ID]->distance) {
						vertex_map_[a->ID]->distance = vertex_map_[v->ID]->distance + cost;
						vertex_map_[a->ID]->path = v;
					}
				} 
				v->adj_vert_.pop ();
			}
			p_queue_.pop ();
			vertex_map_[v->ID]->known = true;
		}
		// Output distance & path //
		for (auto i : vertices_) {
			float cost = vertex_map_[i->ID]->distance;
			std::vector<int> pathway;
			pathway.push_back (i->ID);
			std::cout << i->ID << ": ";
			while (i->ID != start_id) { // going from destination to start //
				pathway.push_back (i->ID);
				i = i->path; // record path in pathway
			}
			pathway.push_back (start_id);
			// output path backwards since we recorded it backwards
			for (unsigned int i = pathway.size()-1; i > 0; i--) 
				std::cout << pathway[i] << " ";
			std::cout << "(Cost: " << cost << ")" << std::endl;	
		}
	}

	// called within IsCyclic checks for cycles recursively //
	bool _isCyclic (Vertex &v, bool *visited, bool *recStk) {
        	if (visited[v.ID] == false) {
                	visited[v.ID] = true;// record that we have visited 
			recStk[v.ID] = true;
			std::priority_queue<Vertex*, std::vector<Vertex*>, Vertex::CompareVertices>
			copy_queue = v.adj_vert_; // copy adjacent heap to avoid altering it prematurely
			while (copy_queue.empty () != true) {
                        	Vertex * a = copy_queue.top ();
				// if we have not visited a vertex and there is a cycle in its adjacents
				if (!visited[a->ID] && _isCyclic (*vertex_map_[a->ID], visited, recStk))
                                	return true; // we know there is a cycle if it shows in our recStk bools
                        	else if (recStk[a->ID])
                	                return true;
				copy_queue.pop ();	
			}
        	}
        	recStk[v.ID] = false; // if there was no cycle rest our recStk for that vertex
        	return false;
	}	

	// User Method that checks if there are cycles recursively //
	bool IsCyclic () {
		bool visited[vertices_.size()];
		bool recStk[vertices_.size()];		
		for (unsigned int i = 0; i < vertices_.size(); i++) {
                	visited[i] = false;
			recStk[i] = false;
		}
        	for (auto v : vertices_)
                	if (_isCyclic (*v, visited, recStk))
                	        return true;
        	return false;
	}

	// visits unknown nodes that are adjacent to the current vertex recursively
	void _topologicalSort (Vertex * v, std::stack<Vertex*> &stk) {
		vertex_map_[v->ID]->known = true;
        	while (v->adj_vert_.empty () != true) {
			Vertex * a = v->adj_vert_.top (); 
		        if (vertex_map_[a->ID]->known == false)
                	        _topologicalSort (vertex_map_[a->ID], stk);
			v->adj_vert_.pop ();
        	}
        	stk.push(v); // and adds to a stack
	}

	// User method to topologically sort vertices
	void TopologicalSort () {
		if (IsCyclic ()) {
                        std::cout << "Cycle Found" << std::endl;
                        return;
                }
		// Initialize containers for recursive calls //
        	std::stack<Vertex*> stk;
        	for (auto i : vertices_) // make sure known is false
                	vertex_map_[i->ID]->known = false;
        	// if vertex is unknown recursively visit it and its neighbors
        	for (auto i : vertices_) {
                	if (vertex_map_[i->ID]->known == false)
                	        _topologicalSort (i, stk);
        	}

		// output topological ordering 
        	while (!stk.empty ()) {
                	std::cout << stk.top ()->ID << " ";
                	stk.pop ();
        	} std::cout << std::endl;
	}

	// Deallocate Memory assigned to vertices //
	~Graph () {
		for (auto &v : vertices_)
			if (v != nullptr) {
				delete v;
				v = nullptr;
			}
	}

};
#endif

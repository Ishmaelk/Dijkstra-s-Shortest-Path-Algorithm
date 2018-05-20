// Ismail Kheir //
// Vertex struct header & implementation //


#ifndef __VERTEX__
#define __VERTEX__

#include <queue>
#include <vector>
#include <limits>

struct Vertex {
        int ID;
	float distance;
        bool known;
        Vertex* path;

        Vertex (const int id, const float dist=std::numeric_limits<float>::max(), const bool k = false) {
                ID = id;
                distance = dist;
                known = k;
		path = this;
        }

	struct CompareVertices {
        	bool operator () (const Vertex *lhs, const Vertex *rhs) const {
                	return lhs->distance >= rhs->distance;
        	}
	};
	// adj_vert_ are ordered in a minheap //
	std::priority_queue<Vertex*, std::vector<Vertex*>, CompareVertices> adj_vert_;
};

#endif

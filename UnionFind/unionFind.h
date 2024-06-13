#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_
#include "queue.h"
#include <iostream>

struct UnionNode {
    int parent; // The parent of the node
    int rank;   // Rank of the set
};

class UnionFind {
private:
    UnionNode *set;         // Array to store id of graph's vertices
    int numOfVertices;      // Number of vertices in the set

public:
    UnionFind(int numOfVertices);  // Create array
    ~UnionFind();                  // Delete array
    void makeSet(int vertex);      // Make set in the array
    int findSet(int vertex);       // Returns the root of the vertex's tree
    void unionSets(Edge &edge); // Union two sets into one
    bool isOneSet();         // Returns true if there is only one set, otherwise returns false
    void printSet();         // Print the set
};

#endif // _UNION_FIND_H_
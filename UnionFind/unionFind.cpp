#include "unionFind.h"

UnionFind::UnionFind(int numOfVertices) {
    set = new UnionNode[numOfVertices];
    this->numOfVertices = numOfVertices;
}

UnionFind::~UnionFind() {
    delete[] set;
}

void UnionFind::makeSet(int vertex) {
    set[vertex].parent = vertex;
    set[vertex].rank = 0;
}

int UnionFind::findSet(int vertex) {
    if (set[vertex].parent != vertex) {
        set[vertex].parent = findSet(set[vertex].parent);
    }
    return set[vertex].parent;
}

void UnionFind::unionSets(Edge &edge) {
    int root1, root2;

    root1 = findSet(edge.vertexStart); // Find the root of the tree with vertexStart
    root2 = findSet(edge.vertexEnd);   // Find the root of the tree with vertexEnd

    if (root1 != root2) { // Roots must be different
        if (set[root1].rank > set[root2].rank) { // Compare roots ranks
            set[root2].parent = root1;           // root1 is greater, union root2
        } else {
            set[root1].parent = root2; // root2 is greater, union root1
            if (set[root1].rank == set[root2].rank) {
                set[root2].rank++;
            }
        }
    }
}

bool UnionFind::isOneSet() {
    int firstParent = findSet(0);

    for (int i = 1; i < this->numOfVertices; i++) {
        if (firstParent != findSet(i)) return false;
    }
    return true;
}

void UnionFind::printSet() {
    std::cout << "Set: ";
    for (int i = 0; i < this->numOfVertices; i++) {
        std::cout << findSet(i) << " ";
    }
    std::cout << std::endl;
}
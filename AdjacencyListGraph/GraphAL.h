#ifndef GRAPHAL_H
#define GRAPHAL_H

#include <string>

struct Node {
    int vertex;
    int edge;
    Node* next;

    Node(int vertex, int edge) : vertex(vertex), edge(edge), next(nullptr) {}
};

class GraphAL {
private:
    Node** array;
    int numOfVertexes;
    int numOfEdges;
    int weight;

public:
    GraphAL();
    ~GraphAL();
    void printGraph();
    void setNumOfVertexes(int);
    void setNumOfEdges(int);
    int getNumOfVertexes();
    int getNumOfEdges();
    Node* getList(int);
    void addVertexes(int);
    void addDirectedEdge(int, int, int);
    void addUndirectedEdge(int, int, int);

    void fillGraphFromFile(std::string &filePath, bool directed);
};

#endif // GRAPHAL_H
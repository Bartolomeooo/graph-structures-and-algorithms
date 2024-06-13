#ifndef _GRAPH_INCIDENCE_MATRIX_H_
#define _GRAPH_INCIDENCE_MATRIX_H_

class GraphIM{ // Graph in incidence matrix
private:
    int **graph; // Two-dimensional array representing incidence matrix
    int numOfVertexes; // Number of vertices in the graph
    int numOfEdges; // Number of edges in the graph
    int weight; // Weight of the whole graph
public:
    GraphIM(); // Constructor
    ~GraphIM(); // Destructor
    void printGraph(); // Printing incidence matrix
    void setNumOfVertexes(int); // Set the number of vertices
    void setNumOfEdges(int); // Set the number of edges
    void setElement(int i, int j, int value);
    int getNumOfVertexes(); // Get the number of vertices
    int getNumOfEdges(); // Get the number of edges
    int findElement(int, int); // Return the value from the array
    int getStartingVertexOfEdge(int); // Get the starting vertex of the given edge
    int getEndingVertexOfEdge(int); // Get the ending vertex of the given edge
    int getEndingVertexOfUndirectedEdge(int, int); // Get the ending vertex of the given undirected edge
    void addDirectedEdge(int, int, int); // Add directed edge to the graph
    void addUndirectedEdge(int, int, int); // Add undirected edge to the graph
    void addVertexes(int); // Add vertexes to the graph, without the edges
    bool checkIfEdgeExists(int, int); // Return true if the given edge exist, false if it doesn't exist
    void fillGraphFromFile(std::string &filePath, bool directed);
};

#endif
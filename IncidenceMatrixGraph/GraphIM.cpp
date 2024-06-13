#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include<vector>
#include "GraphIM.h"

using namespace std;

GraphIM::GraphIM() {
    numOfVertexes = 0;
    numOfEdges = 0;
    graph = nullptr;
    weight = 0;
}

GraphIM::~GraphIM() {
    for (int i = 0; i < numOfVertexes; i++) delete[] graph[i];
    delete[] graph;
}

void GraphIM::printGraph() {
    if (numOfVertexes == 0) {
        cout << " Graph is empty!" << endl;
        return;
    }
    cout << "    ";
    for (int j = 0; j < numOfEdges; j++) {
        cout << setw(5) << j;
    }
    cout << endl << "    ";
    for (int j = 0; j < numOfEdges * 5 + 3; j++) {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < numOfVertexes; i++) {
        cout << " " << i << " |";
        for (int j = 0; j < numOfEdges; j++) {
            cout << setw(5) << graph[i][j];
        }
        cout << endl;
    }
    cout << endl << " Graph weight: " << weight << endl << endl;
}

void GraphIM::setNumOfEdges(int num) {
    this->numOfEdges = num;
}

void GraphIM::setNumOfVertexes(int num) {
    this->numOfVertexes = num;
}

int GraphIM::getNumOfEdges() {
    return numOfEdges;
}

int GraphIM::getNumOfVertexes() {
    return numOfVertexes;
}

int GraphIM::findElement(int n, int m) {
    return graph[n][m];
}

int GraphIM::getStartingVertexOfEdge(int j) {
    if (j > numOfEdges - 1) return -1;

    for (int i = 0; i < numOfVertexes; i++) {
        if (graph[i][j] > 0)
            return i;
    }
    return -1;
}

int GraphIM::getEndingVertexOfEdge(int j) {
    if (j > numOfEdges - 1) return -1;

    for (int i = 0; i < numOfVertexes; i++) {
        if (graph[i][j] < 0)
            return i;
    }
    return -1;
}

int GraphIM::getEndingVertexOfUndirectedEdge(int j, int currentVertex) {
    if (j > numOfEdges - 1) return -1;

    for (int i = 0; i < numOfVertexes; i++) {
        if (i == currentVertex) continue;
        if (graph[i][j] > 0)
            return i;
    }
    return -1;
}

bool GraphIM::checkIfEdgeExists(int v1, int v2) {
    for (int i = 0; i < this->numOfEdges; i++) {
        if (graph[v1][i] > 0 && graph[v2][i] != 0)
            return true;
    }
    return false;
}

void GraphIM::addVertexes(int vertexes) {
    this->graph = new int *[vertexes];
    this->numOfVertexes = vertexes;
    for (int i = 0; i < numOfVertexes; i++) {
        this->graph[i] = new int[0];
    }
}

void GraphIM::addUndirectedEdge(int ver1, int ver2, int dist) {
    for(int i = 0; i < this->numOfVertexes; i++){
        graph[i] = (int*) realloc(graph[i], (this->numOfEdges + 1)*sizeof(int)); //reallocating the arrays for the new edge
        graph[i][this->numOfEdges] = 0; //filling the new edge with zeros
    }

    graph[ver1][this->numOfEdges] = dist; //setting the value of the edge for the starting vertex
    graph[ver2][this->numOfEdges] = dist; //setting the value of the edge for the ending vertex - edge is undirected so the value is the same as for the starting vertex
    this->weight += dist; //increase weight of the graph
    this->numOfEdges += 1; //increase number of edges
}

void GraphIM::addDirectedEdge(int ver1, int ver2, int dist) {
    for(int i = 0; i < this->numOfVertexes; i++){
        graph[i] = (int*) realloc(graph[i], (this->numOfEdges + 1)*sizeof(int)); // Reallocing the arrays for the new edge
        graph[i][this->numOfEdges] = 0; // Filling the new edge with zeros
    }

    graph[ver1][this->numOfEdges] = dist; // Setting the value of the edge for the starting vertex
    graph[ver2][this->numOfEdges] = -1*dist; // Setting the value of the edge for the ending vertex - edge is directed so the value is negative
    this->weight += dist; // Increase weight of the graph
    this->numOfEdges += 1; // Increase number of edges
}

void GraphIM::fillGraphFromFile(string& filePath, bool directed) {
    ifstream inFile(filePath);

    if (inFile.is_open()) {
        int numberOfEdges, numberOfVertexes;
        inFile >> numberOfEdges >> numberOfVertexes;

        this->addVertexes(numberOfVertexes);

        int vertexStart, vertexEnd, distanceValue;

        for (int i = 0; i < numberOfEdges; i++) {
            inFile >> vertexStart >> vertexEnd >> distanceValue;

            if (directed) this->addDirectedEdge(vertexStart, vertexEnd, distanceValue);
            else this->addUndirectedEdge(vertexStart, vertexEnd, distanceValue);
        }
        cout << " Successfully filled matrix!" << endl;
        inFile.close();
    } else {
        cerr << " Cannot open file: " << filePath << endl;
    }
}
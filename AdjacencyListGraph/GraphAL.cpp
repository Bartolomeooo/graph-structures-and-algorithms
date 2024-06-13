#include "GraphAL.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>

GraphAL::GraphAL() : array(nullptr), numOfVertexes(0), numOfEdges(0), weight(0) {}

GraphAL::~GraphAL() {
    for (int i = 0; i < numOfVertexes; i++) {
        Node* current = array[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] array;
}

void GraphAL::printGraph() {
    if (numOfVertexes == 0) {
        std::cout << "Graph is empty!" << std::endl;
        return;
    }
    for (int i = 0; i < numOfVertexes; i++) {
        std::cout << "[" << i << "] = ";
        Node* current = array[i];
        while (current) {
            std::cout << "(" << current->vertex << ":" << current->edge << ")";
            if (current->next) std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    std::cout << "Graph weight: " << weight << std::endl;
}

void GraphAL::setNumOfEdges(int num) { numOfEdges = num; }
void GraphAL::setNumOfVertexes(int num) { numOfVertexes = num; }

int GraphAL::getNumOfEdges() { return numOfEdges; }
int GraphAL::getNumOfVertexes() { return numOfVertexes; }

Node* GraphAL::getList(int ver) { return array[ver]; }

void GraphAL::addVertexes(int vertexes) {
    array = new Node*[vertexes];
    for (int i = 0; i < vertexes; i++) array[i] = nullptr;
    numOfVertexes = vertexes;
}

void GraphAL::addDirectedEdge(int ver1, int ver2, int dist) {
    Node* newNode = new Node(ver2, dist);
    newNode->next = array[ver1];
    array[ver1] = newNode;
    weight += dist;
    numOfEdges++;
}

void GraphAL::addUndirectedEdge(int ver1, int ver2, int dist) {
    addDirectedEdge(ver1, ver2, dist);
    addDirectedEdge(ver2, ver1, dist);
    weight -=dist;
}

void GraphAL::fillGraphFromFile(std::string& filePath, bool directed) {

    std::ifstream inFile(filePath); // Open the file with the description of the edges

    if (inFile.is_open()) { // If the file opened correctly, fill the graph
        int numEdges, numVertexes;
        inFile >> numEdges >> numVertexes; // Get number of edges and number of vertices from the file

        this->addVertexes(numVertexes); // Initialize graph by adding vertices without edges

        int vertexStart, vertexEnd, distanceValue;
        for (int i = 0; i < numEdges; i++) {
            inFile >> vertexStart >> vertexEnd >> distanceValue; // Get the description of the edge from the file

            if (directed) this->addDirectedEdge(vertexStart, vertexEnd, distanceValue); // If the graph ought to be directed - add directed edge
            else this->addUndirectedEdge(vertexStart, vertexEnd, distanceValue); // If the graph ought to be undirected - add undirected edge
        }
        std::cout << "Successfully filled the list!" << std::endl; // Filled the graph from file
        inFile.close();
    } else {
        std::cerr << "Cannot open file: " << filePath << std::endl; // Opening the file failed
    }
}
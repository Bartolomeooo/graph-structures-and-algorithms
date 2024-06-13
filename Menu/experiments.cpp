#include <iomanip>
#include "timer.cpp"
#include "MST.h"
#include "SP.h"
#include "array.cpp"

float unitFactor = 1000000.0f; // Microseconds
std::string unit = " microseconds";

void printResultsTable(const std::string &title, const array<float> &times, int densities[]) {
    std::cout << "\n" << title << " Results:\n";
    std::cout << std::setw(5) << "   Density         " << std::setw(10) << "Average Time (" + unit + ")\n";
    std::cout << std::string(50, '-') << "\n";

    for (size_t i = 0; i < times.size(); ++i) {
        std::cout << std::setw(7) << densities[i] <<" % "<< std::setw(20) << times[i] << "\n";
    }

    std::cout << std::endl;
}

void deleteGraphAL(GraphAL &graphAL, bool shouldPrint) { // Delete the graph in the adjacency list
    if (graphAL.getNumOfVertexes() == 0) { // If the graph is empty, print that and return
        if(shouldPrint) std::cout << " Graph is empty!" << std::endl;
        return;
    }

    graphAL = GraphAL();
    if (shouldPrint) std::cout << " Successfully deleted the list!" << std::endl;
}

void deleteGraphIM(GraphIM &graphIM, bool shouldPrint) { // Delete the graph in the incidence matrix
    if (graphIM.getNumOfVertexes() == 0) { // If the graph is empty, print that and return
        if(shouldPrint) std::cout << " Graph is empty!" << std::endl;
        return;
    }

    graphIM = GraphIM();
    if (shouldPrint) std::cout << " Successfully deleted the matrix!" << std::endl;
}

void generateGraph(GraphAL &graphAL, GraphIM &graphIM, int v, float density, bool directed, bool shouldPrint) {
    if (graphAL.getNumOfVertexes() != 0 || graphIM.getNumOfVertexes() != 0) { // If the graph is not empty, delete its content
        deleteGraphAL(graphAL, shouldPrint);
        deleteGraphIM(graphIM, shouldPrint);
        if (shouldPrint) std::cout << " Successfully deleted graphs!" << std::endl;
    }

    int edges = (int)((float)(((density / 100) * v * (v - 1)) / 2)); // Calculate the number of edges from the given density and number of vertices

    graphAL.addVertexes(v); // Initialize graph with vertices, no edges yet
    graphIM.addVertexes(v); // Initialize graph with vertices, no edges yet

    int currentEdges = 0;
    UnionFind set(v); // We will use union find to make sure that the graph is connected
    Edge edge;
    srand(time(NULL));

    for (int i = 0; i < v; i++) {
        set.makeSet(i);
    }

    while (!set.isOneSet()) { // Creating connected graph
        do {
            edge.vertexStart = rand() % v;
            edge.vertexEnd = rand() % v;
        } while ((edge.vertexStart == edge.vertexEnd) || (set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd))); // Draw new edge if the vertices are the same or if they are in the same set

        edge.weight = (rand() % (2 * edges)) + 1; // Draw the edge's weight from the range <1, number of edges * 2>

        if (!directed) {
            graphAL.addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            graphIM.addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        } else {
            graphAL.addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            graphIM.addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        }
        currentEdges++;
        set.unionSets(edge);
    }
    // Now we have a connected graph and need to add remaining edges
    while (currentEdges < edges) {
        do {
            edge.vertexStart = rand() % v;
            edge.vertexEnd = rand() % v;
        } while ((edge.vertexStart == edge.vertexEnd) || graphIM.checkIfEdgeExists(edge.vertexStart, edge.vertexEnd)); // Draw new edge if the vertices are the same or if the edge already exists

        edge.weight = (rand() % (2 * edges)) + 1; // Draw the edge's weight from the range <1, number of edges * 2>

        if (!directed) {
            graphAL.addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            graphIM.addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        } else {
            graphAL.addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
            graphIM.addDirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        }
        currentEdges++;
    }
    if (shouldPrint)
        std::cout << " Successfully filled graph with " << v << " vertices and " << currentEdges << " edges!" << std::endl;
}

void dijkstraExperiment(GraphAL &graphAL, GraphIM &graphIM) {
    srand(time(NULL));
    int numberOfVer, numberOfMeasurements;
    int densities[] = {25, 50, 99}; // Predefined densities
    array<float> timesAL(0), timesIM(0);

    do {
        std::cout << " Enter the number of vertices: ";
        std::cin >> numberOfVer;
    } while (numberOfVer < 0 || numberOfVer > 1000); // Ask for the input again if the value is not in the expected range

    do {
        std::cout << " Enter the number of measurements: ";
        std::cin >> numberOfMeasurements;
    } while (numberOfMeasurements < 0 || numberOfMeasurements > 5000); // Ask for the input again if the value is not in the expected range

    for (int density : densities) {
        float timeAL = 0, timeIM = 0;
        for (int i = 0; i < numberOfMeasurements; i++) {
            generateGraph(graphAL, graphIM, numberOfVer, density, true, false); // Generate random graph for each measurement
            Timer timerAL; // Set the timer for adjacency list
            SP::dijkstraAL(graphAL, 0, 0); // Perform Dijkstra's algorithm on the generated graph in adjacency list
            timeAL += timerAL.getTime().count() * unitFactor; // Stop the timer and count the time

            Timer timerIM; // Set the timer for incidence matrix
            SP::dijkstraIM(graphIM, 0, 0); // Perform Dijkstra's algorithm on the generated graph in incidence matrix
            timeIM += timerIM.getTime().count() * unitFactor; // Stop the timer and count the time
        }
        timesAL.PushBack(timeAL / numberOfMeasurements);
        timesIM.PushBack(timeIM / numberOfMeasurements);
    }

    printResultsTable("Dijkstra's Algorithm (Adjacency List)", timesAL, densities);
    printResultsTable("Dijkstra's Algorithm (Incidence Matrix)", timesIM, densities);

    deleteGraphAL(graphAL, false); // Delete the graph in adjacency list
    deleteGraphIM(graphIM, false); // Delete the graph in incidence matrix
}

void bellmanFordExperiment(GraphAL &graphAL, GraphIM &graphIM) {
    srand(time(NULL));
    int numberOfVer, numberOfMeasurements;
    int densities[] = {25, 50, 99}; // Predefined densities
    array<float> timesAL(0), timesIM(0);

    do {
        std::cout << " Enter the number of vertices: ";
        std::cin >> numberOfVer;
    } while (numberOfVer < 0 || numberOfVer > 1000); // Ask for the input again if the value is not in the expected range

    do {
        std::cout << " Enter the number of measurements: ";
        std::cin >> numberOfMeasurements;
    } while (numberOfMeasurements < 0 || numberOfMeasurements > 5000); // Ask for the input again if the value is not in the expected range

    for (int density : densities) {
        float timeAL = 0, timeIM = 0;
        for (int i = 0; i < numberOfMeasurements; i++) {
            generateGraph(graphAL, graphIM, numberOfVer, density, true, false); // Generate random graph for each measurement
            Timer timerAL; // Set the timer for adjacency list
            SP::bellmanFordAL(graphAL, 0, 0); // Perform Bellman-Ford algorithm on the generated graph in adjacency list
            timeAL += timerAL.getTime().count() * unitFactor; // Stop the timer and count the time

            Timer timerIM; // Set the timer for incidence matrix
            SP::bellmanFordIM(graphIM, 0, 0); // Perform Bellman-Ford algorithm on the generated graph in incidence matrix
            timeIM += timerIM.getTime().count() * unitFactor; // Stop the timer and count the time
        }
        timesAL.PushBack(timeAL / numberOfMeasurements);
        timesIM.PushBack(timeIM / numberOfMeasurements);
    }

    printResultsTable("Bellman-Ford Algorithm (Adjacency List)", timesAL, densities);
    printResultsTable("Bellman-Ford Algorithm (Incidence Matrix)", timesIM, densities);

    deleteGraphAL(graphAL, false); // Delete the graph in adjacency list
    deleteGraphIM(graphIM, false); // Delete the graph in incidence matrix
}

void primExperiment(GraphAL &graphAL, GraphIM &graphIM) {
    srand(time(NULL));
    int numberOfVer, numberOfMeasurements;
    int densities[] = {25, 50, 99}; // Predefined densities
    array<float> timesAL(0), timesIM(0);

    do {
        std::cout << " Enter the number of vertices: ";
        std::cin >> numberOfVer;
    } while (numberOfVer < 0 || numberOfVer > 1000); // Ask for the input again if the value is not in the expected range

    do {
        std::cout << " Enter the number of measurements: ";
        std::cin >> numberOfMeasurements;
    } while (numberOfMeasurements < 0 || numberOfMeasurements > 5000); // Ask for the input again if the value is not in the expected range

    for (int density : densities) {
        float timeAL = 0, timeIM = 0;
        for (int i = 0; i < numberOfMeasurements; i++) {
            generateGraph(graphAL, graphIM, numberOfVer, density, false, false); // Generate random graph for each measurement
            Timer timerAL; // Set the timer for adjacency list
            MST::primAL(graphAL, 0); // Perform Prim's algorithm on the generated graph in adjacency list
            timeAL += timerAL.getTime().count() * unitFactor; // Stop the timer and count the time

            Timer timerIM; // Set the timer for incidence matrix
            MST::primIM(graphIM, 0); // Perform Prim's algorithm on the generated graph in incidence matrix
            timeIM += timerIM.getTime().count() * unitFactor; // Stop the timer and count the time
        }
        timesAL.PushBack(timeAL / numberOfMeasurements);
        timesIM.PushBack(timeIM / numberOfMeasurements);
    }

    printResultsTable("Prim's Algorithm (Adjacency List)", timesAL, densities);
    printResultsTable("Prim's Algorithm (Incidence Matrix)", timesIM, densities);

    deleteGraphAL(graphAL, false); // Delete the graph in adjacency list
    deleteGraphIM(graphIM, false); // Delete the graph in incidence matrix
}

void kruskalExperiment(GraphAL &graphAL, GraphIM &graphIM) {
    srand(time(NULL));
    int numberOfVer, numberOfMeasurements;
    int densities[] = {25, 50, 99}; // Predefined densities
    array<float> timesAL(0), timesIM(0);

    do {
        std::cout << " Enter the number of vertices: ";
        std::cin >> numberOfVer;
    } while (numberOfVer < 0 || numberOfVer > 1000); // Ask for the input again if the value is not in the expected range

    do {
        std::cout << " Enter the number of measurements: ";
        std::cin >> numberOfMeasurements;
    } while (numberOfMeasurements < 0 || numberOfMeasurements > 5000); // Ask for the input again if the value is not in the expected range

    for (int density : densities) {
        float timeAL = 0, timeIM = 0;
        for (int i = 0; i < numberOfMeasurements; i++) {
            generateGraph(graphAL, graphIM, numberOfVer, density, false, false); // Generate random graph for each measurement
            Timer timerAL; // Set the timer for adjacency list
            MST::kruskalAL(graphAL); // Perform Kruskal's algorithm on the generated graph in adjacency list
            timeAL += timerAL.getTime().count() * unitFactor; // Stop the timer and count the time

            Timer timerIM; // Set the timer for incidence matrix
            MST::kruskalIM(graphIM); // Perform Kruskal's algorithm on the generated graph in incidence matrix
            timeIM += timerIM.getTime().count() * unitFactor; // Stop the timer and count the time
        }
        timesAL.PushBack(timeAL / numberOfMeasurements);
        timesIM.PushBack(timeIM / numberOfMeasurements);
    }

    printResultsTable("Kruskal's Algorithm (Adjacency List)", timesAL, densities);
    printResultsTable("Kruskal's Algorithm (Incidence Matrix)", timesIM, densities);

    deleteGraphAL(graphAL, false); // Delete the graph in adjacency list
    deleteGraphIM(graphIM, false); // Delete the graph in incidence matrix
}
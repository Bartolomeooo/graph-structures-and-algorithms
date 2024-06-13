#include <iostream>
#include <cstdlib>
#include <ctime>
#include "experiments.cpp"

// Graphs declarations
GraphAL graphAL;
GraphIM graphIM;

int askForStartingVertex() {
    if (graphAL.getNumOfVertexes() == 0) {
        return -1;
    }

    int src;
    do {
        std::cout << " Enter starting vertex: ";
        std::cin >> src;
    } while (src < 0 || src >= graphAL.getNumOfVertexes());

    return src;
}

int askForEndingVertex() {
    if (graphAL.getNumOfVertexes() == 0) {
        return -1;
    }

    int dest;
    do {
        std::cout << " Enter ending vertex: ";
        std::cin >> dest;
    } while (dest < 0 || dest >= graphAL.getNumOfVertexes());

    return dest;
}

void testMenu() {
    int choice, direction, src, dest, vertexes;
    std::string filePath;
    float density;
    array<int> path;

    while (true) {
        std::cout << "\n ___________TESTING___________" << std::endl;
        std::cout << " [1] Fill graph from the file" << std::endl;
        std::cout << " [2] Fill graph with random data" << std::endl;
        std::cout << " [3] Print graph" << std::endl;
        std::cout << " [4] Dijkstra's algorithm" << std::endl;
        std::cout << " [5] Bellman-Ford algorithm" << std::endl;
        std::cout << " [6] Prim's algorithm" << std::endl;
        std::cout << " [7] Kruskal's algorithm" << std::endl;
        std::cout << " [8] Delete graph" << std::endl;
        std::cout << " [9] Exit" << std::endl;
        std::cout << " Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                deleteGraphAL(graphAL, false);
                deleteGraphIM(graphIM, false);
                do {
                    std::cout << " Undirected [0] or directed [1] graph? ";
                    std::cin >> direction;
                } while (direction != 0 && direction != 1);
                std::cout << " Path of the file: ";
                std::cin >> filePath;

                graphAL.fillGraphFromFile(filePath, direction);
                graphIM.fillGraphFromFile(filePath, direction);
                break;
            case 2:
                deleteGraphAL(graphAL, false);
                deleteGraphIM(graphIM, false);
                do {
                    std::cout << " Enter number of vertices: ";
                    std::cin >> vertexes;
                } while (vertexes <= 2 || vertexes > 1000);

                do {
                    std::cout << " Enter density [%]: ";
                    std::cin >> density;
                } while (density < 0 || density > 100);

                do {
                    std::cout << " Undirected [0] or directed [1] graph? ";
                    std::cin >> direction;
                } while (direction != 0 && direction != 1);

                generateGraph(graphAL, graphIM, vertexes, density, direction, true);
                break;
            case 3:
                if (graphAL.getNumOfVertexes() == 0) {
                    std::cout << " Graph is empty!" << std::endl;
                    break;
                }
                std::cout << std::endl;
                graphAL.printGraph();
                graphIM.printGraph();
                break;
            case 4:
                src = askForStartingVertex();
                dest = askForEndingVertex();
                if (src == -1 || dest == -1) {
                    std::cout << " Graph is empty!" << std::endl;
                    break;
                }
                path = SP::dijkstraAL(graphAL, src, dest);
                std::cout << std::endl << " Results of the Dijkstra algorithm for adjacency list: " << std::endl;
                std::cout << " Path: ";
                for (int i = 0; i < path.size() - 1; ++i) {
                    std::cout << path[i] << " ";
                }
                std::cout << "\n Total distance: " << path[path.size() - 1] << std::endl;

                path = SP::dijkstraIM(graphIM, src, dest);
                std::cout << std::endl << " Results of the Dijkstra algorithm for incidence matrix: " << std::endl;
                std::cout << " Path: ";
                for (int i = 0; i < path.size() - 1; ++i) {
                    std::cout << path[i] << " ";
                }
                std::cout << "\n Total distance: " << path[path.size() - 1] << std::endl;
                std::cout << std::endl;
                break;
            case 5:
                src = askForStartingVertex();
                dest = askForEndingVertex();
                if (src == -1 || dest == -1) {
                    std::cout << " Graph is empty!" << std::endl;
                    break;
                }
                path = SP::bellmanFordAL(graphAL, src, dest);
                std::cout << std::endl << " Results of the Bellman-Ford algorithm for adjacency list: " << std::endl;
                std::cout << " Path: ";
                for (int i = 0; i < path.size() - 1; ++i) {
                    std::cout << path[i] << " ";
                }
                std::cout << "\n Total distance: " << path[path.size() - 1] << std::endl;

                path = SP::bellmanFordIM(graphIM, src, dest);
                std::cout << std::endl << " Results of the Bellman-Ford algorithm for incidence matrix: " << std::endl;
                std::cout << " Path: ";
                for (int i = 0; i < path.size() - 1; ++i) {
                    std::cout << path[i] << " ";
                }
                std::cout << "\n Total distance: " << path[path.size() - 1] << std::endl;
                std::cout << std::endl;
                break;
            case 6:
                src = askForStartingVertex();
                if (src == -1) {
                    std::cout << " Graph is empty!" << std::endl;
                    break;
                }
                std::cout << std::endl << " MST from Prim's algorithm in adjacency list:" << std::endl;
                MST::primAL(graphAL, src).printGraph();
                std::cout << std::endl << " MST from Prim's algorithm in incidence matrix:" << std::endl;
                MST::primIM(graphIM, src).printGraph();
                break;
            case 7:
                if (graphAL.getNumOfVertexes() == 0) {
                    std::cout << " Graph is empty!" << std::endl;
                    break;
                }
                std::cout << std::endl << " MST from Kruskal's algorithm in adjacency list:" << std::endl;
                MST::kruskalAL(graphAL).printGraph();
                std::cout << std::endl << " MST from Kruskal's algorithm in incidence matrix:" << std::endl;
                MST::kruskalIM(graphIM).printGraph();
                break;
            case 8:
                if (graphAL.getNumOfVertexes() == 0) {
                    std::cout << " Graph is empty!" << std::endl;
                    break;
                }
                deleteGraphAL(graphAL, true);
                deleteGraphIM(graphIM, true);
                break;
            case 9:
                return;
            default:
                std::cout << std::endl << " Wrong choice" << std::endl;
                break;
        }
    }
}

void experimentMenu() {
    int choice;
    while (true) {
        std::cout << "\n ___________EXPERIMENT___________" << std::endl;
        std::cout << " [1] Dijkstra" << std::endl;
        std::cout << " [2] Bellman-Ford" << std::endl;
        std::cout << " [3] Prim" << std::endl;
        std::cout << " [4] Kruskal" << std::endl;
        std::cout << " [5] Exit" << std::endl;
        std::cout << " Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                dijkstraExperiment(graphAL, graphIM);
                break;
            case 2:
                bellmanFordExperiment(graphAL, graphIM);
                break;
            case 3:
                primExperiment(graphAL, graphIM);
                break;
            case 4:
                kruskalExperiment(graphAL, graphIM);
                break;
            case 5:
                return;
            default:
                std::cout << std::endl << " Wrong choice" << std::endl;
                break;
        }
    }
}

void startingMenu() {
    int choice;
    while (true) {
        std::cout << "\n ___________MENU___________" << std::endl;
        std::cout << " [1] Test the algorithms" << std::endl;
        std::cout << " [2] Run the experiment" << std::endl;
        std::cout << " [3] Exit" << std::endl;
        std::cout << " Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                testMenu();
                break;
            case 2:
                experimentMenu();
                break;
            case 3:
                return;
            default:
                std::cout << std::endl << " Wrong choice!" << std::endl;
                break;
        }
    }
}
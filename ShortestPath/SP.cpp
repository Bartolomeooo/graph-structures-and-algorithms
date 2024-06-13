#include "SP.h"
#include <iostream>
#include <climits>
#include <algorithm>
#include "array.cpp"

array<int> SP::bellmanFordAL(GraphAL &graph, int src, int dest) {
    int vertexes = graph.getNumOfVertexes(); // number of vertexes
    if (vertexes == 0) {
        std::cout << " Graph is empty!" << std::endl;
        return array<int>(0);
    }
    int edges = graph.getNumOfEdges(); // number of edges
    array<int> distance(vertexes); // integer array to calculate minimum distance for each vertex
    array<int> previous(vertexes); // integer array of previous vertexes
    bool stop;

    // Set the vertexes with infinity distance and previous vertexes with -1
    for (int i = 0; i < vertexes; i++) {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    distance[src] = 0; // source vertex distance is set to zero

    for (int i = 0; i < vertexes - 1; i++) {
        stop = true;
        for (int j = 0; j < vertexes; j++) {
            for (Node *ver = graph.getList(j); ver; ver = ver->next) {
                // updating the minimum distance for the particular vertex
                if ((distance[j] != INT_MAX) && (distance[ver->vertex] > distance[j] + ver->edge)) {
                    distance[ver->vertex] = distance[j] + ver->edge;
                    previous[ver->vertex] = j;
                    stop = false;
                }
            }
        }
        if (stop) break;
    }

    // Reconstruct the path
    array<int> path(vertexes);
    int pathIndex = 0;
    int current = dest;
    while (current != -1) {
        path[pathIndex++] = current;
        current = previous[current];
    }

    // Reverse the path in-place
    for (int i = 0; i < pathIndex / 2; ++i) {
        std::swap(path[i], path[pathIndex - i - 1]);
    }

    // Resize path array to fit the actual path + total weight
    array<int> result(pathIndex + 1);
    for (int i = 0; i < pathIndex; ++i) {
        result[i] = path[i];
    }
    result[pathIndex] = distance[dest];

    return result;
}

array<int> SP::bellmanFordIM(GraphIM &graph, int src, int dest) {
    int vertexes = graph.getNumOfVertexes(); // number of vertexes
    if (vertexes == 0) {
        std::cout << " Graph is empty!" << std::endl;
        return array<int>(0);
    }
    int edges = graph.getNumOfEdges(); // number of edges
    array<int> distance(vertexes); // integer array to calculate minimum distance for each vertex
    array<int> previous(vertexes); // integer array of previous vertexes
    bool stop;

    // Set the vertexes with infinity distance and previous vertexes with -1
    for (int i = 0; i < vertexes; i++) {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    distance[src] = 0; // source vertex distance is set to zero

    for (int i = 0; i < vertexes - 1; i++) {
        stop = true;
        for (int j = 0; j < edges; j++) {
            int u = graph.getStartingVertexOfEdge(j);
            int v = graph.getEndingVertexOfEdge(j);
            int w = graph.findElement(u, j);
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
                stop = false;
            }
        }
        if (stop) break;
    }

    // Reconstruct the path
    array<int> path(vertexes);
    int pathIndex = 0;
    int current = dest;
    while (current != -1) {
        path[pathIndex++] = current;
        current = previous[current];
    }

    // Reverse the path in-place
    for (int i = 0; i < pathIndex / 2; ++i) {
        std::swap(path[i], path[pathIndex - i - 1]);
    }

    // Resize path array to fit the actual path + total weight
    array<int> result(pathIndex + 1);
    for (int i = 0; i < pathIndex; ++i) {
        result[i] = path[i];
    }
    result[pathIndex] = distance[dest];

    return result;
}

array<int> SP::dijkstraAL(GraphAL &graph, int src, int dest) {
    int vertexes = graph.getNumOfVertexes();
    if (vertexes == 0) {
        std::cout << "Graph is empty!" << std::endl;
        return array<int>(0);
    }
    array<int> distance(vertexes);
    array<bool> visited(vertexes);
    array<int> previous(vertexes);

    // Initialize arrays
    for (int i = 0; i < vertexes; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
        previous[i] = -1;
    }

    distance[src] = 0;

    for (int i = 0; i < vertexes; i++) {
        int min = minimumVertex(distance, visited, vertexes);
        visited[min] = true;

        for (Node *ver = graph.getList(min); ver; ver = ver->next) {
            if (!visited[ver->vertex] && distance[min] != INT_MAX && (distance[ver->vertex] > distance[min] + ver->edge)) {
                distance[ver->vertex] = distance[min] + ver->edge;
                previous[ver->vertex] = min;
            }
        }
    }

    // Reconstruct the path
    array<int> path(vertexes);
    int pathIndex = 0;
    int current = dest;
    while (current != -1) {
        path[pathIndex++] = current;
        current = previous[current];
    }

    // Reverse the path in-place
    for (int i = 0; i < pathIndex / 2; ++i) {
        std::swap(path[i], path[pathIndex - i - 1]);
    }

    // Resize path array to fit the actual path + total weight
    array<int> result(pathIndex + 1);
    for (int i = 0; i < pathIndex; ++i) {
        result[i] = path[i];
    }
    result[pathIndex] = distance[dest];

    return result;
}

array<int> SP::dijkstraIM(GraphIM &graph, int src, int dest) {
    int vertexes = graph.getNumOfVertexes();
    if (vertexes == 0) {
        std::cout << "Graph is empty!" << std::endl;
        return array<int>(0);
    }
    int edges = graph.getNumOfEdges();
    array<int> distance(vertexes);
    array<bool> visited(vertexes);
    array<int> previous(vertexes);

    // Initialize arrays
    for (int i = 0; i < vertexes; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
        previous[i] = -1;
    }

    distance[src] = 0;

    for (int i = 0; i < vertexes; i++) {
        int min = minimumVertex(distance, visited, vertexes);
        visited[min] = true;

        for (int j = 0; j < edges; j++) {
            if (graph.findElement(min, j) > 0 && !visited[graph.getEndingVertexOfEdge(j)] &&
                distance[min] != INT_MAX) {
                int dist = distance[min] + graph.findElement(min, j);
                if (dist < distance[graph.getEndingVertexOfEdge(j)]) {
                    distance[graph.getEndingVertexOfEdge(j)] = dist;
                    previous[graph.getEndingVertexOfEdge(j)] = min;
                }
            }
        }
    }

    // Reconstruct the path
    array<int> path(vertexes);
    int pathIndex = 0;
    int current = dest;
    while (current != -1) {
        path[pathIndex++] = current;
        current = previous[current];
    }

    // Reverse the path in-place
    for (int i = 0; i < pathIndex / 2; ++i) {
        std::swap(path[i], path[pathIndex - i - 1]);
    }

    // Resize path array to fit the actual path + total weight
    array<int> result(pathIndex + 1);
    for (int i = 0; i < pathIndex; ++i) {
        result[i] = path[i];
    }
    result[pathIndex] = distance[dest];

    return result;
}

int SP::minimumVertex(array<int> &dist, array<bool> &visited, int n) {
    int min = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && (min == -1 || dist[i] < dist[min])) {
            min = i;
        }
    }
    return min;
}

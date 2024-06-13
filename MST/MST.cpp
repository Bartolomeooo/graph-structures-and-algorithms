#include "MST.h"
#include <iostream>

GraphAL MST::kruskalAL(GraphAL &graph) {
    int vertexes = graph.getNumOfVertexes(); // Number of vertexes
    if (vertexes == 0) { // If the graph is empty, print that and return
        std::cout << " Graph is empty!" << std::endl;
    }
    int edges = graph.getNumOfEdges(); // Number of edges
    Edge edge;

    UnionFind set(vertexes);
    Queue queue(2 * edges);
    GraphAL mst; // Minimum spanning tree
    mst.addVertexes(vertexes); // Initialize graph with vertices and no edges yet

    for (int i = 0; i < vertexes; i++) {
        set.makeSet(i);
    }

    for (int i = 0; i < vertexes; i++) {
        for (Node *ver = graph.getList(i); ver; ver = ver->next) {
            edge.vertexStart = i;
            edge.vertexEnd = ver->vertex;
            edge.weight = ver->edge;
            queue.push(edge); // Add the edge to the queue
        }
    }

    for (int i = 0; i < vertexes - 1; i++) {
        do {
            edge = queue.front();
            queue.pop();
        } while (set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd));

        mst.addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        set.unionSets(edge); // Union sets connected by the edge
    }

    return mst;
}

GraphIM MST::kruskalIM(GraphIM &graph) {
    int vertexes = graph.getNumOfVertexes(); // Number of vertexes
    if (vertexes == 0) { // If the graph is empty, print that and return
        std::cout << " Graph is empty!" << std::endl;
    }
    int edges = graph.getNumOfEdges(); // Number of edges
    Edge edge;

    UnionFind set(vertexes);
    Queue queue(2 * edges);
    GraphIM mst; // Minimum spanning tree
    mst.addVertexes(vertexes); // Initialize graph with vertices and no edges yet

    for (int i = 0; i < vertexes; i++) {
        set.makeSet(i);
    }

    for (int i = 0; i < vertexes; i++) {
        for (int j = 0; j < edges; j++) {
            if (graph.findElement(i, j) > 0) {
                edge.vertexStart = i;
                edge.vertexEnd = graph.getEndingVertexOfUndirectedEdge(j, i);
                edge.weight = graph.findElement(i, j);
                queue.push(edge); // Add the edge to the queue
            }
        }
    }

    for (int i = 0; i < vertexes - 1; i++) {
        do {
            edge = queue.front();
            queue.pop();
        } while (set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd));

        mst.addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        set.unionSets(edge); // Union sets connected by the edge
    }

    return mst;
}

GraphAL MST::primAL(GraphAL &graph, int src) { // Adjacency list
    int vertexes = graph.getNumOfVertexes(); // Number of vertexes
    if (vertexes == 0) { // If graph is empty, print that and return
        std::cout << " Graph is empty!" << std::endl;
    }
    int edges = graph.getNumOfEdges(); // Number of edges
    array<bool> visited(vertexes); // Boolean array to mark visited/unvisited for each vertex
    GraphAL mst;
    mst.addVertexes(vertexes);

    // Set the vertexes with infinity distance and mark them unvisited
    for (int i = 0; i < vertexes; i++) {
        visited[i] = false;
    }

    visited[src] = true; // Source vertex is set to be visited
    int v = src;
    Edge e;
    Queue q(edges);

    for (int i = 0; i < vertexes - 1; i++) {
        for (Node *ver = graph.getList(v); ver; ver = ver->next) {
            if (!visited[ver->vertex]) {
                e.vertexStart = v;
                e.vertexEnd = ver->vertex;
                e.weight = ver->edge;
                q.push(e); // Add the edge to the queue
            }
        }

        do {
            e = q.front();
            q.pop();
        } while (visited[e.vertexEnd]);

        mst.addUndirectedEdge(e.vertexStart, e.vertexEnd, e.weight);

        visited[e.vertexEnd] = true;
        v = e.vertexEnd;
    }

    return mst;
}

GraphIM MST::primIM(GraphIM &graph, int src) {
    int vertexes = graph.getNumOfVertexes(); // Aumber of vertexes
    if (vertexes == 0) { // If graph is empty, print that and return
        std::cout << " Graph is empty!" << std::endl;
    }
    int edges = graph.getNumOfEdges(); // Number of edges
    array<bool> visited(vertexes); // Boolean array to mark visited/unvisited for each vertex
    GraphIM mst;
    mst.addVertexes(vertexes);

    // Set the vertexes with infinity distance and mark them unvisited
    for (int i = 0; i < vertexes; i++) {
        visited[i] = false;
    }

    visited[src] = true; // Source vertex is set to be visited
    int v = src;
    Edge e;
    Queue q(edges);

    for (int i = 0; i < vertexes - 1; i++) {
        for (int j = 0; j < edges; j++) {
            if (graph.findElement(v, j) > 0 && !visited[graph.getEndingVertexOfUndirectedEdge(j, v)]) {
                e.vertexStart = v;
                e.vertexEnd = graph.getEndingVertexOfUndirectedEdge(j, v);
                e.weight = graph.findElement(v, j);
                q.push(e); // Add the edge to the queue
            }
        }

        do {
            e = q.front();
            q.pop();
        } while (visited[e.vertexEnd]);

        mst.addUndirectedEdge(e.vertexStart, e.vertexEnd, e.weight);

        visited[e.vertexEnd] = true;
        v = e.vertexEnd;
    }

    return mst;
}

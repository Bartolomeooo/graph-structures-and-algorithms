#ifndef QUEUE_H
#define QUEUE_H

#include "array.h"

struct Edge {
    int vertexStart;
    int vertexEnd;
    int weight;

    Edge(int start = 0, int end = 0, int w = 0) : vertexStart(start), vertexEnd(end), weight(w) {}
};

class Queue {
public:
    Queue(int edges);
    ~Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);

    Edge front() const;
    void push(const Edge& edge);
    void pop();
    bool empty() const { return heapPosition == 0; }

private:
    array<Edge> heap;
    int heapPosition;

    void heapifyUp(int index);
    void heapifyDown(int index);
};

#endif

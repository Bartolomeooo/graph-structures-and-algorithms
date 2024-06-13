#include "queue.h"
#include <stdexcept>
#include "array.cpp"

Queue::Queue(int edges) : heap(edges), heapPosition(0) {}

Queue::~Queue() {}

Queue::Queue(const Queue& other) : heap(other.heap), heapPosition(other.heapPosition) {}

Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        heap = other.heap;
        heapPosition = other.heapPosition;
    }
    return *this;
}

Edge Queue::front() const {
    if (heapPosition == 0) {
        throw std::out_of_range("Queue is empty");
    }
    return heap[0];
}

void Queue::push(const Edge& edge) {
    if (heapPosition == heap.size()) {
        heap.resize(heap.size() * 2);
    }
    heap[heapPosition] = edge;
    heapifyUp(heapPosition);
    heapPosition++;
}

void Queue::pop() {
    if (heapPosition == 0) {
        return;
    }
    heapPosition--;
    heap[0] = heap[heapPosition];
    heapifyDown(0);
}

void Queue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].weight >= heap[parent].weight) {
            break;
        }
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

void Queue::heapifyDown(int index) {
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heapPosition && heap[leftChild].weight < heap[smallest].weight) {
        smallest = leftChild;
    }

    if (rightChild < heapPosition && heap[rightChild].weight < heap[smallest].weight) {
        smallest = rightChild;
    }

    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

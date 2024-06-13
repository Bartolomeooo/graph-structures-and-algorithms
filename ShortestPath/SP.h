#ifndef SP_H
#define SP_H

#include "GraphAL.h"
#include "GraphIM.h"
#include "array.h"

class SP {
public:
    static array<int> bellmanFordAL(GraphAL &graph, int src, int dest);
    static array<int> bellmanFordIM(GraphIM &graph, int src, int dest);

    static array<int> dijkstraAL(GraphAL &graph, int src, int dest);
    static array<int> dijkstraIM(GraphIM &graph, int src, int dest);
private:
    static int minimumVertex(array<int> &dist, array<bool> &visited, int n);
};

#endif // SP_H

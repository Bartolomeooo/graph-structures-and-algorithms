#ifndef MST_H
#define MST_H

#include "GraphAL.h"
#include "GraphIM.h"
#include "unionFind.h"
#include "queue.h"
#include "array.h"

class MST {
public:
    static GraphAL kruskalAL(GraphAL &graph);
    static GraphIM kruskalIM(GraphIM &graph);
    static GraphAL primAL(GraphAL &graph, int src);
    static GraphIM primIM(GraphIM &graph, int src);
};

#endif // MST_H
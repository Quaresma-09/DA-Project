#ifndef DAPROJ1_MAXFLOW_H
#define DAPROJ1_MAXFLOW_H

#include "../include/graph/Graph.h"
#include <vector>

class MaxFlow {
    bool bfs(Graph& graph, int source, int sink,
             std::vector<int>& parent,
             std::vector<int>& parentEdge);

public:
    int edmondsKarp(Graph& graph, int source, int sink);
};

#endif
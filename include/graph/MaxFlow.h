#ifndef DAPROJ1_MAXFLOW_H
#define DAPROJ1_MAXFLOW_H

#include "graph/Graph.h"
#include <vector>

/**
 * @brief Implements the Edmonds-Karp algorithm for maximum flow.
 *
 * Uses BFS to find augmenting paths in the residual graph and
 * updates the flow until no more augmenting paths exist.
 */
class MaxFlow {

    /**
     * @brief Finds an augmenting path using BFS.
     *
     * @complexity O(V + E)
     */
    bool bfs(Graph& graph, int source, int sink,
             std::vector<int>& parent,
             std::vector<int>& parentEdge);

public:

    /**
     * @brief Computes the maximum flow from source to sink.
     *
     * @complexity O(V * E^2)
     */
    int edmondsKarp(Graph& graph, int source, int sink);
};

#endif
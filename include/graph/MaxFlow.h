/**
 * @file MaxFlow.h
 * @brief Header file for the MaxFlow class.
 *
 * Declares the Edmonds-Karp algorithm for computing the maximum flow
 * in a directed flow network.
 */

#ifndef DAPROJ1_MAXFLOW_H
#define DAPROJ1_MAXFLOW_H

#include "graph/Graph.h"
#include <vector>

/**
 * @class MaxFlow
 * @brief Implements the Edmonds-Karp algorithm for maximum flow.
 *
 * Uses BFS to find augmenting paths in the residual graph and
 * updates the flow until no more augmenting paths exist.
 * This is a BFS-based variant of the Ford-Fulkerson method.
 */
class MaxFlow {

    /**
     * @brief Finds an augmenting path from source to sink using BFS.
     *
     * Traverses the residual graph looking for a path with available
     * capacity. Populates parent and parentEdge vectors for path
     * reconstruction.
     *
     * @param graph The flow network (residual graph).
     * @param source The source node index.
     * @param sink The sink node index.
     * @param parent Output vector: parent[v] = predecessor of v in the BFS tree.
     * @param parentEdge Output vector: parentEdge[v] = index of the edge used to reach v.
     * @return true if an augmenting path was found, false otherwise.
     *
     * @complexity O(V + E)
     */
    bool bfs(Graph& graph, int source, int sink,
             std::vector<int>& parent,
             std::vector<int>& parentEdge);

public:

    /**
     * @brief Computes the maximum flow from source to sink using Edmonds-Karp.
     *
     * Repeatedly finds augmenting paths via BFS and pushes the maximum
     * possible flow along each path until no more paths exist.
     *
     * @param graph The flow network to compute max flow on.
     * @param source The source node index.
     * @param sink The sink node index.
     * @return The value of the maximum flow.
     *
     * @complexity O(V * E^2)
     */
    int edmondsKarp(Graph& graph, int source, int sink);
};

#endif
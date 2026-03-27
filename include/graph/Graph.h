/**
 * @file Graph.h
 * @brief Header file for the Graph class and Edge struct.
 *
 * Defines the directed graph structure used to represent the flow
 * network for the Edmonds-Karp maximum flow algorithm.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

/**
 * @struct Edge
 * @brief Represents a directed edge in the flow network.
 *
 * Each edge stores its destination node, capacity, current flow,
 * and the index of the corresponding reverse edge in the adjacency
 * list of the destination node (needed for the residual graph).
 */
struct Edge {
    int to;         ///< Destination node of this edge.
    int capacity;   ///< Maximum capacity of this edge.
    int flow;       ///< Current flow through this edge.
    int rev;        ///< Index of the reverse edge in adj[to].

    /**
     * @brief Constructs an Edge.
     * @param to Destination node.
     * @param capacity Maximum capacity.
     * @param flow Initial flow (usually 0).
     * @param rev Index of the reverse edge in the destination's adjacency list.
     */
    Edge(int to, int capacity, int flow, int rev);
};

/**
 * @class Graph
 * @brief Directed graph implemented with adjacency lists.
 *
 * This structure is used to represent the flow network required
 * for maximum flow algorithms (e.g., Edmonds-Karp). Each edge
 * is stored alongside its reverse edge to support residual graph
 * operations.
 */
class Graph {
private:
    std::vector<std::vector<Edge>> adj;  ///< Adjacency list representation.

public:
    /**
     * @brief Default constructor. Creates an empty graph.
     */
    Graph();

    /**
     * @brief Constructs a graph with a given number of vertices.
     * @param numVertices The number of vertices in the graph.
     */
    explicit Graph(int numVertices);

    /**
     * @brief Adds a directed edge and its corresponding reverse edge.
     *
     * The reverse edge (with capacity 0) is required to build the
     * residual graph used by the Edmonds-Karp algorithm.
     *
     * @param from Source node of the edge.
     * @param to Destination node of the edge.
     * @param capacity Maximum capacity of the edge.
     *
     * @complexity O(1)
     */
    void addEdge(int from, int to, int capacity);

    /**
     * @brief Returns a mutable reference to the adjacency list.
     * @return Reference to the adjacency list.
     *
     * @complexity O(1)
     */
    std::vector<std::vector<Edge>>& getAdj();

    /**
     * @brief Returns a const reference to the adjacency list.
     * @return Const reference to the adjacency list.
     *
     * @complexity O(1)
     */
    const std::vector<std::vector<Edge>>& getAdj() const;

    /**
     * @brief Returns the number of vertices in the graph.
     * @return Number of vertices (size of the adjacency list).
     *
     * @complexity O(1)
     */
    int size() const;
};

#endif
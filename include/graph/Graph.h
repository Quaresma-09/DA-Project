#ifndef DA_PROJECT_GRAPH_H
#define DA_PROJECT_GRAPH_H

#include <vector>

/**
 * @brief Represents an edge in the flow network.
 *
 * Stores destination node, capacity, current flow and the index
 * of the corresponding reverse edge in the adjacency list.
 */
struct Edge {
    int to;
    int capacity;
    int flow;
    int rev;

    Edge(int to, int capacity, int flow, int rev);
};

/**
 * @brief Directed graph implemented with adjacency lists.
 *
 * This structure is used to represent the flow network required
 * for maximum flow algorithms (e.g., Edmonds-Karp).
 */
class Graph {
private:
    std::vector<std::vector<Edge>> adj;

public:
    Graph();
    explicit Graph(int numVertices);

    /**
     * @brief Adds a forward edge and its corresponding reverse edge.
     *
     * The reverse edge is required to build the residual graph.
     *
     * @complexity O(1)
     */
    void addEdge(int from, int to, int capacity);

    /**
     * @brief Returns the adjacency list of the graph.
     *
     * @complexity O(1)
     */
    std::vector<std::vector<Edge>>& getAdj();
    const std::vector<std::vector<Edge>>& getAdj() const;

    /**
     * @brief Returns the number of vertices in the graph.
     *
     * @complexity O(1)
     */
    int size() const;
};

#endif
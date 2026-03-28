/**
 * @file Graph.cpp
 * @brief Implementation of the Graph class and Edge struct.
 */

#include "graph/Graph.h"

Edge::Edge(int to, int capacity, int flow, int rev)
    : to(to), capacity(capacity), flow(flow), rev(rev) {}

Graph::Graph() = default;

Graph::Graph(int numVertices) : adj(numVertices) {}

void Graph::addEdge(int from, int to, int capacity) {
    int fromRev = static_cast<int>(adj[to].size());
    int toRev = static_cast<int>(adj[from].size());

    adj[from].emplace_back(to, capacity, 0, fromRev);
    adj[to].emplace_back(from, 0, 0, toRev);
}

std::vector<std::vector<Edge>>& Graph::getAdj() {
    return adj;
}

const std::vector<std::vector<Edge>>& Graph::getAdj() const {
    return adj;
}

int Graph::size() const {
    return static_cast<int>(adj.size());
}
/**
 * @file MaxFlow.cpp
 * @brief Implementation of the Edmonds-Karp maximum flow algorithm.
 */

#include "graph/MaxFlow.h"

#include <algorithm>
#include <limits>
#include <queue>

bool MaxFlow::bfs(Graph& graph, int source, int sink,
                  std::vector<int>& parent,
                  std::vector<int>& parentEdge) {
    int n = graph.size();

    parent.assign(n, -1);
    parentEdge.assign(n, -1);

    std::queue<int> q;
    q.push(source);
    parent[source] = source;

    std::vector<std::vector<Edge>>& adj = graph.getAdj();

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < static_cast<int>(adj[current].size()); i++) {
            Edge& edge = adj[current][i];
            int residualCapacity = edge.capacity - edge.flow;

            // Only visit unvisited nodes with available residual capacity
            if (parent[edge.to] == -1 && residualCapacity > 0) {
                parent[edge.to] = current;
                parentEdge[edge.to] = i;

                if (edge.to == sink) {
                    return true;
                }

                q.push(edge.to);
            }
        }
    }

    return false;
}

int MaxFlow::edmondsKarp(Graph& graph, int source, int sink) {
    int maxFlow = 0;

    std::vector<int> parent;
    std::vector<int> parentEdge;

    std::vector<std::vector<Edge>>& adj = graph.getAdj();

    // Find augmenting paths until none exist
    while (bfs(graph, source, sink, parent, parentEdge)) {

        // Find the bottleneck (minimum residual capacity along the path)
        int pathFlow = std::numeric_limits<int>::max();

        int current = sink;
        while (current != source) {
            int previous = parent[current];
            int edgeIndex = parentEdge[current];

            Edge& edge = adj[previous][edgeIndex];
            int residualCapacity = edge.capacity - edge.flow;

            pathFlow = std::min(pathFlow, residualCapacity);
            current = previous;
        }

        // Update flow along the path and reverse edges
        current = sink;
        while (current != source) {
            int previous = parent[current];
            int edgeIndex = parentEdge[current];

            Edge& edge = adj[previous][edgeIndex];
            Edge& reverseEdge = adj[current][edge.rev];

            edge.flow += pathFlow;
            reverseEdge.flow -= pathFlow;

            current = previous;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}
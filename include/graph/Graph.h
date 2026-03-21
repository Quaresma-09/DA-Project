#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
    int to;         //destination vertex
    int capacity;   //edge capacity
    int flow;       //current flow
    int rev;        //index of the reverse edge

    Edge(int to, int capacity, int flow, int rev);
};

class Graph {
private:
    std::vector<std::vector<Edge>> adj;  //adjacency list

public:
    Graph();
    explicit Graph(int numVertices);

    void addEdge(int from, int to, int capacity);

    std::vector<std::vector<Edge>>& getAdj();
    const std::vector<std::vector<Edge>>& getAdj() const;

    int size() const;
};

#endif
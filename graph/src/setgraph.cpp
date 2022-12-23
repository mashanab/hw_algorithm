#include "setgraph.h"

SetGraph::SetGraph(const int &vertices_count)
: graph(vertices_count, std::set<int>()) {}

SetGraph::SetGraph(const IGraph &igraph)
: SetGraph(igraph.get_vertices_count()) {
    for (int vertice = 0; vertice < graph.size(); ++vertice) {
        std::vector<int> row = igraph.get_next_vertices(vertice);
        for (int other_vertice : row) {
            graph[vertice].insert(other_vertice);
        }
    }
}

void SetGraph::add_edge(const int &from, const int &to) {
    graph[from].insert(to);
}

int SetGraph::get_vertices_count() const {
    return graph.size();
}

std::vector<int> SetGraph::get_next_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int child = 0; child < graph.size(); ++child) {
        if (graph[vertex].find(child) != graph[vertex].end()) {
            result.push_back(child);
        }
    }
    return result;
}

std::vector<int> SetGraph::get_prev_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int child = 0; child < graph.size(); ++child) {
        if (graph[child].find(vertex) != graph[child].end()) {
            result.push_back(child);
        }
    }
    return result;
}

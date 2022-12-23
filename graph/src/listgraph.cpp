#include "listgraph.h"


ListGraph::ListGraph(const int &vertices_count)
: graph(vertices_count, std::vector<int>()) {}

ListGraph::ListGraph(const IGraph &igraph)
: ListGraph(igraph.get_vertices_count()) {
    for (int vertice = 0; vertice < graph.size(); ++vertice) {
        graph[vertice] = igraph.get_next_vertices(vertice);
    }
}

void ListGraph::add_edge(const int &from, const int &to) {
    graph[from].push_back(to);
}

int ListGraph::get_vertices_count() const {
    return graph.size();
}

std::vector<int> ListGraph::get_next_vertices(const int &vertex) const {
    std::vector<int> result(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}

std::vector<int> ListGraph::get_prev_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        for (const auto &child : graph[i]) {
            if (vertex == child) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}
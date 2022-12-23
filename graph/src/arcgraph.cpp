#include "arcgraph.h"

ArcGraph::ArcGraph(const int &vertices_count)
: vertices_count(vertices_count) {}

ArcGraph::ArcGraph(const IGraph &igraph)
: ArcGraph(igraph.get_vertices_count()) {
    for (int vertice = 0; vertice < vertices_count; ++vertice) {
        std::vector<int> related_nodes = igraph.get_next_vertices(vertice);
        for (int other_node : related_nodes) {
            graph.emplace_back(vertice, other_node);
        }
    }
}

void ArcGraph::add_edge(const int &from, const int &to) {
    graph.emplace_back(from, to);
}

int ArcGraph::get_vertices_count() const {
    return vertices_count;
}

std::vector<int> ArcGraph::get_next_vertices(const int &vertex) const {
    std::vector<int> result;
    for (const auto &linkage : graph) {
        if (linkage.first == vertex) {
            result.push_back(linkage.second);
        }
    }
    return result;
}

std::vector<int> ArcGraph::get_prev_vertices(const int &vertex) const {
    std::vector<int> result;
    for (const auto &linkage : graph) {
        if (linkage.second == vertex) {
            result.push_back(linkage.first);
        }
    }
    return result;
}
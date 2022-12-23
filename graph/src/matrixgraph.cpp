#include "matrixgraph.h"

MatrixGraph::MatrixGraph(const int &vertices_count)
: graph(vertices_count, std::vector<int>(vertices_count, 0)) {}

MatrixGraph::MatrixGraph(const IGraph &igraph)
: MatrixGraph(igraph.get_vertices_count()) {
    for (int vertice = 0; vertice < graph.size(); ++vertice) {
        std::vector<int> row = igraph.get_next_vertices(vertice);
        for (const int &other_vertice : row) {
            graph[vertice][other_vertice] = 1;
        }
    }
}

void MatrixGraph::add_edge(const int &from, const int &to) {
    graph[from][to] = 1;
}

int MatrixGraph::get_vertices_count() const {
    return graph.size();
}

std::vector<int> MatrixGraph::get_next_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int child = 0; child < graph.size(); ++child) {
        if (graph[vertex][child] == 1) {
            result.push_back(child);
        }
    }
    return result;
}

std::vector<int> MatrixGraph::get_prev_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int child = 0; child < graph.size(); ++child) {
        if (graph[child][vertex] == 1) {
            result.push_back(child);
        }
    }
    return result;
}

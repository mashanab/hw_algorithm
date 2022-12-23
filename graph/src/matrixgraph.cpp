#include "matrixgraph.h"

MatrixGraph::MatrixGraph(size_t verticesCount)
        : graph_(verticesCount, std::vector<int>(verticesCount, 0)) {}

MatrixGraph::MatrixGraph(const IGraph &graph)
        : MatrixGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph_.size(); ++i) {
        std::vector<int> row = graph.GetNextVertices(i);
        for (int j : row) {
            graph_[i][j] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    graph_[from][to] = 1;
}

size_t MatrixGraph::VerticesCount() const {
    return graph_.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        if (graph_[vertex][i] == 1) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        if (graph_[i][vertex] == 1) {
            result.push_back(i);
        }
    }
    return result;
}
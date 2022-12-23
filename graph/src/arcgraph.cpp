#include "arcgraph.h"

ArcGraph::ArcGraph(size_t verticesCount)
    : verticesCount_(verticesCount) {}

ArcGraph::ArcGraph(const IGraph &graph)
    : ArcGraph(graph.VerticesCount()) {
    for (int i = 0; i < verticesCount_; ++i) {
        std::vector<int> row = graph.GetNextVertices(i);
        for (int j : row) {
            graph_.emplace_back(i, j);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    graph_.emplace_back(from, to);
}

size_t ArcGraph::VerticesCount() const {
    return verticesCount_;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (const auto & i : graph_) {
        if (i.first == vertex) {
            result.push_back(i.second);
        }
    }
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (const auto & i : graph_) {
        if (i.second == vertex) {
            result.push_back(i.first);
        }
    }
    return result;
}
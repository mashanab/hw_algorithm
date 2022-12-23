#include "setgraph.h"

SetGraph::SetGraph(size_t verticesCount)
        : graph_(verticesCount, std::set<int>()) {}

SetGraph::SetGraph(const IGraph &graph)
        : SetGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph_.size(); ++i) {
        std::vector<int> row = graph.GetNextVertices(i);
        for (int j : row) {
            graph_[i].insert(j);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    graph_[from].insert(to);
}

size_t SetGraph::VerticesCount() const {
    return graph_.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        if (graph_[vertex].find(i) != graph_[vertex].end()) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        if (graph_[i].find(vertex) != graph_[i].end()) {
            result.push_back(i);
        }
    }
    return result;
}
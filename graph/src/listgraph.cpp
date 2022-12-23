#include "listgraph.h"


ListGraph::ListGraph(size_t verticesCount)
    : graph_(verticesCount, std::vector<int>()) {}

ListGraph::ListGraph(const IGraph &graph)
    : ListGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph_.size(); ++i) {
        graph_[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    graph_[from].push_back(to);
}

size_t ListGraph::VerticesCount() const {
    return graph_.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result(graph_[vertex].size());
    std::copy(graph_[vertex].begin(), graph_[vertex].end(), result.begin());
    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        for (auto child : graph_[i]) {
            if (vertex == child) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}
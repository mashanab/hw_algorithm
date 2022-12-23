#ifndef LISTGRAPH
#define LISTGRAPH

#include "igraph.h"


class ListGraph : public IGraph {
public:
    explicit ListGraph(size_t verticesCount);
    ~ListGraph() override = default;

    explicit ListGraph(const IGraph&);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> graph_;
};


#endif  // LISTGRAPH
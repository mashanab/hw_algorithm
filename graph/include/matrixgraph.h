#ifndef MATRIXGRAPH
#define MATRIXGRAPH

#include "igraph.h"


class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(size_t verticesCount);
    ~MatrixGraph() override = default;

    explicit MatrixGraph(const IGraph&);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> graph_;
};


#endif //  MATRIXGRAPH
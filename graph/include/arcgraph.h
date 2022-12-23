#ifndef ARCGRAPH
#define ARCGRAPH

#include "igraph.h"


class ArcGraph : public IGraph {
public:
    explicit ArcGraph(size_t verticesCount);
    ~ArcGraph() override = default;

    explicit ArcGraph(const IGraph&);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> graph_;
    size_t verticesCount_;
};


#endif //  ARCGRAPH
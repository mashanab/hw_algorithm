#ifndef SETGRAPH
#define SETGRAPH

#include "igraph.h"

#include <set>


class SetGraph : public IGraph {
public:
    explicit SetGraph(size_t verticesCount);
    ~SetGraph() override = default;

    explicit SetGraph(const IGraph&);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::set<int>> graph_;
};


#endif //  SETGRAPH
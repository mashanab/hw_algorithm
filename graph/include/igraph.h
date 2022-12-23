#ifndef IGRAPH
#define IGRAPH

#include <vector>
#include <stddef.h>


struct IGraph {
    virtual ~IGraph() = default;

    virtual void AddEdge(int from, int to) = 0;

    virtual size_t VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


#endif //  IGRAPH
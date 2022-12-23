#pragma once

#include "igraph.h"

class MatrixGraph : public IGraph {
 public:
    explicit MatrixGraph(const int &vertices_count);
    explicit MatrixGraph(const IGraph &);
    ~MatrixGraph() override=default;

    void add_edge(const int &from, const int &to) override;

    int get_vertices_count() const override;

    std::vector<int> get_next_vertices(const int &vertex) const override;
    std::vector<int> get_prev_vertices(const int &vertex) const override;

 private:
    std::vector< std::vector<int> > graph;
};

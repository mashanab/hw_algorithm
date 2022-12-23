#pragma once

#include "igraph.h"


class ArcGraph : public IGraph {
 public:
    explicit ArcGraph(const int &vertices_count);
    explicit ArcGraph(const IGraph &);
    ~ArcGraph() override=default;

    void add_edge(const int &from, const int &to) override;

    int get_vertices_count() const override;

    std::vector<int> get_next_vertices(const int &vertex) const override;
    std::vector<int> get_prev_vertices(const int &vertex) const override;

 private:
    std::vector< std::pair<int, int> > graph;
    int vertices_count;
};

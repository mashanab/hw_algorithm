#pragma once

#include <set>

#include "igraph.h"

class SetGraph : public IGraph {
 public:
    explicit SetGraph(const int &vertices_count);
    explicit SetGraph(const IGraph &);
    ~SetGraph() override=default;

    void add_edge(const int &from, const int &to) override;

    int get_vertices_count() const override;

    std::vector<int> get_next_vertices(const int &vertex) const override;
    std::vector<int> get_prev_vertices(const int &vertex) const override;

 private:
    std::vector< std::set<int> > graph;
};

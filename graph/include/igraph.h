#pragma once

#include <vector>
#include <stddef.h>


struct IGraph {
    virtual ~IGraph()=default;

    virtual void add_edge(const int &from, const int &to)=0;

    virtual int get_vertices_count() const=0;

    virtual std::vector<int> get_next_vertices(const int &vertex) const=0;
    virtual std::vector<int> get_prev_vertices(const int &vertex) const=0;
};

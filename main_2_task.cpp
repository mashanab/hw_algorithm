#include <vector>
#include <iostream>
#include <set>
#include <climits>
#include <queue>

struct IGraph {
    virtual ~IGraph()=default;

    virtual void add_edge(const int &from, const int &to)=0;

    virtual int get_vertices_count() const=0;

    virtual std::vector<int> get_next_vertices(const int &vertex) const=0;
    virtual std::vector<int> get_prev_vertices(const int &vertex) const=0;
};


class ListGraph : public IGraph {
 public:
    explicit ListGraph(int vertices_count);
    ~ListGraph() override=default;

    explicit ListGraph(const IGraph &);

    void add_edge(const int &from, const int &to) override;

    int get_vertices_count() const override;

    std::vector<int> get_next_vertices(const int &vertex) const override;
    std::vector<int> get_prev_vertices(const int &vertex) const override;

 private:
    std::vector<std::vector<int>> graph;
};

class MatrixGraph : public IGraph {
 public:
    explicit MatrixGraph(int vertices_count);
    ~MatrixGraph() override=default;

    explicit MatrixGraph(const IGraph &);

    void add_edge(const int &from, const int &to) override;

    int get_vertices_count() const override;

    std::vector<int> get_next_vertices(const int &vertex) const override;
    std::vector<int> get_prev_vertices(const int &vertex) const override;

 private:
    std::vector<std::vector<int>> graph;
};

class ArcGraph : public IGraph {
 public:
    explicit ArcGraph(int vertices_count);
    ~ArcGraph() override=default;

    explicit ArcGraph(const IGraph &);

    void add_edge(const int &from, const int &to) override;

    int get_vertices_count() const override;

    std::vector<int> get_next_vertices(const int &vertex) const override;
    std::vector<int> get_prev_vertices(const int &vertex) const override;

private:
    std::vector< std::pair<int, int> > graph;
    int vertices_count;
};

class SetGraph : public IGraph {
public:
    explicit SetGraph(int vertices_count);
    ~SetGraph() override=default;

    explicit SetGraph(const IGraph&);

    void add_edge(const int &from, const int &to) override;

    int get_vertices_count() const override;

    std::vector<int> get_next_vertices(const int &vertex) const override;
    std::vector<int> get_prev_vertices(const int &vertex) const override;

private:
    std::vector<std::set<int>> graph;
};



ListGraph::ListGraph(int vertices_count)
: graph(vertices_count, std::vector<int>()) {}

ListGraph::ListGraph(const IGraph &igraph)
: ListGraph(igraph.get_vertices_count()) {
    for (int i = 0; i < graph.size(); ++i) {
        graph[i] = igraph.get_next_vertices(i);
    }
}

int ListGraph::get_vertices_count() const {
    return graph.size();
}

void ListGraph::add_edge(const int &from, const int &to) {
    graph[from].push_back(to);
}

std::vector<int> ListGraph::get_prev_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        for (auto child : graph[i]) {
            if (vertex == child) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}

std::vector<int> ListGraph::get_next_vertices(const int &vertex) const {
    std::vector<int> result(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}



MatrixGraph::MatrixGraph(int vertices_count)
: graph(vertices_count, std::vector<int>(vertices_count, 0)) {}

MatrixGraph::MatrixGraph(const IGraph &igraph)
: MatrixGraph(igraph.get_vertices_count()) {
    for (int i = 0; i < graph.size(); ++i) {
        std::vector<int> row = igraph.get_next_vertices(i);
        for (const int &j : row) {
            graph[i][j] = 1;
        }
    }
}

int MatrixGraph::get_vertices_count() const {
    return graph.size();
}

void MatrixGraph::add_edge(const int &from, const int &to) {
    graph[from][to] = 1;
}

std::vector<int> MatrixGraph::get_prev_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i][vertex] == 1) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> MatrixGraph::get_next_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[vertex][i] == 1) {
            result.push_back(i);
        }
    }
    return result;
}



ArcGraph::ArcGraph(int vertices_count)
: vertices_count(vertices_count) {}

ArcGraph::ArcGraph(const IGraph &igraph)
: ArcGraph(igraph.get_vertices_count()) {
    for (int i = 0; i < vertices_count; ++i) {
        std::vector<int> row = igraph.get_next_vertices(i);
        for (const int &j : row) {
            graph.emplace_back(i, j);
        }
    }
}

int ArcGraph::get_vertices_count() const {
    return vertices_count;
}

void ArcGraph::add_edge(const int &from, const int &to) {
    graph.emplace_back(from, to);
}

std::vector<int> ArcGraph::get_prev_vertices(const int &vertex) const {
    std::vector<int> result;
    for (const auto &i : graph) {
        if (i.second == vertex) {
            result.push_back(i.first);
        }
    }
    return result;
}

std::vector<int> ArcGraph::get_next_vertices(const int &vertex) const {
    std::vector<int> result;
    for (const auto &i : graph) {
        if (i.first == vertex) {
            result.push_back(i.second);
        }
    }
    return result;
}



SetGraph::SetGraph(int vertices_count)
: graph(vertices_count, std::set<int>()) {}

SetGraph::SetGraph(const IGraph &igraph)
: SetGraph(igraph.get_vertices_count()) {
    for (int i = 0; i < graph.size(); ++i) {
        std::vector<int> row = igraph.get_next_vertices(i);
        for (int j : row) {
            graph[i].insert(j);
        }
    }
}

int SetGraph::get_vertices_count() const {
    return graph.size();
}

void SetGraph::add_edge(const int &from, const int &to) {
    graph[from].insert(to);
}

std::vector<int> SetGraph::get_prev_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i].find(vertex) != graph[i].end()) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> SetGraph::get_next_vertices(const int &vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[vertex].find(i) != graph[vertex].end()) {
            result.push_back(i);
        }
    }
    return result;
}



int number_of_shortest_paths(const int from, const int to, const IGraph &graph) {
    const int N = graph.get_vertices_count();
    std::vector<int> distance(N, INT_MAX);
    distance[from] = 0;

    std::vector<int> counter(N, 0);
    counter[from] = 1;

    std::queue<int> queue;
    queue.push(from);
    while (!queue.empty()) {
        int curr = queue.front();
        queue.pop();

        for (const auto &next: graph.get_next_vertices(curr)) {
            if (distance[curr] < distance[next] - 1) {
                distance[next] = distance[curr] + 1;
                counter[next] = counter[curr];
                queue.push(next);
            } else if (distance[curr] == distance[next] - 1) {
                counter[next] += counter[curr];
            }
        }
    }
    return counter[to];
}

template<typename T>
void run(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int count_vertex = 0;
    int count_edge = 0;
    in >> count_vertex;
    in >> count_edge;

    T graph(count_vertex);

    int from = 0;
    int to = 0;
    for (int i = 0; i < count_edge; ++i) {
        in >> from;
        in >> to;

        graph.add_edge(from, to);
        graph.add_edge(to, from);
    }

    int start = 0;
    int end = 0;
    in >> start;
    in >> end;

    out << number_of_shortest_paths(start, end, graph) << std::endl;
}

int main() {
    run<ListGraph>();
    return 0;
}

#include <iostream>
#include <algorithm>
#include <cassert>
#include <set>
#include <vector>
#include <climits>

class ListGraph {
    struct Node {
        Node(const int &id, const int &weight);
        bool operator<(const Node &r) const;

        int id;
        int weight;
    };
 public:
    explicit ListGraph(const int &size);
    virtual ~ListGraph()=default;

    void add_edge(const int &from, const int &to, const int &weight);
    int vertices_count() const;
    std::vector<Node> get_next_vertices(const int &vertex) const;

    int amount_of_shortest_path(const int &from, const int &to);

 private:
    std::vector< std::vector<Node> > matrix_graph;
    int vertices_amount = 0;
};

ListGraph::Node::Node(const int &id, const int &weight) : id(id), weight(weight) {}

bool ListGraph::Node::operator<(const ListGraph::Node &r) const {
    return ( weight == r.weight ? id < r.id : weight < r.weight );
}

ListGraph::ListGraph(const int &size) : vertices_amount(size), matrix_graph(size) {}

std::vector<ListGraph::Node> ListGraph::get_next_vertices(const int &vertex) const {
    return matrix_graph[vertex];
}

int ListGraph::vertices_count() const {
    return vertices_amount;
}

int ListGraph::amount_of_shortest_path(const int &from, const int &to) {
    std::vector<int> distance(vertices_amount, INT_MAX);
    distance[from] = 0;

    std::set<Node> queue;
    queue.emplace(from, 0);
    while (!queue.empty()) {
        auto current = queue.begin()->id; queue.erase(queue.begin());
        for (const auto &neighbour : get_next_vertices(current)) {
            if (distance[neighbour.id] == INT_MAX) {
                distance[neighbour.id] = distance[current] + neighbour.weight;

                queue.emplace(neighbour.id, distance[neighbour.id]);
            } else if (distance[neighbour.id] > distance[current] + neighbour.weight) {
                queue.erase(Node(neighbour.id, distance[neighbour.id]));

                distance[neighbour.id] = distance[current] + neighbour.weight;

                queue.emplace(neighbour.id, distance[neighbour.id]);
            }
        }
    }
    return distance[to];
}

void ListGraph::add_edge(const int &from, const int &to, const int &weight) {
    matrix_graph[from].push_back(Node(to, weight));
    matrix_graph[to].push_back(Node(from, weight));
}

void processing(std::istream &in = std::cin, std::ostream &out = std::cout) {
    int cities = 0;
    int roads = 0;
    in >> cities;
    in >> roads;

    ListGraph graph(cities);
    int from = 0;
    int to = 0;
    int weight = 0;
    for (int iterator = 0; iterator < roads; ++iterator) {
        in >> from;
        in >> to;
        in >> weight;
        graph.add_edge(from, to, weight);
    }

    in >> from;
    in >> to;
    out << graph.amount_of_shortest_path(from, to) << std::endl;
}

int main() {
    processing();
    return 0;
}

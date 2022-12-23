#include <vector>
#include <iostream>
#include <climits>
#include <queue>
#include <sstream>

#include "arcgraph.h"
#include "listgraph.h"
#include "matrixgraph.h"
#include "setgraph.h"

int number_of_shortest_paths(const int &from, const int &to, const IGraph &igraph) {
    std::vector<int> distance(igraph.get_vertices_count(), INT_MAX);
    distance[from] = 0;

    std::vector<int> counter(igraph.get_vertices_count(), 0);
    counter[from] = 1;

    std::queue<int> queue;
    queue.push(from);
    while (!queue.empty()) {
        int curr = queue.front();
        queue.pop();
        for (const auto &next : igraph.get_next_vertices(curr)) {
            if (distance[curr] + 1 < distance[next]) {
                distance[next] = distance[curr] + 1;
                counter[next] = counter[curr];

                queue.push(next);
            } else if (distance[curr] + 1 == distance[next]) {
                counter[next] += counter[curr];
            }
        }
    }
    return counter[to];
}

template<typename T>
void run(std::istream &input = std::cin, std::ostream &output = std::cout) {
    int count_vertex = 0;
    int count_edge = 0;
    input >> count_vertex;
    input >> count_edge;

    T igraph(count_vertex);

    int from = 0;
    int to = 0;
    for (int i = 0; i < count_edge; ++i) {
        input >> from;
        input >> to;

        igraph.add_edge(from, to);
        igraph.add_edge(to, from);
    }

    int start = 0;
    int end = 0;
    input >> start;
    input >> end;

    output << number_of_shortest_paths(start, end, igraph) << std::endl;
}

int main() {
    std::stringstream ss("4\n5\n0 1\n0 2\n1 2\n1 3\n2 3\n\n0 3");
//    run<ListGraph>(ss);
    // run<ListGraph>();
    std::stringstream ss2("4\n5\n0 1\n0 2\n1 2\n1 3\n2 3\n\n0 3");
    run<MatrixGraph>(ss2);
    // run<MatrixGraph>();
    std::stringstream ss3("4\n5\n0 1\n0 2\n1 2\n1 3\n2 3\n\n0 3");
    run<SetGraph>(ss3);
    // run<SetGraph>();
    return 0;
}

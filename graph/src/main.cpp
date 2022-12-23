#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#include <iostream>
#include "arcgraph.h"
#include "listgraph.h"
#include "matrixgraph.h"
#include "setgraph.h"

int number_of_shortest_paths(const int from, const int to, IGraph &graph) {
    std::vector<int> distance(graph.VerticesCount(), INT_MAX);
    distance[from] = 0;

    std::vector<int> counter(graph.VerticesCount(), 0);
    counter[from] = 1;

    std::queue<int> queue;

    queue.push(from);

    while (!queue.empty()) {
        int curr = queue.front();
        queue.pop();

        for (auto &next: graph.GetNextVertices(curr)) {
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

    input >> count_vertex >> count_edge;

    // ListGraph graph(count_vertex);
    // MatrixGraph graph(count_vertex);
    // SetGraph graph(count_vertex);
    T graph(count_vertex);

    int from = 0;
    int to = 0;
    for (size_t i = 0; i < count_edge; ++i) {
        input >> from >> to;

        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    int start = 0;
    int end = 0;

    input >> start >> end;

    output << number_of_shortest_paths(start, end, graph) << std::endl;
}

int main() {

    run<ListGraph>();

    return 0;
}
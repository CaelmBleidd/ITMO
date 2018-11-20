#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

size_t n;
std::vector<std::vector<int64_t>> graph;

void read_ordered_weight_graph() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> n;

    graph.assign(n + 1, std::vector<int64_t>(n + 1));

    for (auto i = 1; i < n + 1; ++i) {
        for (auto j = 1; j < n + 1; ++j) {
            std::cin >> graph[i][j];
        }
    }
}

void floyd() {
    for (auto k = 1; k < n + 1; ++k) {
        for (auto i = 1; i < n + 1; ++i) {
            for (auto j = 1; j < n + 1; ++j) {
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}

void write_graph() {
    for (auto i = 1; i < n + 1; ++i) {
        for (auto j = 1; j < n + 1; ++j)
            std::cout << graph[i][j] << ' ';
        std::cout << '\n';
    }
}

int main() {
    read_ordered_weight_graph();
    floyd();
    write_graph();
    return 0;
}
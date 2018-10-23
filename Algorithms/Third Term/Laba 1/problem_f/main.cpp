#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>

std::vector<std::vector<int64_t> > graph, t_graph;
std::vector<int64_t> colors;
std::vector<int64_t> ordered;
std::vector<uint16_t> used;
std::set<std::pair<int64_t, int64_t>> edges;

int64_t color = 0;

void first_dfs(int64_t vertex) {
    used[vertex] = 1;
    for(auto next: graph[vertex])
        if (!used[next])
            first_dfs(next);
    ordered.push_back(vertex);
}

void second_dfs(int64_t vertex, int64_t color) {
    colors[vertex] = color;
    for(auto i : t_graph[vertex]) {
        if (colors[i] == -1)
            second_dfs(i, color);
    }
}

int main() {
    int64_t n, m;
    std::cin >> n >> m;

    graph.resize(n + 1);
    t_graph.resize(n + 1);

    for (int64_t i = 0; i < m; ++i) {
        int64_t first, second;
        std::cin >> first >> second;
        graph[first].push_back(second);
        t_graph[second].push_back(first);
    }

    used.assign(n + 1, 0);
    for (int64_t i = 1; i <= n; ++i) {
        if (used[i] == 0)
            first_dfs(i);
    }

    colors.assign(n + 1, -1);
    for (uint64_t i = 1; i <= n; ++i) {
        int64_t vertex = ordered[n - i];
        if (colors[vertex] == -1)
            second_dfs(vertex, color++);
    }

    for (auto i = 1; i < graph.size(); ++i) {
        for (auto j = 0; j < graph[i].size(); ++j) {
            auto tmp = graph[i][j];
            if (colors[i] != colors[tmp]) {
                edges.insert(std::make_pair(colors[i], colors[tmp]));
            }
        }
    }
    std::cout << edges.size();

    return 0;
}
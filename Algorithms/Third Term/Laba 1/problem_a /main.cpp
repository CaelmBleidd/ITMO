#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

bool is_cycle = false;

std::vector<int16_t> color;
std::vector<std::unordered_set<int64_t>> edges;
std::vector<int64_t> answer;

void dfs(int64_t vertex) {
    if (color[vertex] == 2)
        return;
    else if (color[vertex] == 1) {
        is_cycle = true;
        return;
    }

    color[vertex] = 1;
    for (auto i : edges[vertex]) {
        dfs(i);
    }
    color[vertex] = 2;
    answer.push_back(vertex);
}

void top_sort() {
    for (int i = 1; i < color.size(); ++i) {
        dfs(i);
    }
    std::reverse(answer.begin(), answer.end());
}

int main() {
    uint64_t n{0}, m{0};
    std::cin >> n >> m;

    color.assign(n + 1, 0);
    edges.assign(n + 1, std::unordered_set<int64_t>());

    for (int64_t i = 0; i < m; ++i) {
        int64_t vertex_1{0}, vertex_2{0};
        std::cin >> vertex_1 >> vertex_2;
        edges[vertex_1].insert(vertex_2);
    }

    top_sort();

    if (is_cycle)
        std::cout << -1;
    else {
        for (auto i: answer)
            std::cout << i << ' ';
    }
    return 0;
}


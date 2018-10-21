#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>

int64_t const AMOUNT_VERTEXES = (int64_t) 1e5 + 1;

std::set<uint64_t> brides;
std::map<std::pair<uint64_t, uint64_t>, uint64_t> number_of_edge;
std::vector<std::set<int64_t>> edges;
std::vector<uint64_t> time_in;
std::vector<uint64_t> fup;
std::vector<bool> used;

uint64_t timer = 0;

void dfs(uint64_t vertex, uint64_t parent) {
    used[vertex] = true;
    ++timer;
    time_in[vertex] = timer;
    fup[vertex] = timer;
    for (auto i : edges[vertex]) {
        if (i == parent)
            continue;
        if (used[i] == 1)
            fup[vertex] = std::min(fup[vertex], time_in[i]);
        else {
            dfs(i, vertex);
            fup[vertex] = std::min(fup[vertex], fup[i]);
        }
        if (time_in[vertex] < fup[i])
            brides.insert(number_of_edge[std::make_pair(vertex, i)]);
    }
}

int main() {
    uint64_t n{0}, m{0};
    std::cin >> n >> m;

    edges.resize(n + 1);
    time_in.resize(n + 1);
    fup.resize(n + 1);
    used.assign(n + 1, false);

    time_in[0] = INT64_MAX;


    for (uint64_t i = 1; i <= m; ++i) {
        uint64_t vertex_1{0}, vertex_2{0};
        std::cin >> vertex_1 >> vertex_2;
        number_of_edge[std::make_pair(vertex_1, vertex_2)] = i;
        number_of_edge[std::make_pair(vertex_2, vertex_1)] = i;
        edges[vertex_1].insert(vertex_2);
        edges[vertex_2].insert(vertex_1);
    }

    for (uint64_t i = 1; i <= n; ++i) {
        if (!used[i])
            dfs(i, 0);
    }

    std::cout << brides.size() << '\n';
    for (auto i : brides)
        std::cout << i << ' ';

    return 0;
}
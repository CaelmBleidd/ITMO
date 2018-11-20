#include <iostream>
#include <vector>
#include <set>

std::vector<bool> color;
std::vector<std::set<std::pair<int64_t, int64_t>>> graph;
std::vector<int64_t> result;

uint64_t n = 0;
uint64_t m = 0;

void read_unordered_weight_graph() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> n >> m;
    color.assign(n + 1, false);
    graph.assign(n + 1, std::set<std::pair<int64_t, int64_t>>()); // [weight -> number]
    result.assign(n + 1, INT64_MAX / 3);

    result[0] = result[1] = 0;

    for (auto i = 0; i < m; ++i) {
        int64_t from, to, weight;
        std::cin >> from >> to >> weight;
        graph[from].insert(std::make_pair(weight, to));
        graph[to].insert(std::make_pair(weight, from));
    }
}

void dijkstra() {
    std::set<std::pair<int64_t, int64_t>> container;
    container.insert(std::make_pair(0, 1));
    while (!container.empty()) {
        auto tmp = *container.begin();
        container.erase(container.begin());
        for (auto u : graph[tmp.second]) {
            if (result[u.second] > result[tmp.second] + u.first) {
                 result[u.second] = result[tmp.second] + u.first;
                 container.erase(u);
                 container.insert(u);
            } else
                continue;
        }
    }
}


int main() {
    read_unordered_weight_graph();
    dijkstra();
    for (auto i  = 1; i < result.size(); ++i)
        std::cout << result[i] << ' ';
    return 0;
}


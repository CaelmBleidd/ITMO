#include <iostream>
#include <vector>

struct edge {
    edge(uint64_t from, uint64_t to, int64_t value) : from(from), to(to), value(value) {}

    uint64_t from, to;
    int64_t value;
};

std::vector<edge> edges;
std::vector<int64_t> result;
std::vector<int64_t> path;
std::vector<int64_t> cycle;
int64_t n, m, k, start;
std::vector<std::vector<int64_t>> answer;

void read_ordered_graph() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> n >> m >> k >> start;

    answer.assign(k + 1, std::vector<int64_t>(n + 1, INT64_MAX / 2));

    for (uint64_t i = 1; i <= m; ++i) {
        int64_t from, to, tmp;
        std::cin >> from >> to >> tmp;
        if (tmp != 100000)
            edges.emplace_back(from, to, tmp);
    }
}

void shortest_k_path() {
    answer[0][start] = 0;

    for (auto i = 1; i <= k; ++i) {
        for (auto &edge : edges) {
            if (answer[i - 1][edge.from] < INT64_MAX / 3) {
                answer[i][edge.to] = std::min(answer[i][edge.to], answer[i - 1][edge.from] + edge.value);
            }
        }
    }
}


int main() {
    read_ordered_graph();
    shortest_k_path();
    for (auto i = 1; i <= n; ++i) {
        if (answer[k][i] > 1e9)
            std::cout << -1 << ' ';
        else
            std::cout << answer[k][i] << ' ';
    }
    return 0;
}
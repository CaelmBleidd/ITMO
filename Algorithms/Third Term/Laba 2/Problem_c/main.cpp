#include <iostream>
#include <vector>

struct edge {
    edge(uint64_t from, uint64_t to, int64_t value): from(from), to(to), value(value) {}

    uint64_t from, to;
    int64_t value;
};

std::vector<edge> edges;
std::vector<int64_t> result;
std::vector<int64_t> path;
std::vector<int64_t> cycle;
uint64_t n;

void read_ordered_graph() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> n;

    result.assign(n + 1, 0);
    path.assign(n + 1, -1);
    result[0] = result[1] = 0;

    for (uint64_t i = 1; i <= n; ++i) {
        for (uint64_t j = 1; j <= n; ++j) {
            int64_t tmp;
            std::cin >> tmp;
            if (tmp != 100000)
                edges.emplace_back(i, j, tmp);
        }
    }
}

void ford_bellman() {
    int64_t was_changed = -1;
    for (auto i = 0; i < n; ++i) {
        was_changed = -1;
        for (auto j = 0; j < edges.size(); ++j) {
            if (result[edges[j].from] < INT64_MAX / 3) {
                if (result[edges[j].to] > result[edges[j].from] + edges[j].value) {
                    result[edges[j].to] = std::max(-(INT64_MAX / 3), result[edges[j].from] + edges[j].value);
                    path[edges[j].to] = edges[j].from;
                    was_changed = edges[j].to;
                }
            }
        }
    }

    if (was_changed == -1) {
        std::cout << "NO";
    } else {
        for (auto i = 0; i < n; ++i)
            was_changed = path[was_changed];

        auto u = was_changed;
        cycle.push_back(was_changed);
        while( u != path[was_changed]) {
            was_changed = path[was_changed];
            cycle.push_back(was_changed);
        }

        std::cout << "YES\n" << cycle.size() << '\n';
        for (auto i = cycle.rbegin(); i != cycle.rend(); ++i) {
            std::cout << *i << ' ';
        }
    }

}

int main() {
    read_ordered_graph();
    ford_bellman();
    return 0;
}

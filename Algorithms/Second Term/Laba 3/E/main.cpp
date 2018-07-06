#include <iostream>
#include <vector>

int64_t n;
std::vector<std::vector<int64_t> > edges(2 * 100000 + 50);
std::vector<int64_t> decomposition(2 * 100000 + 50);
std::vector<int64_t> level(2 * 100000 + 50, -1);

int64_t dfs_counting(int64_t v, int64_t size, int64_t &centroid, int64_t p = -1) {
    int64_t s = 1;
    for (auto to: edges[v])
        if (level[to] == -1 && to != p)
            s += dfs_counting(to, size, centroid, v);
    if (centroid == -1 && (2 * s >= size || p == -1))
        centroid = v;
    return s;
}

void dfs(int64_t v, int64_t size, int64_t depth, int64_t last) {
    int64_t centroid = -1;
    dfs_counting(v, size, centroid);
    level[centroid] = depth;
    decomposition[centroid] = last;
    for (auto to: edges[centroid])
        if (level[to] == -1)
            dfs(to, size / 2, depth + 1, centroid);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::cin >> n;
    int64_t v = 0, u = 0;
    for (uint64_t i = 0; i < n - 1; ++i) {
        std::cin >> v >> u;
        edges[--v].push_back(--u);
        edges[u].push_back(v);
    }

    dfs(0, n, 0, -1);
    for (uint64_t i = 0; i < n; ++i) {
        std::cout << decomposition[i] + 1 << ' ';
    }

    return 0;
}
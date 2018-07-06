#include <iostream>
#include <vector>
#include <cmath>

int64_t lca(int64_t v, int64_t u, int64_t &min, std::vector<int64_t> &d,
            std::vector<std::vector<std::pair<int64_t, int64_t>>> &dp, int64_t length) {
    if (d[v] > d[u]) {
        int64_t tmp = v;
        v = u;
        u = tmp;
    }
    for (int64_t i = length - 1; i >= 0; --i) {
        if (d[u] - d[v] >= (1 << i)) {
            min = std::min(min, dp[u][i].second);
            u = dp[u][i].first;
        }
    }

    if (v == u)
        return v;

    for (int64_t i = length - 1; i >= 0; --i) {
        if (dp[v][i] != dp[u][i]) {
            min = std::min(std::min(min, dp[v][i].second), dp[u][i].second);
            v = dp[v][i].first;
            u = dp[u][i].first;
        }
    }
    return dp[v][0].first;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::freopen("minonpath.in", "r", stdin);
    std::freopen("minonpath.out", "w", stdout);

    int64_t n = 0;
    std::cin >> n;
    int64_t length = (int64_t) (std::log(n) / std::log(2)) + 1;

    std::vector<int64_t> d(n, 0);
    std::vector<std::vector<std::pair<int64_t, int64_t>>> dp;

    for (int64_t i = 0; i < n; ++i) {
        dp.emplace_back(std::vector<std::pair<int64_t, int64_t>>(length));
    }

    for (int64_t i = 0; i < length; ++i) {
        dp[0][i] = std::make_pair(0, INT64_MAX);
    }

    for (int64_t i = 1; i < n; ++i) {
        int64_t from = 0, cost = 0;
        std::cin >> from >> cost;
        dp[i][0] = std::make_pair(--from, cost);
        d[i] = d[from] + 1;
    }

    std::pair<int64_t, int64_t> cur, to;
    for (int64_t j = 1; j < length; ++j) {
        for (int64_t i = 1; i < n; ++i) {
            cur = dp[i][j - 1];
            to = dp[cur.first][j - 1];
            dp[i][j] = std::make_pair(to.first, std::min(cur.second, to.second));
        }
    }

    int64_t m = 0;
    std::cin >> m;


    for (int64_t i = 0; i < m; ++i) {
        int64_t min = INT64_MAX;
        int64_t first = 0, second = 0;
        std::cin >> first >> second;
        lca(first - 1, second - 1, min, d, dp, length);
        std::cout << min << '\n';
    }

    return 0;
}


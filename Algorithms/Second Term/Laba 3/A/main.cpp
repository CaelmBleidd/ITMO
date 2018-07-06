#include <iostream>
#include <vector>
#include <cmath>


int main() {
    int64_t n;
    std::cin >> n;
    int64_t length;
    std::vector<int64_t> d(n);

    length = static_cast<int64_t> (std::log(n) / std::log(2) + 1);

    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(length));

    d[0] = 0;

    for (int64_t i = 0; i < length; ++i) {
        dp[0][i] = 0;
    }
    for (int64_t i = 1; i < n; ++i) {
        int64_t from;
        std::cin >> from;
        --from;
        dp[i][0] = from;
        d[i] = d[from] + 1;
    }
    for (int64_t j = 1; j < length; ++j) {
        for (int64_t i = 1; i < n; ++i) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }

    int64_t m;
    std::cin >> m;
    for (int64_t p = 0; p < m; ++p) {
        int64_t v, u = 0;
        std::cin >> v >> u;
        --v;
        --u;
        if (d[v] > d[u]) {
            int64_t tmp = v;
            v = u;
            u = tmp;
        }
        for (int64_t i = length - 1; i >= 0; --i) {
            if (d[u] - d[v] >= (1 << i)) {
                u = dp[u][i];
            }
        }
        if (v == u) {
            std::cout << v + 1 << '\n';
            continue;
        }
        for (int64_t i = length - 1; i >= 0; --i) {
            if (dp[v][i] != dp[u][i]) {
                v = dp[v][i];
                u = dp[u][i];
            }
        }
        std::cout << dp[v][0] + 1 << '\n';
    }


    return 0;
}
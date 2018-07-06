#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <deque>

const uint64_t MODULE = (uint64_t) 1e9 + 7;

int main() {
    std::freopen("problem4.in", "r", stdin);
    std::freopen("problem4.out", "w", stdout);

    uint64_t answer = 0;
    uint64_t n, m, k, l;
    std::vector<bool> terminals;

    n = m = k = l = 0;
    std::cin >> n >> m >> k >> l;

    std::vector<uint64_t> from (m + 1);
    std::vector<uint64_t> to(m + 1);

    terminals.assign(n + 1, false); //допускающие состояния
    for (uint64_t i = 0; i < k; ++i) {
        uint64_t p = 0;
        std::cin >> p;
        terminals[p] = true;
    }


    for (uint64_t i = 0; i < m; ++i) {
        uint64_t number = 0, second_number = 0;
        char symbol = ' ';
        std::cin >> number >> second_number >> symbol;
        from[i + 1] = number;
        to[i + 1] = second_number;
    }

    std::vector<uint64_t> dp(n + 1);
    for (auto i = 0; i <= n; ++i)
        dp[i] = terminals[i] ? 1 : 0;

    for (uint64_t i = 0; i < l; ++i) {
        std::vector<uint64_t> new_dp(n + 1, 0);
        for (uint64_t j = 1; j <= m; ++j) {
            new_dp[from[j]] += dp[to[j]];
            new_dp[from[j]] %= MODULE;
        }
        dp = new_dp;
    }

    std::cout << dp[1];

    return 0;
}


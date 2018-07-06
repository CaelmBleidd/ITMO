
#include <iostream>
#include <vector>
#include <cmath>

uint64_t array[100001];
uint64_t left[10000001];
uint64_t right[10000001];
uint64_t answer[10000001];
uint64_t logs[100001];
uint64_t st[100001][20];

int main() {
    std::freopen("sparse.in", "r", stdin);
    std::freopen("sparse.out", "w", stdout);

    uint64_t n, m, a1;
    n = m = a1 = 0;

    std::cin >> n >> m >> a1;

    logs[0] = 0;
    logs[1] = 0;
    for (size_t i = 2; i <= n + 20; ++i)
        logs[i] = (logs[i / 2] + 1);


    array[1] = a1;

    for (size_t i = 2; i <= n; ++i) {
        array[i] = (23 * array[i - 1] + 21563) % 16714589;
    }

    uint64_t k = 20;

    for (int i = 0; i <= n; i++)
        st[i][0] = array[i];

    for (int j = 1; j <= k + 1; j++)
        for (int i = 0; i + (1 << j) <= n + 1; i++)
            st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);


    std::cin >> left[1] >> right[1];

    for (size_t i = 2; i <= m; ++i) {
        uint64_t l = std::min(left[i - 1], right[i - 1]);
        uint64_t r = std::max(left[i - 1], right[i - 1]);
        uint64_t j = logs[r - l + 1];
        answer[i - 1] = std::min(st[l][j], st[r - (1 << j) + 1][j]);
        left[i] = ((17 * left[i - 1] + 751 + answer[i - 1] + 2 * (i - 1)) % n) + 1;
        right[i] = ((13 * right[i - 1] + 593 + answer[i - 1] + 5 * (i - 1)) % n) + 1;
    }
    uint64_t l = std::min(left[m], right[m]);
    uint64_t r = std::max(left[m], right[m]);
    uint64_t j = logs[(r - l + 1)];
    answer[m] = std::min(st[l][j], st[r - (1 << j) + 1][j]);

    std::cout <<  left[m] << ' ' << right[m] << ' ' << answer[m];


    return 0;
}
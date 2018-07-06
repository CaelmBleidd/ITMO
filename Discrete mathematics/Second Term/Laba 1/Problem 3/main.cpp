#include <iostream>
#include <vector>
#include <cmath>

int main() {
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);

    double_t n, m;
    std::vector<double_t > a(1, 0);
    std::vector<double_t > b(1, 0);

    std::cin >> n >> m;

    for (size_t i = 1; i <= m; ++i) {
        uint64_t aa, bb;
        std::cin >> aa >> bb;
        a.push_back(aa);
        b.push_back(bb);
    }

    double_t result = 0;
    double_t tmp = 1;
    double_t win = 1;
    double_t lose = 1;

    for (int64_t i = 1; i <= m; ++i) {
        lose = win * (a[i] - 1) / a[i];
        win *= 1 / a[i];
        result += lose * b[i - 1];
    }
    result += win * b[m];
    std::cout << n - result;
    return 0;
}
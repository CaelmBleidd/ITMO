#include <iostream>
#include <vector>
#include <cmath>

int main() {
    freopen("sum0.in", "r", stdin);
    freopen("sum0.out", "w", stdout);

    const auto first_const = (int64_t) std::pow(2, 16);
    const auto second_const = (int64_t) std::pow(2, 30);

    std::vector<int64_t> a(1);
    std::vector<int64_t> b(1);

    int64_t n, x, y;
    std::cin >> n >> x >> y >> a[0];

    int64_t m, z, t;
    std::cin >> m >> z >> t >> b[0];

    for (int64_t i = 1; i < n; ++i) {
        a.push_back((x * a[i - 1] + y) % first_const);
    }

    for (int64_t i = 1; i < 2 * m; ++i) {
        auto tmp = (z * b[i - 1] + t) >= 0 ?(z * b[i - 1] + t) % second_const : second_const + (z * b[i - 1] + t);
        b.push_back(tmp);
    }

    for (int64_t i = 0; i < b.size(); ++i) {
        b[i] %= n;
    }

    int64_t result = 0;

    std::vector<int64_t> tree(std::move(a));
    for (int i = 1; i < n; ++i) {
        tree[i] = tree[i] + tree[i-1];
    }

    for (int64_t i = 0; i < m; ++i) {
        int64_t left = std::min(b[2 * i], b[2 * i + 1]);
        int64_t right = std::max(b[2 * i], b[2 * i + 1]);
        result += left > 0 ? tree[right] - tree[left - 1] : tree[right];
    }

    std::cout << result;

    return 0;
}


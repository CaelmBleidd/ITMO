#include <iostream>
#include <vector>

int main() {
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);

    double result = 0;
    double k, n;
    std::vector<double> p;
    std::vector<double> m;

    std::cin >> k >> n;
    for (int64_t i = 0; i < k; ++i) {
        int64_t pi, mi;
        std::cin >> pi >> mi;
        p.push_back(pi);
        m.push_back(mi);
    }

    for (int i = 0; i < k; ++i) {
        result += (p[i] / n) * (m[i] / 100);
    }
    std::cout << result;
    return 0;
}
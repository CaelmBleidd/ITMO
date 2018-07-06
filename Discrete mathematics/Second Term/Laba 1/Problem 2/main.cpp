#include <iostream>
#include <vector>
#include <vector>
#include <cmath>

int main() {
    freopen("shooter.in", "r", stdin);
    freopen("shooter.out", "w", stdout);

    double n, m, k;
    std::vector<double> p;

    std::cin >> n >> m >> k;

    for (int64_t i = 0; i < n; i++) {
        double a;
        std::cin >> a;
        p.push_back(1 - a);
    }
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += std::pow(p[i], m);
    }
    double result = (std::pow(p[k - 1], m)) / sum;
    std::printf("%.13f", result);

    return 0;
}
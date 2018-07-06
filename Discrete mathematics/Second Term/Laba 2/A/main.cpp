#include <iostream>
#include <string>
#include <vector>

int main() {
    std::freopen("problem1.in", "r", stdin);
    std::freopen("problem1.out", "w", stdout);

    std::string line;
    std::cin >> line;

    size_t n, m, k;
    n = m = k = 0;
    std::cin >> n >> m >> k;

    std::vector<size_t> terminals(k, 0);
    for (auto i : terminals)
        std::cin >> i;

    size_t start = 1;




    return 0;
}
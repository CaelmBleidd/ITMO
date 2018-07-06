#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    std::freopen("problem1.in", "r", stdin);
    std::freopen("problem1.out", "w", stdout);

    std::string line;
    std::cin >> line;

    size_t n, m, k;
    n = m = k = 0;
    std::cin >> n >> m >> k;

    std::vector<bool> terminals(n + 1, false); //допускающие состояния
    for (size_t i = 0; i < k; ++i) {
        size_t p = 0;
        std::cin >> p;
        terminals[p] = true;
    }

    std::vector<std::map<char, size_t>> transitions(n + 1);

    size_t cur_position = 1;

    for (size_t i = 0; i < m; ++i ) {
        size_t number = 0, second_number = 0;
        char symbol = ' ';
        std::cin >> number >> second_number >> symbol;
        transitions[number][symbol] = second_number;
    }

    for (size_t i = 0; i < line.size(); ++i) {
        char tmp_symbol = line[i];
        cur_position = transitions[cur_position][tmp_symbol];
    }

    if (terminals[cur_position])
        std::cout << "Accepts";
    else
        std::cout << "Rejects";


    return 0;
}
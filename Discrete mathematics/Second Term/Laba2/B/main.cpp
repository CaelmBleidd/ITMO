#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>

int64_t word_size;

bool is_accept(int64_t index, int64_t pos, std::vector<std::vector<int64_t>> &matrix, std::vector<bool> &terminals,
               std::vector<std::vector<std::pair<char, int64_t>>> &transitions, std::string &line){
    if (matrix[index][pos] != -1)
        return matrix[index][pos] == 1;
    if (index == word_size ) {
        matrix[index][pos] = terminals[pos] ? 1 : 0;
        return matrix[index][pos] == 1;
    }

    for (std::pair<char, int64_t> p : transitions[pos]) {
        if (p.first == line[index] && is_accept(index + 1, p.second, matrix, terminals, transitions, line)) {
            matrix[index][pos] =1;
            return true;
        }
    }

    matrix[index][pos] = 0;
    return false;
}

int main() {
    std::freopen("problem2.in", "r", stdin);
    std::freopen("problem2.out", "w", stdout);

    std::string line;
    std::cin >> line;
    word_size = line.size();

    int64_t cur_pos = 1;

    int64_t n, m, k;
    n = m = k = 0;
    std::cin >> n >> m >> k;

    std::vector<bool> terminals(n + 1, false); //допускающие состояния
    for (int64_t i = 0; i < k; ++i) {
        int64_t p = 0;
        std::cin >> p;
        terminals[p] = true;
    }

    std::vector<std::vector<std::pair<char, int64_t>>> transitions(n + 1);
    for (int64_t i = 0; i < m; ++i) {
        int64_t from = 0, to = 0;
        char symbol = 's';
        std::cin >> from >> to >> symbol;
        transitions[from].push_back(std::pair<char, int64_t>(symbol, to));
    }

    std::vector<std::vector<int64_t>> matrix(line.size() + 1, std::vector<int64_t> (m + 1, -1));

    bool accept = false;

    accept = is_accept(0, 1, matrix, terminals, transitions, line);

    if (accept)
        std::cout << "Accepts";
    else
        std::cout << "Rejects";

    return 0;
}

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

void read_dka(std::vector<bool> &terminals, std::vector<std::unordered_map<char, size_t>> &transition, std::set<char> &alphabet) {
    size_t n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;

    terminals.assign(n + 1, false);
    transition.resize(n + 1);

    for (size_t i = 0; i < k; ++i) {
        size_t tmp = 0;
        std::cin >> tmp;
        terminals[tmp] = true;
    }

    std::vector<char> tmp_alpha;

    for (size_t i = 0; i < m; ++i) {
        size_t from = 0, to = 0;
        char symbol = ' ';
        std::cin >> from >> to >> symbol;
        transition[from][symbol] = to;
        tmp_alpha.push_back(symbol);
    }
    std::set<char> d(tmp_alpha.begin(), tmp_alpha.end());
    alphabet = d;
}

struct dka {
    std::vector<bool> terminals;
    std::vector<std::unordered_map<char, size_t>> transitions;
    std::set<char> alphabet;


    dka() {
        read_dka(terminals, transitions, alphabet);
    };

};

bool is_isomorphic(dka *first_dka, dka *second_dka, size_t first, size_t second, std::vector<bool> &used) {
    used[first] = true;
    if (first_dka->terminals[first] != second_dka->terminals[second])
        return false;
    bool isomorphism = true;
    for (char symbol : first_dka->alphabet) {
        bool first_contains = (first_dka->transitions[first].find(symbol) != first_dka->transitions[first].end());
        bool second_contains = (second_dka->transitions[second].find(symbol) != second_dka->transitions[second].end());

        if (first_contains != second_contains) {
            return false;
        } else {
            if (!used[first_dka->transitions[first][symbol]] && first_contains && second_contains) {
                isomorphism &= is_isomorphic(first_dka, second_dka, first_dka->transitions[first][symbol],
                                             second_dka->transitions[second][symbol], used);
            }
        }
    }
    return isomorphism;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("isomorphism.in", "r", stdin);
    std::freopen("isomorphism.out", "w", stdout);

    auto first = new dka();
    auto second = new dka();

    std::vector<bool> used(first->terminals.size(), false);

    bool result = is_isomorphic(first, second, 1, 1, used);
    if (result)
        std::cout << "YES";
    else
        std::cout << "NO";

    return 0;
}
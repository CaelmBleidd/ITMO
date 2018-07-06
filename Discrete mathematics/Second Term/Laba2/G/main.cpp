#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <deque>

void read_dka(std::vector<bool> &terminals, std::vector<std::unordered_map<char, size_t>> &transition, std::set<char> &alphabet, std::vector<bool> &used) {
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

    for (uint64_t j = 0; j < n + 1; ++j) {
        for (char i = 'a'; i <= 'z'; ++i) {
            if (transition[j].find(i) == transition[j].end())
                transition[j][i] = 0;
        }
    }

    std::set<char> d(tmp_alpha.begin(), tmp_alpha.end());
    alphabet = d;

    used.assign(n + 1, false);
}

struct dka {
    std::vector<bool> terminals;
    std::vector<std::unordered_map<char, size_t>> transitions;
    std::set<char> alphabet;
    std::vector<bool> used;

    dka() {
        read_dka(terminals, transitions, alphabet, used);
    };

};


bool is_equal(dka *first, dka *second, size_t first_size, size_t second_size) {
    std::deque<std::pair<uint64_t, uint64_t>> queue;
    queue.emplace_back(1, 1);
    while (!queue.empty()) {
        auto tmp = queue.front();
        auto u = tmp.first;
        auto v = tmp.second;
        queue.pop_front();
        if (first->terminals[u] != second->terminals[v])
            return false;
        first->used[u] = (u != 0);
        second->used[v] = (v != 0);
        if (v == 0 && u == 0)
            continue;
        for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
            if (!first->used[first->transitions[u][symbol]] || !second->used[second->transitions[v][symbol]]) {
                queue.emplace_back(std::make_pair(first->transitions[u][symbol], second->transitions[v][symbol]));
            }
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("equivalence.in", "r", stdin);
    std::freopen("equivalence.out", "w", stdout);

    auto first = new dka();
    auto second = new dka();

    std::vector<bool> used(first->terminals.size(), false);

    bool result = is_equal(first, second, 1, 1);
    if (result)
        std::cout << "YES";
    else
        std::cout << "NO";

    return 0;
}
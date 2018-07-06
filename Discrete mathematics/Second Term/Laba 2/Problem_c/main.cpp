#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

const uint64_t MODULE = (uint64_t) (1e9 + 7);
void read_dka(uint64_t &n, uint64_t &m, uint64_t &k, std::vector<bool> &terminals,
              std::vector<std::vector<uint64_t>> &transitions,
              std::vector<std::vector<uint64_t>> &r_transitions, std::vector<bool> &loop) {
    std::cin >> n >> m >> k;

    terminals.assign(n + 1, false);
    for (uint64_t i = 0; i < n; ++i) {
        uint64_t tmp = 0;
        std::cin >> tmp;
        terminals[tmp] = true;
    }

    transitions.resize(n + 1);
    loop.assign(n + 1, false);
    for (uint64_t i = 0; i < m; ++i) {
        uint64_t first, second;
        first = second = 0;
        char symbol = ' ';
        std::cin >> first >> second >> symbol;
        transitions[first].push_back(second);
        r_transitions[second].push_back(first);

        if (first == second)
            loop[first] = true;
    }

//    for (uint64_t j = 0; j < n + 1; ++j) {
//        for (char i = 'a'; i <= 'z'; ++i) {
//            if (transitions[j].find(i) == transitions[j].end())
//                transitions[j][i] = 0;
//            if (r_transitions[j].find(i) == r_transitions[j].end())
//                r_transitions[j][i] = 0;
//        }
//    }


}


struct dka {
    uint64_t n = 0, m = 0, k = 0;
    std::vector<bool> terminals;
    std::vector<std::vector<uint64_t>> transitions;
    std::vector<std::vector<uint64_t>> r_transitions;
    std::vector<bool> loop;

    dka() {
        read_dka(n, m, k, terminals, transitions, r_transitions, loop);
    }
};

void top_sort(uint64_t number, std::vector<uint64_t> &used, std::vector<uint64_t> &size, dka &my_dka, std::vector<bool> &reachable, std::vector<uint64_t> &order) {
    used[number] = 3;
    reachable[number] = true;
    for (uint64_t i = 0; i < my_dka.transitions[number].size(); ++i) {
        if (used[my_dka.transitions[number][i]] != 3) {
            top_sort(my_dka.transitions[number][i], used, size, my_dka, reachable, order);
        }
    }
    order.push_back(number);
}

void con(uint64_t number, uint64_t curr_color, std::vector<bool> &reachable,) {
    if
}


int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::freopen("problem3.in", "r", stdin);
    std::freopen("problem3.out", "w", stdout);

    uint64_t n, m, k;
    n = m = k = 0;
    std::cin >> n >> m >> k;

    auto my_dka = dka();

    std::vector<bool> reachable(n + 1);
    std::vector<uint64_t> used (n + 1, 0);
    std::vector<uint64_t> color(n + 1);
    std::vector<uint64_t> ordered_vert;
    std::vector<uint64_t> size(n + 1);
    uint64_t colors = 0;

    top_sort(1, used, size, my_dka, reachable, ordered_vert);
    std::reverse(ordered_vert.begin(), ordered_vert.end());



    return 0;
}

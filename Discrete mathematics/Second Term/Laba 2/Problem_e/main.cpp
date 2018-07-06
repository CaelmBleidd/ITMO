#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <bitset>

uint64_t used_vertices = 1;

const uint64_t MODULE = (uint64_t) (1e9 + 7);
const uint64_t MAXN = 100;

typedef std::vector<std::vector<std::vector<uint64_t>>> vvv_uint64_t;
typedef std::vector<std::vector<uint64_t>> vv_uint64_t;
typedef std::map<std::bitset<MAXN>, uint64_t, bool (*)(const std::bitset<MAXN> &, const std::bitset<MAXN> &)> hyyyyyy;

bool compare(const std::bitset<MAXN> &a, const std::bitset<MAXN> &b) {
    return a.to_string() < b.to_string();
}

void read_nka(std::vector<bool> &terminals, vvv_uint64_t &g, uint64_t n, uint64_t m, uint64_t k) {
    terminals.assign(n, false);
    for (uint64_t i = 0; i < k; ++i) {
        uint64_t tmp = 0;
        std::cin >> tmp;
        terminals[tmp - 1] = true;
    }

    g.assign(n, vv_uint64_t(26));
    for (uint64_t i = 0; i < m; ++i) {
        uint64_t from, to;
        char symbol = ' ';
        from = to = 0;
        std::cin >> from >> to >> symbol;
        g[--from][symbol - 'a'].push_back(--to);
    }
}

struct nka {
    std::vector<bool> terminals;
    vvv_uint64_t g;
    uint64_t n, m, k, l;

    nka() {
        std::cin >> n >> m >> k >> l;
        read_nka(terminals, g, n, m, k);
    }
};

void nka_to_dka(std::queue<std::bitset<MAXN>> &queue,
                uint64_t n,
                nka &my_nka,
                hyyyyyy &new_ids,
                std::vector<bool> &new_terminal,
                std::vector<uint64_t> &from,
                std::vector<uint64_t> &tos) {
    while (!queue.empty()) {
        std::bitset<MAXN> now = queue.front();
        queue.pop();
        for (uint64_t ch = 0; ch < 26; ++ch) {
            std::bitset<MAXN> to;
            bool term = false;
            for (uint64_t i = 0; i < n; ++i) {
                if (!now[i])
                    continue;
                for (uint64_t j = 0; j < my_nka.g[i][ch].size(); ++j) {
                    uint64_t t = my_nka.g[i][ch][j];
                    to[t] = true;
                    term |= my_nka.terminals[t];
                }
            }

            if (new_ids.count(to) == 0) {
                new_ids[to] = used_vertices++;
                queue.push(to);
                new_terminal.push_back(term);
            }
            from.push_back(new_ids[now]);
            tos.push_back(new_ids[to]);
        }
    }
}



uint64_t solve(
        nka &my_nka,
        hyyyyyy &ids,
        std::vector<bool> &terminals,
        std::vector<uint64_t> &from,
        std::vector<uint64_t> &to,
        std::bitset<MAXN> &initial) {
    std::vector<uint64_t> dp(used_vertices);
    for (uint64_t i = 0; i < used_vertices; ++i)
        dp[i] = terminals[i] ? 1 : 0;
    for (uint64_t i = 0; i < my_nka.l; ++i) {
        std::vector<uint64_t> new_dp(used_vertices);
        for (uint64_t j = 0; j < from.size(); ++j) {
            new_dp[from[j]] += dp[to[j]];
            new_dp[from[j]] %= MODULE;
        }
        dp = new_dp;
    }
    return dp[ids[initial]];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::freopen("problem5.in", "r", stdin);
    std::freopen("problem5.out", "w", stdout);

    auto my_nka = nka();

    hyyyyyy new_ids(compare);
    std::bitset<MAXN> initial;
    initial.set(0);
    new_ids[initial] = 0;

    std::queue<std::bitset<MAXN>> q;
    q.push(initial);

    std::vector<uint64_t> from;
    std::vector<uint64_t> tos;
    std::vector<bool> new_terminals(1, my_nka.terminals[0]);

    nka_to_dka(q, my_nka.n, my_nka, new_ids, new_terminals, from, tos);

    std::cout << solve(my_nka, new_ids, new_terminals, from, tos, initial);

    return 0;
}


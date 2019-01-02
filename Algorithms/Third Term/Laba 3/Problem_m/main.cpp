#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>

#define ll int64_t

using namespace std;

const ll MAX_N = 400500;

struct State {
    State() = default;

    ll link;
    ll len;
    unordered_map<char, ll> next;
};


State automaton[MAX_N * 2];

void add_symbol(State automaton[], ll &n, ll &last, char c) {
    ll p = n++;
    automaton[p].len = automaton[last].len + 1;
    ll v = last;
    while (v != -1 && automaton[v].next.find(c) == automaton[v].next.end()) {
        automaton[v].next[c] = p;
        v = automaton[v].link;
    }
    if (v == -1) {
        automaton[p].link = 0;
    } else {
        ll u = automaton[v].next[c];
        if (automaton[v].len + 1 == automaton[u].len) {
            automaton[p].link = u;
        } else {
            ll w = n++;
            automaton[w].len = automaton[v].len + 1;
            automaton[w].link = automaton[u].link;
            automaton[w].next = automaton[u].next;
            while (v != -1 && automaton[v].next[c] == u) {
                automaton[v].next[c] = w;
                v = automaton[v].link;
            }
            automaton[p].link = w;
            automaton[u].link = w;
        }
    }
    last = p;
}

ll build_automaton(State automaton[], const string &s) {
    for (ll i = 0; i < 2 * s.size() + 10; ++i) {
        automaton[i].link = -1;
        automaton[i].len = -1;
    }
    ll last = 0;
    ll n = 1;
    automaton[last].len = 0;
    for (char i : s) {
        add_symbol(automaton, n, last, i);
    }
    return n;
}

int main() {
    std::freopen("common.in", "r", stdin);
    std::freopen("common.out", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    string first_line;
    string second_line;
    cin >> first_line;
    cin >> second_line;

    auto size = build_automaton(automaton, first_line);

    ll vertex = 0, length = 0, best = 0, best_pos = 0;
    for (ll i = 0; i < second_line.size(); ++i) {
        while (vertex && !automaton[vertex].next.count(second_line[i])) {
            vertex = automaton[vertex].link;
            length = automaton[vertex].len;
        }
        if (automaton[vertex].next.count(second_line[i])) {
            vertex = automaton[vertex].next[second_line[i]];
            ++length;
        }
        if (length > best) {
            best = length;
            best_pos = i;
        }
    }

    std::cout << second_line.substr(best_pos - best + 1, best);
}

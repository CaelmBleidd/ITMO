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
    ll link;
    ll len;
    ll next[26];
};

State automaton[MAX_N * 2];
vector<ll> amount;
vector<bool> counted;

ll global_last;
ll global_size;


void add_symbol(State automaton[], ll &n, ll &last, ll c) {
    ll p = n++;
    automaton[p].len = automaton[last].len + 1;
    ll v = last;
    while (v != -1 && automaton[v].next[c] == -1) {
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
            for (auto i = 0; i < 26; ++i) {
                automaton[w].next[i] = automaton[u].next[i];
            }
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
        for (ll &j : automaton[i].next) {
            j = -1;
        }
    }
    ll last = 0;
    ll n = 1;
    automaton[last].len = 0;
    for (char i : s) {
        add_symbol(automaton, n, last, i - 'a');
    }
    global_last = last;
    global_size = n;
    return n;
}

ll count(ll number) {
    if (counted[number])
        return amount[number];
    ll sum = 1;
    for (ll i: automaton[number].next) {
        if (i != -1)
            sum += count(i);
    }
    counted[number] = true;
    amount[number] = sum;
    return sum;
}

int main() {
    std::freopen("count.in", "r", stdin);
    std::freopen("count.out", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    string line;
    cin >> line;

    auto size = build_automaton(automaton, line);
    amount.resize(size, 0);
    counted.resize(size, false);

    auto answer = count(0) - 1;
    cout << amount[0] - 1;

}


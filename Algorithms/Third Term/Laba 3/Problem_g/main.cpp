#include <iostream>
#include <vector>
#include <string>


#define ll int64_t
#define forn for(int64_t i = 0; i < n; ++i)

using namespace std;

const int MAX_N = 1000100;
const int K = 26;

struct State {
    int link;
    int len;
    int next[K];
};

State automaton[MAX_N * 2];

void add_symbol(State automaton[], int &n, int &last, int c) {
    int p = n++;
    automaton[p].len = automaton[last].len + 1;
    int v = last;
    while (v != -1 && automaton[v].next[c] == -1) {
        automaton[v].next[c] = p;
        v = automaton[v].link;
    }
    if (v == -1) {
        automaton[p].link = 0;
    } else {
        int u = automaton[v].next[c];
        if (automaton[v].len + 1 == automaton[u].len) {
            automaton[p].link = u;
        } else {
            int w = n++;
            automaton[w].len = automaton[v].len + 1;
            automaton[w].link = automaton[u].link;
            for (auto i = 0; i < K; ++i) {
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

int build_automaton(State automaton[], const string &s) {
    for (int i = 0; i < 2 * s.size() + 10; ++i) {
        automaton[i].link = -1;
        automaton[i].len = -1;
        for (int &j : automaton[i].next) {
            j = -1;
        }
    }
    int last = 0;
    int n = 1;
    automaton[last].len = 0;
    for (char i : s) {
        add_symbol(automaton, n, last, i - 'a');
    }
    return n;
}

int main() {
    std::freopen("search4.in", "r", stdin);
    std::freopen("search4.out", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll n = 0;
    cin >> n;

    vector<string> lines;

    forn {
        string tmp;
        cin >> tmp;
        lines.push_back(tmp);
    }

    string line;
    cin >> line;

    build_automaton(automaton, line);

    string answer;

    for (const auto &tmp: lines) {
        auto state = 0;
        bool accepts = true;
        for (auto c: tmp) {
            if (automaton[state].next[c - 'a'] == -1) {
                accepts = false;
                break;
            } else {
                state = automaton[state].next[c - 'a'];
            }
        }
        if (accepts)
            answer += "YES\n";
        else
            answer += "NO\n";
    }

    cout << answer;

    return 0;
}

/*
 *
 */
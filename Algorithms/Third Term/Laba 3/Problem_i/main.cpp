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
    int first_position;
};

State automaton[MAX_N * 2];
State second_automaton[MAX_N * 2];

void add_symbol(State automaton[], int &n, int &last, int c) {
    int p = n++;
    automaton[p].len = automaton[last].len + 1;
    automaton[p].first_position = automaton[p].len - 1;
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
            automaton[w].first_position = automaton[u].first_position;
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

void reverse_str(string &str) {
    ll n = str.length();
    for (auto i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

ll find_first_position(State automaton[], string const &pattern) {
    ll s_t = 0;
    ll vertex = 0;
    while (s_t < pattern.size()) {
        vertex = automaton[vertex].next[pattern[s_t] - 'a'];
        s_t++;
        if (vertex == -1)
            return -1;
    }
    return automaton[vertex].first_position - (ll) pattern.length() + 1;
}

int main() {
    std::freopen("search6.in", "r", stdin);
    std::freopen("search6.out", "w", stdout);

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

    auto first_size = build_automaton(automaton, line);
    reverse_str(line);
    auto second_size = build_automaton(second_automaton, line);

    for (auto &tmp_line : lines) {
        cout << find_first_position(automaton, tmp_line);
        reverse_str(tmp_line);
        auto reverse_position = find_first_position(second_automaton, tmp_line);
        if (reverse_position == -1)
            cout << ' ' << -1 << '\n';
        else
            cout << ' ' << line.size() - tmp_line.size() - reverse_position << '\n';
    }


    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>

#define ll int64_t

using namespace std;

const int MAX_N = 1000000;

struct State {
    int link;
    int len;
    unordered_map<char, int> next;
};


State automaton[MAX_N * 2];
int cnt[MAX_N * 2];
set<pair<int, int>> base;
int s_t = 0;

void add_symbol(State automaton[], int &n, int &last, char c) {
    int p = n++;
    automaton[p].len = automaton[last].len + 1;
    cnt[p] = 1;
    base.insert(make_pair(automaton[p].len, p));
    int v = last;
    while (v != -1 && automaton[v].next.find(c) == automaton[v].next.end()) {
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
            automaton[w].next = automaton[u].next;
            cnt[w] = 0;
            base.insert(make_pair(automaton[w].len, w));
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
    }
    int last = 0;
    int n = 1;
    automaton[last].len = 0;
    for (char i : s) {
        add_symbol(automaton, n, last, i);
    }
    return n;
}

int count_number(string pattern) {
    int vertex = 0;
    s_t = 0;
    while (s_t < pattern.size()) {
        if (automaton[vertex].next.find(pattern[s_t]) == automaton[vertex].next.end())
            return 0;
        vertex = automaton[vertex].next[pattern[s_t]];
        s_t++;
    }
    return cnt[vertex];
}


int main() {
    std::freopen("search5.in", "r", stdin);
    std::freopen("search5.out", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);



    int number;
    cin >> number;

    vector<string> lines;
    for (auto i = 0; i < number; ++i) {
        string tmp;
        cin >> tmp;
        lines.push_back(tmp);
    }

    string temp;
    cin >> temp;
    auto size = build_automaton(automaton, temp);
    for (auto it = base.rbegin(); it != base.rend(); it++) {
        cnt[automaton[it->second].link] += cnt[it->second];
    }
    for (auto i = 0; i < number; ++i) {
        cout << count_number(lines[i]) << '\n';
    }




}

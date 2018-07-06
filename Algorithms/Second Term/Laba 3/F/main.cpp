#include <iostream>
#include <vector>
#include <cmath>
#include <set>

int64_t l, n;
int64_t const MAX = 200001;

std::vector<std::vector<int64_t>> edges(MAX);
std::vector<bool> dead(MAX, false);
std::vector<std::vector<int64_t> > up(MAX);
std::vector<int64_t> parent(MAX);
std::vector<int64_t> depth(MAX);
std::vector<int64_t> counter;
std::vector<int64_t> r(MAX);
std::vector<int64_t> alive(MAX);


void dfs(int64_t v, int64_t p, int64_t d) {
    up[v][0] = p;
    depth[v] = d;
    for (int64_t i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to: edges[v])
        dfs(to, v, d + 1);
}

int64_t find_set(int64_t v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int64_t a, int64_t b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (r[a] < r[b]) {
            int64_t temp = a;
            a = b;
            b = temp;
        }
        parent[b] = a;
        if (r[a] == r[b])
            ++r[a];
    }
}

void check(int64_t v) {
    parent[v] = v;
    r[v] = 0;
    for (auto child: edges[v])
        if (dead[child])
            union_sets(child, v);
    alive[find_set(v)] = up[v][0];
    if (dead[up[v][0]]) {
        int64_t temp = alive[find_set(up[v][0])];
        union_sets(v, up[v][0]);
        alive[find_set(v)] = temp;
    }
}

int64_t lca(int64_t v, int64_t u) {
    if (depth[v] > depth[u]) {
        int64_t temp = u;
        u = v;
        v = temp;
    }
    for (int64_t i = l; i >= 0; --i)
        if (depth[u] - depth[v] >= counter[i])
            u = up[u][i];
    if (v == u)
        return v;
    for (int64_t i = l; i >= 0; --i)
        if (up[v][i] != up[u][i] && depth[up[v][i]] == depth[up[u][i]]) {
            v = up[v][i];
            u = up[u][i];
        }
    return dead[up[v][0]] ? alive[find_set(up[v][0])] : up[v][0];
}

void add(int64_t parent, int64_t child) {
    depth[child] = depth[parent] + 1;
    up[child][0] = parent;
    for (int64_t i = 1; i <= l; ++i) {
        up[child][i] = up[up[child][i - 1]][i - 1];
    }
}

int main() {
    std::cin >> n;
    l = 1;
    while ((1 << l) <= n)
        ++l;
    ++l;
    for (int64_t i = 0; i < MAX; ++i)
        alive[i] = i;
    for (int64_t i = 0; i <= l; ++i)
        counter.push_back(1 << i);
    for (int64_t i = 0; i < n; ++i)
        up[i].resize(l + 1);
    dfs(0, 0, 1);

    std::string s;
    int64_t numb = 1;
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> s;
        if (s == "+") {
            int64_t v;
            std::cin >> v;
            edges[--v].push_back(numb);
            add(v, numb);
            ++numb;
        } else if (s == "-") {
            int64_t v;
            std::cin >> v;
            dead[--v] = true;
            check(v);
        } else {
            int64_t v = 0, u = 0;
            std::cin >> v >> u;
            std::cout << lca(--v, --u) + 1 << '\n';
        }
    }


    return 0;
}
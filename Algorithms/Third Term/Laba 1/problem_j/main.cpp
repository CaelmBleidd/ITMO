#include <iostream>
#include <vector>

std::vector<int64_t> p;
int64_t n, m;

struct Node {
    Node(int64_t v = 0, int64_t u = 0, int64_t weight = 0) : v(v), u(u), weight(weight) {}

    int64_t v, u, weight;
};

void make_set() {
    for (uint64_t i = 0; i < n; ++i) {
        p[i] = i;
    }
}

int64_t get(int64_t v) {
    if (v == p[v])
        return v;
    else {
        p[v] = get(p[v]);
        return p[v];
    }
}

void unionn(int64_t a, int64_t b) {
    a = get(a);
    b = get(b);
    if (a != b)
        p[a] = b;
}

template<typename T>
T sqr(T amount) {
    return amount * amount;
}

int main() {
    std::cin >> n >> m;

    int64_t result = 0;
    std::vector<Node> g(m);

    for (uint64_t i = 0; i < m; ++i) {
        int64_t a, b, c;
        std::cin >> a >> b >> c;
        --a;
        --b;
        g[i] = Node(a, b, c);
    }

    std::sort(g.begin(), g.end(), [](Node a, Node b) { return a.weight < b.weight; });
    p.resize(n);
    make_set();
    for (auto i : g) {
        if (get(i.u) != get(i.v)) {
            unionn(i.v, i.u);
            result += i.weight;
        }
    }

    std::cout << result;

    return 0;
}
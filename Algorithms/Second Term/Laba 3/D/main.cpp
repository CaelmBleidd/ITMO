//#include <iostream>
//#include <vector>
//
//int64_t n, m;
//int64_t MAX_N = 2*100000 + 50;
//std::vector< std::vector<int64_t> > edges(MAX_N);
//std::vector<int64_t> centroidDecomp(MAX_N);
//std::vector<int64_t> level(MAX_N, -1);
//void input() {
//
//}
//
//int64_t dfsCounting(int64_t v, int64_t size, int64_t &centroid, int64_t p = -1) {
//    int64_t s = 1;
//    for (auto to: edges[v])
//        if (level[to] == -1 && to != p)
//            s += dfsCounting(to, size, centroid, v);
//    if (centroid == -1 && (2 * s >= size || p == -1))
//        centroid = v;
//    return s;
//}
//
//void dfs(int64_t v, int64_t size, int64_t depth, int64_t last) {
//    int64_t centroid = -1;
//    dfsCounting(v, size, centroid);
//    level[centroid] = depth;
//    centroidDecomp[centroid] = last;
//    for (auto to: edges[centroid])
//        if (level[to] == -1)
//            dfs(to, size / 2, depth + 1, centroid);
//}
//
//void solve() {
//    dfs(0, n, 0, -1);
//}
//
//void output() {
//    for (int64_t i = 0; i < n; ++i)
//        out << centroidDecomp[i] + 1<< " ";
//}
//
//int64_t main() {
//    std::cin >> n;
//    int64_t v = 0, u = 0;
//    for (int64_t i = 0; i < n - 1; ++i) {
//        std::cin >> v >> u;
//        edges[--v].push_back(--u);
//        edges[u].push_back(v);
//    }
//    solve();
//    output();
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define in cin
#define out cout

//ifstream in("input.txt");
//ofstream out("output.txt");

int n, m;
int MAX_N = 2*100000 + 50;
vector< vector<int> > edges(MAX_N);
vector<int> centroidDecomp(MAX_N);
vector<int> level(MAX_N, -1);
void input() {
    in >> n;
    int v, u;
    for (int i = 0; i < n - 1; ++i) {
        in >> v >> u;
        --v;
        --u;
        edges[v].push_back(u);
        edges[u].push_back(v);
    }
}

int dfsCounting(int v, int size, int &centroid, int p = -1) {
    int s = 1;
    for (auto to: edges[v])
        if (level[to] == -1 && to != p)
            s += dfsCounting(to, size, centroid, v);
    if (centroid == -1 && (2 * s >= size || p == -1))
        centroid = v;
    return s;
}

void dfs(int v, int size, int depth, int last) {
    int centroid = -1;
    dfsCounting(v, size, centroid);
    level[centroid] = depth;
    centroidDecomp[centroid] = last;
    for (auto to: edges[centroid])
        if (level[to] == -1)
            dfs(to, size / 2, depth + 1, centroid);
}

void solve() {
    dfs(0, n, 0, -1);
}

void output() {
    for (int i = 0; i < n; ++i)
        out << centroidDecomp[i] + 1<< " ";
}

int main() {
    input();
    solve();
    output();
    return 0;
}
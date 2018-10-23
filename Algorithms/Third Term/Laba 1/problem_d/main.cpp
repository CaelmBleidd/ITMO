#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <stack>

uint64_t n, m;
std::vector<std::vector<uint64_t>> graph;
std::map<uint64_t, std::pair<uint64_t, uint64_t>> edges;
std::vector<bool> used;
std::vector<uint64_t> time_in;
std::vector<uint64_t> fun;
std::stack<uint64_t> cur_component;
std::vector<uint64_t> colors;

uint64_t cur_color = 0;
uint64_t timer = 0;

void read_undirected_graph() {
    std::cin >> n >> m;

    graph.resize(n + 1);
    time_in.resize(n + 1);
    fun.resize(n + 1);
    colors.assign(n + 1, 0);
    used.assign(n + 1, false);

    for (uint64_t i = 1; i <= m; ++i) {
        uint64_t vertex_1, vertex_2;
        std::cin >> vertex_1 >> vertex_2;
        graph[vertex_1].push_back(i);
        graph[vertex_2].push_back(i);
        edges[i] = std::make_pair(vertex_1, vertex_2);
    }
}

void paint(uint64_t vertex) {
    ++cur_color;
    uint64_t cur_vertex = 0;
    while(cur_vertex != vertex && !cur_component.empty()) {
        colors[cur_component.top()] = cur_color;
        cur_vertex = cur_component.top();
        cur_component.pop();
    }
}

void dfs(uint64_t vertex, uint64_t from_edge) {
    used[vertex] = true;
    ++timer;
    time_in[vertex] = fun[vertex] = timer;
    cur_component.push(vertex);

    for (uint64_t cur_edge: graph[vertex]) {
        if (cur_edge == from_edge)
            continue;
        auto edge = edges[cur_edge];
        auto u = edge.first;
        if (u == vertex)
            u = edge.second;
        if (used[u] == 1)
            fun[vertex] = std::min(fun[vertex], time_in[u]);
        else {
            dfs(u, cur_edge);
            fun[vertex] = std::min(fun[vertex], fun[u]);
            if (time_in[vertex] < fun[u])
                paint(u);
        }
    }

}


int main() {
    read_undirected_graph();
    for (uint64_t i = 1; i <= n; ++i) {
        if (used[i] == 0) {
            dfs(i, 0);
            paint(i);
        }
    }

    std::cout << cur_color << '\n';
    for(uint64_t i = 1; i <=n; ++i) {
        std::cout << colors[i] << ' ';
    }

    return 0;
}
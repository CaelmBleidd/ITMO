#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>

uint64_t n, m;
std::vector<std::vector<uint64_t>> graph;
std::map<uint64_t, std::pair<uint64_t, uint64_t>> edges;
std::vector<bool> used;
std::vector<uint64_t> time_in;
std::vector<uint64_t> fun;
std::vector<uint64_t> colors;

uint64_t max_color = 0;
uint64_t timer = 0;



void read_undirected_graph() {
    std::cin >> n >> m;

    graph.resize(n + 1);
    time_in.resize(n + 1);
    fun.resize(n + 1);
    colors.assign(m + 1, 0);
    used.assign(n + 1, false);

    for (uint64_t i = 1; i <= m; ++i) {
        uint64_t vertex_1, vertex_2;
        std::cin >> vertex_1 >> vertex_2;
        graph[vertex_1].push_back(i);
        graph[vertex_2].push_back(i);
        edges[i] = std::make_pair(vertex_1, vertex_2);
    }
}



void paint(uint64_t vertex, uint64_t from_edge, uint64_t color) {
    used[vertex] = true;
    for (uint64_t cur_edge: graph[vertex]) {
        if (cur_edge == from_edge)
            continue;
        auto edge = edges[cur_edge];
        auto u = edge.first;
        if (u == vertex)
            u = edge.second;
        if (!used[u]) {
            if (time_in[vertex] <= fun[u]) {
                colors[cur_edge] = ++max_color;
                paint(u, cur_edge, max_color);
            } else {
                colors[cur_edge] = color;
                paint(u, cur_edge, color);
            }
        } else if (time_in[vertex] > time_in[u]) {
            colors[cur_edge] = color;
        }
    }
}




void dfs(uint64_t vertex, uint64_t from_edge) {
    used[vertex] = true;
    ++timer;
    time_in[vertex] = fun[vertex] = timer;

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
        }
    }
}


int main() {
    read_undirected_graph();

    for (uint64_t i = 1; i <= n; ++i) {
        if (used[i] == 0) {
            dfs(i, 0);
        }
    }
    used.assign(n + 1, false);
    
    for (uint64_t i = 1; i <= n; ++i) {
        if (!used[i]) {
            paint(i, 0, max_color );
        }
    }

    std::cout << max_color << '\n';
    for(uint64_t i = 1; i <= m; ++i) {
        std::cout << colors[i] << ' ';
    }

    return 0;
}
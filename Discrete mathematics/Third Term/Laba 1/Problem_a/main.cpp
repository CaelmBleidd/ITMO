#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

int64_t n = 0;

std::vector<std::vector<int64_t>> graph;
std::deque<uint64_t> queue;

void read_graph() {
    std::string number;
    std::getline(std::cin, number);
    n = std::stoll(number);

    graph.assign(n + 1, std::vector<int64_t>(n + 1, 0));

    for (auto i = 1; i < n + 1; ++i) {
        std::string buffer;
        std::getline(std::cin, buffer);
        uint64_t position = 1;
        for (char j : buffer) {
            graph[i][position ] = j - '0';
            graph[position++][i] = j - '0';
        }
    }

    for (uint64_t i = 0; i < n; ++i) {
        queue.push_back(i + 1);
    }
}


void find_hamiltonian_cycle() {
    int64_t start = 0;
    int64_t changes = 0;
    for (auto i: queue)
        std::cout << i << ' ';
    std::cout << '\n';
    for (auto k = 0; k < n * (n - 1); ++k) {
        if (graph[*queue.begin()][*(queue.begin() + 1)] == 0) {
            int64_t i = 2;
            while (graph[*queue.begin()][*(queue.begin() + i)] == 0 || graph[*(queue.begin() + 1)][*(queue.begin() + i + 1)] == 0) {
                ++i;
            }
            std::reverse(queue.begin() + 1, queue.begin() + i + 1);
        }
        queue.push_back(queue.front());
        queue.pop_front();

    }
}

int main() {
//    std::freopen("fullham.in", "r", stdin);
//    std::freopen("fullham.out", "w", stdout);

    read_graph();
    find_hamiltonian_cycle();
    for (auto i : queue) {
        std::cout << i << ' ';
    }
    return 0;
}
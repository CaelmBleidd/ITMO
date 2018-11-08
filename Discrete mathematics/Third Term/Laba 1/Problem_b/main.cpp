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

    graph.assign(n , std::vector<int64_t>(n , 0));

    for (auto i = 0; i < n; ++i) {
        std::string buffer;
        std::getline(std::cin, buffer);
        uint64_t position = 0;
        for (char j : buffer) {
            graph[i][position ] = j - '0';
            graph[position++][i] = j - '0';
        }
    }

    for (uint64_t i = 0; i < n; ++i) {
        queue.push_back(i);
    }
}

void maine_swap(int64_t v, int64_t u) {
    auto tmp = queue[v % n];
    queue[v % n] = queue[u % n];
    queue[u % n] = tmp;
}

void find_hamiltonian_cycle() {
    int64_t start = 0;
    int64_t changes = 0;
    for (auto k = 0; k < n * (n - 1); ++k, ++start) {
        if (graph[queue[start % n] %  (n)][queue[(start + 1) % n] % (n)] == 0) {
            int64_t left = start + 1, i = start + 2;
            while (i - start != n && (graph[queue[start % n]][queue[i % n]] == 0 || graph[queue[(start + 1) % n]][queue[(i + 1) % n]] == 0)) {
                ++i;
            }
            if (i - start == n) {
                i = start + 2;
                while (graph[queue[start % n]][queue[i % n]] == 0)
                    ++i;
            }
            while (left <= i) {
                maine_swap(left, i);
                ++left;
            }
            changes = 0;
        } else if (++changes > n)
            break;
    }
}

int main() {
    std::freopen("chvatal.in", "r", stdin);
    std::freopen("chvatal.out", "w", stdout);

    read_graph();
    find_hamiltonian_cycle();
    for (auto i : queue) {
        std::cout << i + 1 << ' ';
    }
    return 0;
}
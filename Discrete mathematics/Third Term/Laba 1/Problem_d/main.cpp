#include <iostream>
#include <vector>
#include <deque>

int64_t n = 0;

std::deque<int64_t> answer;
std::vector<std::vector<int64_t>> graph;

void read_graph() {
    std::string number;
    std::getline(std::cin, number);
    n = std::stoll(number);

    graph.assign(n + 1, std::vector<int64_t>(n + 1, 0));

    for (auto i = 1; i <= n; ++i) {
        std::string buffer;
        std::getline(std::cin, buffer);
        for (int u = 0; u < buffer.size(); ++u) {
            if (buffer[u] == '1') {
                graph[i][u + 1] = 1;
            } else
                graph[u + 1][i] = 1;
        }
    }

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("guyaury.in", "r", stdin);
    std::freopen("guyaury.out", "w", stdout);

    read_graph();

    answer.push_back(1);


    for (int v = 2; v <= n; ++v) {
        auto it = answer.begin();
        while (it != answer.end() && graph[*it][v]) {
            ++it;
        }
        answer.insert(it, v);
    }

    int64_t first = (int64_t)answer.size() - 1;
    while (first >= 2) {
        if (graph[answer[first--]][answer[0]] == 1)
            break;
    }

    std::deque<int64_t> cycle;

    for (auto i = 0; i < first + 1; ++i) {
        cycle.push_back(answer[i]);
    }
    for (auto i = 0; i < first + 1; ++i) {
        answer.pop_front();
    }

    for (auto st = 0; st < answer.size();) {
        auto pp = 0;
        while (pp < cycle.size() && graph[cycle[pp]][answer[st]])
            ++pp;
        if (pp < cycle.size()) {
            cycle.insert(cycle.begin() + pp, answer.begin(), answer.begin() + st + 1);
            for (auto i = 0; i < st + 1; ++i) {
                answer.pop_front();
            }
            st = 0;
        } else {
            ++st;
        }
    }

    for (auto i: cycle)
        std::cout << i << ' ';
    return 0;
}
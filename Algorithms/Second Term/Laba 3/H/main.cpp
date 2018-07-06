#include <iostream>
#include <unordered_map>
#include <vector>

void merge(std::unordered_map<int64_t, bool> &first, std::unordered_map<int64_t, bool> &second) {
    if (first.size() < second.size())
        first.swap(second);
    for (auto i : second) {
        first.insert(i);
    }
    second.clear();
}

void dfs(int64_t vertice, std::vector<std::vector<int64_t>> &array, std::vector<int64_t> &color,
         std::vector<std::unordered_map<int64_t, bool>> &s, std::vector<int64_t> &res) {

    s[vertice][color[vertice]] = true;
    for (int64_t i = 0; i < array[vertice].size(); ++i) {
        auto to = array[vertice][i];
        dfs(to, array, color, s, res);
        merge(s[vertice], s[to]);
    }
    res[vertice] = s[vertice].size();
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int64_t n = 0;
    std::cin >> n;

    std::vector<std::vector<int64_t>> array(n + 1);
    std::vector<int64_t> color(n + 1);
    std::vector<std::unordered_map<int64_t, bool>> s(n + 1);

    for (uint64_t i = 1; i <= n; ++i) {
        int64_t parent = 0, col = 0;
        std::cin >> parent >> col;
        array[parent].push_back(i);
        color[i] = col;
    }

    std::vector<int64_t> res(n + 1);

    dfs(0, array, color, s, res);

    for (uint64_t i = 1; i < n + 1; ++i) {
        std::cout << res[i] << ' ';
    }

    return 0;
}
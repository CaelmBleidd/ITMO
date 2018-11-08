#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
#include <list>

int64_t n = 0;

std::list<int64_t> answer;

bool request(int64_t v, int64_t u) {
    std::cout << 1 << " " << v + 1 << ' ' << u + 1 << '\n';
    std::cout.flush();
    std::string tmp;
    std::cin >> tmp;
    return tmp == "YES";
}

void set(int64_t pos, int64_t elem) {
    auto it = answer.begin();
    for (int i = 0; i < pos; ++i)
        ++it;
    answer.insert(it, elem);
}

int64_t get(int64_t pos) {
    auto it = answer.begin();
    for (int i = 0; i < pos; ++i) ++it;
    return *it;
}

void bin_search(int64_t left, int64_t right, int64_t insert) {
    if (left == right) {
        set(left, insert);
    } else if (request(insert - 1, get((left + right) / 2) - 1))
        bin_search(left, (left + right) / 2, insert);
    else
        bin_search(((left + right) / 2) + 1, right, insert);
}


int main() {

    std::cin >> n;
    answer.push_back(1);
    if (n > 1) {
        if (request(0, 1))
            set(1, 2);
        else
            set(0, 2);
        while (answer.size() < n)
            bin_search(0, answer.size(), answer.size() + 1);
    }
    std::cout << "0 ";
    for (auto i : answer)
        std::cout << i << ' ';

    return 0;
}

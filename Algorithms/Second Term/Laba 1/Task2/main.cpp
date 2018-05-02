#include <iostream>
#include <vector>
#include <cmath>

void build(const std::vector<int64_t> &source, std::vector<int64_t> &tree, size_t tmp, size_t left, size_t right);

int64_t sum(std::vector<int64_t> &tree, size_t tmp, size_t to_left, size_t to_right, size_t act_left, size_t act_right);

void set(std::vector<int64_t> &tree, size_t tmp, size_t to_left, size_t to_right, size_t pos, int64_t value);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("rsq.in", "r", stdin);
    std::freopen("rsq.out", "w", stdout);

    size_t n;
    std::cin >> n;

    std::vector<int64_t> array(n);
    std::vector<int64_t> tree(4 * n);

    for (size_t i = 0; i < n; ++i) {
        int64_t a;
        std::cin >> a;
        array[i] = a;
    }

    build(array, tree, (size_t) 1, (size_t) 0, (size_t) n - 1);

    while (std::cin) {
        std::string command;
        size_t left, right;
        left = right = 0;

        std::cin >> command;
        std::cin >> left;
        std::cin >> right;
        --left;
        --right;

        if (command == "sum") {
            std::cout << sum(tree, 1, 0, n - 1, left, right) << '\n';
        } else {
            set(tree, 1, 0, n - 1, left, right + 1);
        }
    }

    return 0;
}

void build(const std::vector<int64_t> &source, std::vector<int64_t> &tree, size_t tmp, size_t left, size_t right) {
    if (left == right) {
        tree[tmp] = source[left];
    } else {
        size_t middle = (left + right) / 2;
        build(source, tree, tmp * 2, left, middle);
        build(source, tree, tmp * 2 + 1, middle + 1, right);
        tree[tmp] = tree[tmp * 2] + tree[tmp * 2 + 1];
    }
}

int64_t
sum(std::vector<int64_t> &tree, size_t tmp, size_t to_left, size_t to_right, size_t act_left, size_t act_right) {
    if (act_left > act_right)
        return 0;
    if (act_left == to_left && act_right == to_right)
        return tree[tmp];
    size_t middle = (to_left + to_right) / 2;
    return sum(tree, tmp * 2, to_left, middle, act_left, act_right < middle ? act_right : middle) +
           sum(tree, tmp * 2 + 1, middle + 1, to_right, act_left > middle + 1 ? act_left : middle + 1, act_right);

}

void set(std::vector<int64_t> &tree, size_t tmp, size_t to_left, size_t to_right, size_t pos, int64_t value) {
    if (to_left == to_right)
        tree[tmp] = value;
    else {
        size_t middle = (to_left + to_right) / 2;
        if (pos <= middle)
            set(tree, tmp * 2, to_left, middle, pos, value);
        else
            set(tree, tmp * 2 + 1, middle + 1, to_right, pos, value);
        tree[tmp] = tree[tmp * 2] + tree[tmp * 2 + 1];
    }

}
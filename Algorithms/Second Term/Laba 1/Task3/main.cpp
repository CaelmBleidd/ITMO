#include <iostream>
#include <vector>
#include <cmath>

struct Node {
    int64_t value;
    int64_t add_to_value = 0;
    int64_t replace_value = 0;
    bool need_new_value = false;
    int64_t min;
};

size_t size;

void push(std::vector<Node> &tree, size_t actual_root) {
    if (actual_root >= size) {
        tree[actual_root].add_to_value = 0;
        if (tree[actual_root].need_new_value) {
            tree[actual_root].need_new_value = false;
            tree[actual_root].min = tree[actual_root].replace_value;
        }
        return;
    }

    if (tree[actual_root].add_to_value != 0) {
        if (tree[actual_root * 2].need_new_value) {
            tree[actual_root * 2].replace_value += tree[actual_root].add_to_value;
        } else
            tree[actual_root * 2].add_to_value += tree[actual_root].add_to_value;
        tree[actual_root * 2].min += tree[actual_root].add_to_value;
        if (tree[actual_root * 2 + 1].need_new_value) {
            tree[actual_root * 2 + 1].replace_value += tree[actual_root].add_to_value;
        } else
            tree[actual_root * 2 + 1].add_to_value += tree[actual_root].add_to_value;
        tree[actual_root * 2 + 1].min += tree[actual_root].add_to_value;
        tree[actual_root].add_to_value = 0;
    }

    if (tree[actual_root].need_new_value) {
        tree[actual_root * 2].replace_value = tree[actual_root].replace_value;
        tree[actual_root * 2].min = tree[actual_root].replace_value;
        tree[actual_root * 2].need_new_value = true;
        tree[actual_root * 2 + 1].replace_value = tree[actual_root].replace_value;
        tree[actual_root * 2 + 1].min = tree[actual_root].replace_value;
        tree[actual_root * 2 + 1].need_new_value = true;
        tree[actual_root * 2].add_to_value = 0;
        tree[actual_root * 2 + 1].add_to_value = 0;
        tree[actual_root].need_new_value = false;
    }
    tree[actual_root].min = std::min(tree[actual_root * 2].min, tree[actual_root * 2 + 1].min);
}

void add(std::vector<Node> &tree, size_t actual_root, size_t left_bound, size_t right_bound,
         size_t actual_left_bound,
         size_t actual_right_bound, int64_t value) {
    push(tree, actual_root);
    if (actual_right_bound <= left_bound || actual_left_bound >= right_bound)
        return;
    if (actual_left_bound <= left_bound && right_bound <= actual_right_bound) {
        tree[actual_root].add_to_value = value;
        tree[actual_root].min += value;
        return;
    }
    size_t middle = (left_bound + right_bound) / 2;
    add(tree, actual_root * 2, left_bound, middle, actual_left_bound, actual_right_bound, value);
    add(tree, actual_root * 2 + 1, middle, right_bound, actual_left_bound, actual_right_bound, value);
    push(tree, actual_root);
}

void set(std::vector<Node> &tree, size_t actual_root, size_t left_bound, size_t right_bound,
         size_t actual_left_bound, size_t actual_right_bound, int64_t value) {
    push(tree, actual_root);
    if (actual_right_bound <= left_bound || actual_left_bound >= right_bound)
        return;
    if (actual_left_bound <= left_bound && right_bound <= actual_right_bound) {
        tree[actual_root].replace_value = value;
        tree[actual_root].need_new_value = true;
        tree[actual_root].min = value;
        tree[actual_root].add_to_value = 0;
        return;
    }
    size_t middle = (left_bound + right_bound) / 2;
    set(tree, actual_root * 2, left_bound, middle, actual_left_bound, actual_right_bound, value);
    set(tree, actual_root * 2 + 1, middle, right_bound, actual_left_bound, actual_right_bound, value);
    push(tree, actual_root);
}

int64_t minimum(std::vector<Node> &tree, size_t actual_root, size_t left_bound,
                size_t right_bound, size_t actual_left_bound, size_t actual_right_bound) {
    push(tree, actual_root);
    if (actual_right_bound <= left_bound || actual_left_bound >= right_bound)
        return INT64_MAX;
    if (actual_left_bound <= left_bound && right_bound <= actual_right_bound) {
        return tree[actual_root].min;
    }
    size_t middle = (left_bound + right_bound) / 2;
    return std::min(
            minimum(tree, actual_root * 2, left_bound, middle, actual_left_bound, actual_right_bound),
            minimum(tree, actual_root * 2 + 1, middle, right_bound, actual_left_bound, actual_right_bound));
}


int main() {
    std::freopen("rmq2.in", "r", stdin);
    std::freopen("rmq2.out", "w", stdout);

    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    for (size = 1; size < n; size *= 2);

    std::vector<int64_t> source(n);
    std::vector<Node> tree(2 * size);

    for (size_t i = 0; i < n; ++i) {
        int64_t a;
        std::cin >> a;
        source[i] = a;
    }

    for (size_t i = size; i < size + n; i++)
        tree[i].min = source[i - size];
    for (size_t i = size + n; i < 2 * size; i++)
        tree[i].min = INT64_MAX;
    for (size_t i = size - 1; i >= 1; i--)
        tree[i].min = std::min(tree[2 * i].min, tree[2 * i + 1].min);
    for (size_t i = 0; i < 2 * size; i++) {
        tree[i].add_to_value = 0;
        tree[i].need_new_value = false;
    }


    std::string command;
    size_t left = 0, right = 0;
    int64_t value = 0;

    while (std::cin >> command && std::cin >> left && std::cin >> right) {
        if (command == "set") {
            std::cin >> value;
            set(tree, 1, 0, size, left - 1, right, value);
        } else if (command == "add") {
            std::cin >> value;
            add(tree, 1, 0, size, left - 1, right, value);
        } else {
            std::cout << minimum(tree, 1, 0, size, left - 1, right) << '\n';
        }
    }
    return 0;
}

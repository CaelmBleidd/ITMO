#include <iostream>
#include <vector>


void update(std::vector<int64_t> &, size_t);

int64_t find_place(std::vector<int64_t> &tree, size_t actual_root, size_t actual_left_bound, size_t actual_right_bound,
                   size_t left_bound, size_t right_bound);

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);

    size_t n = 0;
    int64_t m = 0;

    std::cin >> n >> m;

    std::string command;
    size_t number_of_place = 0;

    size_t size_of_tree = 1;
    for (size_of_tree = 1; size_of_tree < n; size_of_tree *= 2);

    std::vector<int64_t> tree(size_of_tree * 2);

    int64_t p = 1;

    for (size_t i = size_of_tree; i < size_of_tree + n; ++i)
        tree[i] = p++;

    for (size_t i = size_of_tree + n; i < size_of_tree * 2; ++i)
        tree[i] = INT64_MAX;

    for (size_t i = size_of_tree - 1; i >= 1; --i) {
        tree[i] = std::min(tree[i * 2], tree[i * 2 + 1]);
    }

    while (m-- > 0) {
        std::cin >> command >> number_of_place;
        if (command == "exit") {
            tree[number_of_place + size_of_tree - 1] = number_of_place;
            update(tree, number_of_place + size_of_tree - 1);
        } else {
            int64_t place = find_place(tree, 1, number_of_place - 1, size_of_tree - 1, 0, size_of_tree - 1);
            if (place == INT64_MAX)
                place = find_place(tree, 1, 0, number_of_place - 1, 0, size_of_tree - 1);
            tree[size_of_tree + place - 1] = INT64_MAX;
            update(tree, size_of_tree + place - 1);
            std::cout << place << '\n';

        }
    }

    return 0;
}

void update(std::vector<int64_t> &tree, size_t actual_root) {
    if (actual_root == 1) {
        tree[1] = std::min(tree[2], tree[3]);
        return;
    }
    tree[actual_root / 2] = std::min(tree[actual_root / 2 * 2], tree[actual_root / 2 * 2 + 1]);
    update(tree, actual_root / 2);
}

int64_t find_place(std::vector<int64_t> &tree, size_t actual_root, size_t actual_left_bound, size_t actual_right_bound,
                   size_t left_bound, size_t right_bound) {
    if (actual_left_bound > actual_right_bound)
        return INT64_MAX;
    if (actual_left_bound == left_bound && actual_right_bound == right_bound)
        return tree[actual_root];
    size_t middle = (left_bound + right_bound) / 2;
    return std::min(
            find_place(tree, actual_root * 2, actual_left_bound, std::min(actual_right_bound, middle), left_bound,
                       middle),
            find_place(tree, actual_root * 2 + 1, std::max(actual_left_bound, middle + 1), actual_right_bound,
                       middle + 1, right_bound));
}

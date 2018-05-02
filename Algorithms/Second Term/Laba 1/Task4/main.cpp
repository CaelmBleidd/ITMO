#include <iostream>
#include <vector>
#include <cmath>

struct Request {
    char color;
    int64_t x, l;
};

struct Node {
    int64_t length = 0;
    int64_t number = 0;
    int64_t color = 0; // -1 == смешанный, 0 - белый, 1 - чёрный (хыч-хыч)
};

size_t size;

void set(std::vector<Node> &tree, size_t actual_root, size_t actual_left, size_t actual_right, size_t left_bound,
         size_t right_bound, int64_t value) {
    if (actual_left > actual_right)
        return;
    if (actual_left == left_bound && actual_right == right_bound) {
        tree[actual_root].number = value == 1 ? 1 : 0;
        if (actual_left == actual_right)
            tree[actual_root].length = value == 1 ? 1 : 0;
        else
            tree[actual_root].length = value == 1 ? (int64_t) actual_right - actual_left : 0;
        tree[actual_root].color = value;
        return;
    }
    if (tree[actual_root].color == value) {
        return;
    }
    tree[actual_root].color = -1;
    size_t middle = (left_bound + right_bound) / 2;
    set(tree, actual_root * 2, actual_left, std::min(actual_right, middle), left_bound, middle, value);
    set(tree, actual_root * 2 + 1, std::max(middle + 1, actual_left), actual_right, middle + 1, right_bound, value);
    tree[actual_root].length = tree[actual_root * 2].length + tree[actual_root * 2 + 1].length;
    tree[actual_root].number = tree[actual_root * 2].number + tree[actual_root * 2 + 1].number;

    // нам нужно идти до того сына, который будет равен 1 или 0, тогда можем спокойно зайти в его левого/правого
    int64_t left_actual_root = actual_root * 2;
    int64_t right_actual_root = actual_root * 2 + 1;

    int64_t one_more_left;
    int64_t one_more_right;
    while (
            (tree[left_actual_root].color != 0 && tree[left_actual_root].color != 1))
        left_actual_root = left_actual_root * 2 + 1;  // самый правый лист левого сына, все поддеревья которого покрашены в один цвет
    while ((tree[right_actual_root].color != 0 && tree[right_actual_root].color != 1))
        right_actual_root = right_actual_root * 2;  // самый левый лист правого сына, все поддеревья которого покрашены в один цвет

    one_more_left = left_actual_root;
    one_more_right = right_actual_root;

    while(one_more_left * 2 + 1 < 2 * size) {
        one_more_left = one_more_left * 2 + 1;
    }

    while(one_more_right * 2 < 2 * size) {
        one_more_right *= 2;
    }


    if (tree[left_actual_root].color == 1 && tree[right_actual_root].color == 1 && one_more_left >= actual_left + size && one_more_right <= actual_right + size) {
        tree[actual_root].number -= 1;
        tree[actual_root].length += 1;
    }

    if (tree[actual_root * 2].color == tree[actual_root * 2 + 1].color)
        tree[actual_root].color = tree[actual_root * 2].color;

    return;

}

int main() {
    std::freopen("painter.in", "r", stdin);
    std::freopen("painter.out", "w", stdout);

    int64_t min_coordinate = INT64_MAX;
    int64_t max_coordinate = INT64_MIN;
    int64_t delta = 0;

    size_t n = 0;
    std::cin >> n;

    std::vector<Request> requests(n);

    // считываем все запросы
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> requests[i].color >> requests[i].x >> requests[i].l;
        if (requests[i].x < min_coordinate)
            min_coordinate = requests[i].x;
        if (requests[i].x + requests[i].l > max_coordinate)
            max_coordinate = requests[i].x + requests[i].l;
    }

    // ищем смещение
    if (min_coordinate < 1)
        delta = 1 + std::abs(min_coordinate);
    else
        delta = 0;

    // изменяем во всех реквестах координату
    for (auto i : requests) {
        i.x += delta;
    }

    // размер будущего бинарного дерева

    for (size = 1; size < delta + max_coordinate; size *= 2);

    std::vector<Node> tree(size * 2);

    for (auto i : tree) {   // заполняем дерево
        i.length = 0;
        i.number = 0;
    }


    for (size_t i = 0; i < requests.size(); ++i) {
        int64_t left = requests[i].x - 1;
        int64_t right = requests[i].x + requests[i].l - 1;
        int64_t color = requests[i].color == 'W' ? 0 : 1;
        set(tree, 1, left, right, 0, size - 1, color);
        std::cout << tree[1].number << ' ' << tree[1].length << '\n';
    }


    return 0;
}
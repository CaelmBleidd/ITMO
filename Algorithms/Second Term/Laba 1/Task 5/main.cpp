//#include <iostream>
//#include <vector>
//
//size_t size = 1;
//int64_t r = 1;
//
//struct matrix {
//    int64_t a, b, c, d;
//};
//
//const matrix zero = {1, 0, 0, 1};
//
//matrix multiply(matrix, matrix);
//
//matrix get(std::vector<matrix> &, size_t, size_t, size_t, size_t, size_t);
//
//void print(matrix);
//
//int main() {
//    std::cin.tie(nullptr);
//    std::ios_base::sync_with_stdio(false);
//
//    std::freopen("crypto.in", "r", stdin);
//    std::freopen("crypto.out", "w", stdout);
//
//    size_t n, m;
//    n = m = 0;
//
//    std::cin >> r >> n >> m;
//
//    for (size = 1; size < n; size *= 2);
//
//    std::vector<matrix> tree(2 * size);
//
//    int64_t a, b, c, d;
//    a = b = c = d = 0;
//    for (size_t i = size; i < size + n; ++i) {
//        std::cin >> a >> b >> c >> d;
//        tree[i].a = a;
//        tree[i].b = b;
//        tree[i].c = c;
//        tree[i].d = d;
//    }
//
//    for (size_t i = size + n; i < 2 * size; ++i)
//        tree[i] = zero;
//
//    for (size_t i = size - 1; i >= 1; --i)
//        tree[i] = multiply(tree[2 * i], tree[2 * i + 1]);
//
//    size_t left, right;
//    left = right = 0;
//
//    for (size_t i = 0; i < m; ++i) {
//        std::cin >> left >> right;
//        print(get(tree, 1, 0, size, left - 1, right));
//    }
//
//    return 0;
//}
//
//matrix multiply(matrix first, matrix second) {
//    return {(first.a * second.a + first.b * second.c) % r,
//            (first.a * second.b + first.b * second.d) % r,
//            (first.c * second.a + first.d * second.c) % r,
//            (first.c * second.b + first.d * second.d) % r};
//}
//
//matrix
//get(std::vector<matrix> &tree, size_t actual_root, size_t left_bound, size_t right_bound, size_t actual_left_bound,
//    size_t actual_right_bound) {
//    if (actual_right_bound <= left_bound || actual_left_bound >= right_bound) {
//        return zero;
//    }
//    if (actual_left_bound <= left_bound && right_bound <= actual_right_bound) {
//        return tree[actual_root];
//    }
//    size_t middle = (left_bound + right_bound) / 2;
//    return multiply(
//            get(tree, actual_root * 2, left_bound, middle, actual_left_bound, actual_right_bound),
//            get(tree, actual_root * 2 + 1, middle, right_bound, actual_left_bound, actual_right_bound));
//}
//
//void print(matrix matrix) {
//    std::cout << matrix.a << ' ' << matrix.b << '\n' << matrix.c << ' ' << matrix.d << "\n\n";
//}
//

#include <iostream>
#include <vector>

size_t size = 1;
int64_t r = 1;

struct matrix {
    int64_t a, b, c, d;
};

const matrix zero = {1, 0, 0, 1};

matrix multiply(matrix, matrix);

matrix get(std::vector<matrix> &, size_t, size_t, size_t, size_t, size_t);

void print(matrix);

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::freopen("crypto.in", "r", stdin);
    std::freopen("crypto.out", "w", stdout);

    size_t n, m;
    n = m = 0;

    std::cin >> r >> n >> m;

    for (size = 1; size < n; size *= 2);

    std::vector<matrix> tree(2 * size);

    int64_t a, b, c, d;
    a = b = c = d = 0;
    for (size_t i = size; i < size + n; ++i) {
        std::cin >> a >> b >> c >> d;
        tree[i].a = a;
        tree[i].b = b;
        tree[i].c = c;
        tree[i].d = d;
    }

    for (size_t i = size + n; i < 2 * size; ++i)
        tree[i] = zero;

    for (size_t i = size - 1; i >= 1; --i)
        tree[i] = multiply(tree[2 * i], tree[2 * i + 1]);

    size_t left, right;
    left = right = 0;

    for (size_t i = 0; i < m; ++i) {
        std::cin >> left >> right;
        print(get(tree, 1, 0, size - 1, left - 1, right - 1));
    }

    return 0;
}

matrix multiply(matrix first, matrix second) {
    return {(first.a * second.a + first.b * second.c) % r,
            (first.a * second.b + first.b * second.d) % r,
            (first.c * second.a + first.d * second.c) % r,
            (first.c * second.b + first.d * second.d) % r};
}

matrix
get(std::vector<matrix> &tree, size_t actual_root, size_t left_bound, size_t right_bound, size_t actual_left_bound,
    size_t actual_right_bound) {
    if (actual_left_bound > actual_right_bound)
        return zero;
    if (actual_left_bound == left_bound && actual_right_bound == right_bound)
        return tree[actual_root];
    size_t middle = (left_bound + right_bound) / 2;
    return multiply(
            get(tree, actual_root * 2, left_bound, middle, actual_left_bound, std::min(actual_right_bound, middle)),
            get(tree, actual_root * 2 + 1, middle + 1, right_bound, std::max(actual_left_bound, middle + 1),
                actual_right_bound));
}

void print(matrix matrix) {
    std::cout << matrix.a << ' ' << matrix.b << '\n' << matrix.c << ' ' << matrix.d << "\n\n";
}
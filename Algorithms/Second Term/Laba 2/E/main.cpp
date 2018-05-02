#include <iostream>
#include <random>


size_t size_of_tree = 0;

int64_t get_random(int64_t left, int64_t right) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int64_t> uniform_dist(left, right);
    return uniform_dist(e1);
}

struct Node {
public:
    int64_t value;
    int64_t key;
    size_t size;
    int64_t sum;
    Node *left;
    Node *right;
    int64_t min;
    int64_t max;

    Node(int64_t value) {
        size = 1;
        key = get_random(1, INT64_MIN);
        this->value = value;
        left = nullptr;
        right = nullptr;
        sum = value;
        min = value;
        max = value;
    }

    void set_left(Node *node) {
        left = node;
        recalc();
    }

    void set_right(Node *node) {
        right = node;
        recalc();
    }

    void recalc() {
        size = 1;
        sum = value;
        min = max = value;
        if (left != nullptr) {
            size += left->size;
            sum += left->sum;
            min = std::min(min, left->min);
            max = std::max(max, left->max);
        }
        if (right != nullptr) {
            size += right->size;
            sum += right->sum;
            min = std::min(min, right->min);
            max = std::max(max, right->max);
        }
    }

};


std::pair<Node *, Node *> split(Node *root, int64_t value) {
    if (root == nullptr)
        return std::pair<Node *, Node *>(nullptr, nullptr);
    if (root->value < value) {
        std::pair<Node *, Node *> splited_node = split(root->right, value);
        root->set_right(splited_node.first);
        return std::pair<Node *, Node *>(root, splited_node.second);
    } else {
        std::pair<Node *, Node *> splited_node = split(root->left, value);
        root->set_left(splited_node.second);
        return std::pair<Node *, Node *>(splited_node.first, root);
    }
}

Node *append(Node *root, Node *node) {
    if (root == nullptr)
        return node;

    if (root->key < node->key) {
        std::pair<Node *, Node *> splited_node = split(root, node->value);
        node->set_left(splited_node.first);
        node->set_right(splited_node.second);
        return node;
    }

    if (root->value < node->value) {
        root->set_right(append(root->right, node));
    } else {
        root->set_left(append(root->left, node));
    }
    return root;
}

int64_t summa(Node *root, int64_t left_bound, int64_t right_bound) {
    if (root == nullptr)
        return 0;
    if (left_bound > right_bound)
        return 0;
    int64_t sum = 0;
    if (left_bound <= root->min && root->max <= right_bound)
        return root->sum;
    sum = summa(root->left, left_bound, right_bound < root->value ? right_bound : root->value) +
          summa(root->right, left_bound > root->value ? left_bound : root->value, right_bound);
    if (root->value >= left_bound && root->value <= right_bound)
        sum += root->value;
    return sum;
}

bool exists(Node *p, int64_t value) {
    if (p == nullptr)
        return false;
    if (value == p->value)
        return true;
    if (value < p->value) {
        if (p->left == nullptr)
            return false;
        return exists(p->left, value);
    } else if (value > p->value) {
        if (p->right == nullptr)
            return false;
        return exists(p->right, value);
    }
}

Node *merge(Node *a, Node *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    if (a->key > b->key) {
        a->set_right(merge(a->right, b));
        return a;
    } else {
        b->set_left(merge(a, b->left));
        return b;
    }
}


Node *remove(Node *root, int64_t value) {
    if (root == nullptr) return nullptr;

    if (root->value == value) {
        Node *node = merge(root->left, root->right);
        delete root;
        return node;
    }

    if (root->value < value) {
        root->set_right(remove(root->right, value));
    } else {
        root->set_left(remove(root->left, value));
    }
    return root;
}


Node *kth(Node *root, int64_t k) {
    int64_t leftSize = 0;
    if (root->left != nullptr) leftSize = root->left->size;
    if (leftSize >= k) return kth(root->left, k);
    if (leftSize + 1 == k) return root;
    return kth(root->right, k - leftSize - 1);
}


int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int64_t last_result = 0;
    size_t n = 0;
    std::cin >> n;
    int64_t left, right, value;
    left = right = value = 0;
    char operation;
    char last_operation;

    Node *root = nullptr;

    for (size_t i = 0; i < n; ++i) {
        std::cin >> operation;

        if (root == nullptr && operation == '+') {
            std::cin >> value;
            root = new Node(value);
            ++size_of_tree;
            last_operation = '+';
            continue;
        }

        switch (operation) {
            case '+':
                std::cin >> value;

                if (last_operation == '+') {
                    if (!exists(root, value))
                        root = append(root, new Node(value));
                } else {
                    value = (value + last_result) % 1000000000;
                    if (!exists(root, value))
                        root = append(root, new Node(value));
                }
                last_operation = '+';
                break;
            case '?':
                std::cin >> left >> right;
                last_result = summa(root, left, right);
                std::cout << last_result << '\n';
                last_operation = '?';
                break;
        }
    }

    return 0;
}
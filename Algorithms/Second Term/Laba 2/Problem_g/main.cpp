#include <iostream>
#include <vector>
#include <random>

int64_t get_random(int64_t left, int64_t right) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int64_t> uniform_dist(left, right);
    return uniform_dist(e1);
}

struct Node {
    Node *parent;
    Node *left;
    Node *right;
    int64_t value;
    int64_t key;
    size_t size;

    Node(int64_t value) {
        this->value = value;
        this->key = get_random(1, INT64_MAX);
        right = left = parent = nullptr;
    }

    size_t update_size(Node *&root) {
        size_t count = 0;
        if (root->left != nullptr) {
            count += root->left->size;
        }
        if (root->right != nullptr)
            count += root->right->size;
        count += 1;
        root->size = count;
        return count;
    }

};

size_t drisnya_s_plokhim_vremenem(Node *&root) {
    size_t count = 0;
    if (root->left != nullptr) {
        count += drisnya_s_plokhim_vremenem(root->left);
    }
    if (root->right != nullptr)
        count += drisnya_s_plokhim_vremenem(root->right);
    count += 1;
    root->size = count;
    return count;
}

void split(Node *root, Node *&first_drisnya, Node *&second_drisya, int64_t value) {
    if (root == nullptr) {
        first_drisnya = second_drisya = nullptr;
        return;
    }

    size_t left = root->left == nullptr ? 0 : root->left->size;

    if (value <= left) {
        split(root->left, first_drisnya, root->left, value);
        second_drisya = root;
    } else {
        split(root->right, root->right, second_drisya, value - left - 1);
        first_drisnya = root;
    }
    if (first_drisnya != nullptr) first_drisnya->update_size(first_drisnya);
    if (second_drisya != nullptr) second_drisya->update_size(second_drisya);
}

void merge(Node *&first_drisnya, Node *&second_drisya, Node *&root) {
    if (first_drisnya == nullptr || second_drisya == nullptr) {
        root = first_drisnya == nullptr ? second_drisya : first_drisnya;
        return;
    }
    if (first_drisnya->key > second_drisya->key) {
        merge(first_drisnya->right, second_drisya, first_drisnya->right);
        root = first_drisnya;
    } else {
        merge(first_drisnya, second_drisya->left, second_drisya->left);
        root = second_drisya;
    }
    if (root != nullptr) root->update_size(root);
}


void print(Node *&root) {
    if (root->left != nullptr)
        print(root->left);
    std::cout << root->value << ' ';
    if (root->right != nullptr)
        print(root->right);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    size_t i = 0;

    Node *root = new Node(1);
    Node *last = root;
    i = 1;

    while (i < n) {
        Node *tmp = new Node(i + 1);
        while (true) {
            if (tmp->key <= last->key) {
                if (last->parent != nullptr) {
                    last = last->parent;
                    continue;
                } else {
                    root->parent = tmp;
                    tmp->left = root;
                    tmp->parent = tmp->right = nullptr;
                    last = tmp;
                    root = tmp;
                    break;
                }
            } else {
                tmp->left = last->right;
                if (tmp->left != nullptr)
                    tmp->left->parent = tmp;
                last->right = tmp;
                tmp->parent = last;
                tmp->right = nullptr;
                last = tmp;
                break;
            }
        }
        ++i;
    }

    root->size = drisnya_s_plokhim_vremenem(root);
    // построили дерево за линию, дальше можно забить на parent и прочую дрисню


    for (size_t i = 0; i < m; ++i) {
        size_t left, right;
        std::cin >> left >> right;
        left -= 1;
        Node *first_drisnya;
        Node *second_drisya;
        Node *mozhet_third_drisnya_mmmmmm;
        split(root, second_drisya, mozhet_third_drisnya_mmmmmm, right);
        split(second_drisya, first_drisnya, second_drisya, left);
        merge(second_drisya, first_drisnya, second_drisya);
        merge(second_drisya, mozhet_third_drisnya_mmmmmm, root);
    }

    print(root);

    return 0;
}
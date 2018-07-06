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

    Node *left;
    Node *right;

    Node (int64_t value) {
        size = 1;
        key = get_random(1, INT64_MIN);
        this->value = value;
        left = nullptr;
        right = nullptr;
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
        if (left != nullptr)
            size += left->size;
        if (right != nullptr)
            size += right->size;
    }

};


std::pair<Node *, Node *>  split(Node *root, int64_t value) {
    if (root == nullptr)
        return std::pair<Node *, Node *> (nullptr, nullptr);

    if (root->value < value) {
        std::pair<Node *, Node *>  splited_node = split(root->right, value);
        root->set_right(splited_node.first);
        return std::pair<Node *, Node *> (root, splited_node.second);
    }
    else {
        std::pair<Node *, Node *>  splited_node = split(root->left, value);
        root->set_left(splited_node.second);
        return std::pair<Node *, Node *> (splited_node.first, root);
    }
}

Node* insert(Node *root, Node *node) {
    if (root == nullptr)
        return node;

    if (root->key < node->key) {
        std::pair<Node *, Node *>  splited_node = split(root, node->value);
        node->set_left(splited_node.first);
        node->set_right(splited_node.second);
        return node;
    }

    if (root->value < node->value) {
        root->set_right(insert(root->right, node));
    }
    else {
        root->set_left(insert(root->left, node));
    }
    return root;
}

Node* merge(Node *a, Node *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    if (a->key > b->key) {
        a->set_right(merge(a->right, b));
        return a;
    }
    else {
        b->set_left(merge(a, b->left));
        return b;
    }
}

Node* erase(Node* root, int64_t value) {
    if (root == nullptr) return nullptr;

    if (root->value == value) {
        Node *node = merge(root->left, root->right);
        delete root;
        return node;
    }

    if (root->value < value) {
        root->set_right(erase(root->right, value));
    }
    else {
        root->set_left(erase(root->left, value));
    }
    return root;
}


Node* kth(Node* root, int64_t k) {
    int64_t leftSize = 0;
    if (root->left != nullptr) leftSize = root->left->size;
    if (leftSize >= k) return kth(root->left, k);
    if (leftSize + 1 == k) return root;
    return kth(root->right, k - leftSize - 1);
}


int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);


    size_t n = 0;
    std::cin >> n;

    Node *root = nullptr;

    for (size_t i = 0; i < n; ++i) {
        int64_t first, second;
        first = second = 0;
        std::cin >> first >> second;

        if (root == nullptr) {
            root = new Node(second);
            ++size_of_tree;
            continue;
        }

        switch (first) {
            case -1:
                root = erase(root, second);
                --size_of_tree;
                break;
            case 1:
                root = insert(root, new Node(second));
                ++size_of_tree;
                break;
            default:
                Node* value = kth(root, size_of_tree - second + 1);
                std::cout << value->value << '\n';
                break;
        }
    }

    return 0;
}
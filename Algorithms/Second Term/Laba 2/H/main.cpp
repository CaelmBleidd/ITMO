#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

int64_t get_random(int64_t left, int64_t right) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int64_t> uniform_dist(left, right);
    return uniform_dist(e1);
}

struct Node {
    Node *left;
    Node *right;
    int64_t size;
    std::string value;
    int64_t key;

    Node() {
        this->right = this->left = nullptr;
        this->size = 0;
        this->value = "";
        key = get_random(1, INT64_MAX);
    }

    Node(Node *left, Node *right, int64_t size) {
        this->right = right;
        this->left = left;
        this->size = size;
        this->value = "";
        key = get_random(1, INT64_MAX);
    }

    Node(std::string &value) {
        right = left = nullptr;
        size = value.size();
        this->value = value;
        key = get_random(1, INT64_MAX);
    }

    void recalc() {
        int64_t new_size = 0;
        if (left != nullptr)
            new_size += left->size;
        if (right != nullptr)
            new_size += right->size;
        size = new_size;
        if (!value.empty())
            size += value.size();
    }

    int64_t get_index() {
        int64_t index = 0;
        if (left != nullptr)
            index += left->size;
        if (!value.empty())
            index += value.size();
        return index;
    }


};


//Node *merge(Node *left, Node *right) {
//    int64_t new_size = 0;
//    if (left)
//        new_size += left->size;
//    if (right)
//        new_size += right->size;
//    return new Node(left, right, new_size);
//}

void merge(Node *left, Node *right, Node *&root) {
    if (left == nullptr || right == nullptr)
        return void(root = left ? left : right);

    if (left->key > right->key) {
        root = left;
        merge(left->right, right, root->right);
    } else {
        root = right;
        merge(left, right->left, root->left);
    }
    if (root) root->recalc();
}

//std::pair<Node *, Node *> split(Node *node, int64_t index) {
//    auto tree1 = new Node();
//    auto tree2 = new Node();
//    std::pair<Node *, Node *> answer(tree1, tree2);
//    if (node->left) {
//        if (node->left->size >= index) {
//            answer = split(node->left, index);
//            tree1 = answer.first;
//            tree2->left = answer.second;
//            tree2->right = node->right;
//            tree2->size = tree2->left->size + tree2->right->size;
//        } else {
//            answer = split(node->right, index - node->left->size);
//            tree1->left = node->left;
//            tree1->right = answer.first;
//            tree1->size = tree1->left->size + tree1->right->size;
//            tree2 = answer.second;
//        }
//    } else {
//        tree1->value = node->value.substr(0, index);
//        tree2->value = node->value.substr(index);
//        tree1->size = index;
//        tree2->size = node->value.length() - index ;
//    }
//    answer.first = tree1;
//    answer.second = tree2;
//    return answer;
//}

void split(Node *root, int64_t x, Node *&left, Node *&right) {
    if (root->) {

    }

    int64_t key = root->get_index();
    if (key <= x) {
        left = root;
        split(root->right, x - key, left->right, right);
        if (left) left->recalc();
    } else {
        right = root;
        split(root->left, x, left, right->left);
        if (right) right->recalc();
    }
}

//Node *insert(Node *node, int64_t k, std::string value) {
//    std::pair<Node *, Node *> tmp = split(node, k);
//    Node *tree1 = tmp.first;
//    Node *tree3 = tmp.second;
//    auto tree2 = new Node(value);
//    return merge(merge(tree1, tree2), tree3);
//}
void insert(Node *&root, Node* new_node, int64_t value) {
    Node *left = nullptr;
    Node *right = nullptr;
    split(root, value - 1, left, right);
    merge(left, new_node, left);
    merge(left, right, root);
}

void remove( Node *&node, int64_t begin_index, int64_t end_index) {
    Node* tree1;
    Node* tree2;
    Node* tree3;
    Node* tree4;
    split(node, begin_index, tree1, tree2);
    split(tree2, end_index - begin_index, tree3, tree4);
    merge(tree1, tree4, node);
}

std::string get_substring(Node* node, int64_t begin_index, int64_t end_index) { //индексы не включительно
    std::string answer;
    if (node->left) {
        if (node->left->size >= end_index) {
            answer = get_substring(node->left, begin_index, end_index);
        } else {
            if (node->left->size > begin_index) {
                answer = get_substring(node->left, begin_index, node->left->size) +
                         get_substring(node->right, 0, end_index - node->left->size);
            }  else {
                answer = get_substring(node->right, begin_index - node->left->size, end_index - node->left->size);
            }
        }
    } else {
        answer = node->value.substr(begin_index, end_index);
    }

    return answer;
}


int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::freopen("log.in", "r", stdin);
    std::freopen("log.out", "w", stdout);

    int64_t n = 0;
    std::cin >> n;

    Node* root = nullptr;

    int64_t index = 0;
    int64_t amount = 0;
    int64_t begin_index = 0;
    int64_t count = 0;

    for (int64_t i = 0; i < n; ++i) {
        char operation = '?';

        std::cin >> operation;

        if (root == nullptr && operation == '+') {
            char letter = 'w';
            std::cin >> index >> amount >> letter;
            std::string line(amount, letter);
            root = new Node(line);
            root->recalc();
            continue;
        }

        switch (operation) {
            case '+': {
                char letter = 'w';
                std::cin >> index >> amount >> letter;
                std::string line(amount, letter);
                insert(root, new Node(line), index);
                break;
            }
            case '-': {
                std::cin >> begin_index >> count;
                remove(root, begin_index - 1, begin_index + count - 1);
                break;
            }
            default: {
                std::cin >> begin_index >> count;
                auto line = get_substring(root, begin_index - 1, count);
                int64_t number = 1;
                std::sort(line.begin(), line.end());
                for (int64_t p = 1; p < line.size(); ++p) {
                    if (line[p] != line[p - 1])
                        ++number;
                }
                std::cout << number << '\n';
                break;
            }
        }
    }


    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    Node *parent;
    Node *left;
    Node *right;
    int64_t value;
    int64_t key;
    size_t number;

    Node(int64_t value, int64_t key, size_t number) {
        this->value = value;
        this->key = key;
        right = left = parent = nullptr;
        this->number = number;
    }

};


void print(Node *root) {
    if (root->parent != nullptr)
        std::cout << root->parent->number << ' ';
    else
        std::cout << 0 << ' ';
    if (root->left != nullptr)
        std::cout << root->left->number << ' ';
    else
        std::cout << 0 << ' ';
    if (root->right != nullptr)
        std::cout << root->right->number << '\n';
    else
        std::cout << 0 << '\n';
}


//void merge(std::vector<Node*> &suk, size_t param, size_t left, size_t mid, size_t right) {
//    int64_t it1 = mid - left + 1;
//    int64_t it2 = right - mid;
//
//    std::vector<Node*> L(it1);
//    std::vector<Node*> R(it2);
//
//}
//
//void m_sort(std::vector<Node*> &suk, size_t param, size_t left, size_t right) {
//    if (left + 1 >= right)
//        return;
//    size_t mid = (left + right) / 2;
//    m_sort(suk, param, left, mid);
//    m_sort(suk, param, mid, right);
//    merge(suk, param,  left, mid, right);
//}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::pair<int64_t, std::pair<int64_t, size_t>>> elem(n);
    std::vector<Node*> suk(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> elem[i].first >> elem[i].second.first;
        elem[i].second.second = i + 1;
        suk[i] = new Node(elem[i].first, elem[i].second.first, elem[i].second.second);
    }

//    m_sort(suk, 0, 0, n - 1);
    std::sort(elem.begin(), elem.end());

    size_t i = 0;

//    Node *root = new Node(elem[i].first, elem[i].second.first, elem[i].second.second);
    Node *root = suk[elem[i].second.second - 1];
    root->parent = root->right = root->left = nullptr;
    Node *last = root;
    i = 1;

    while (i < n) {
//        Node *tmp = new Node(elem[i].first, elem[i].second.first, elem[i].second.second);
        Node *tmp = suk[elem[i].second.second - 1];
        while (true) {
            if (tmp->key <= last->key) { //>=
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

    std::cout << "YES" << '\n';
    for(auto i : suk)
        print(i);

    return 0;
}
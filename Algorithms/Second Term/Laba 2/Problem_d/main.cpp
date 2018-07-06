#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include <cmath>


#include <iostream>

struct node {
    node *left_child;
    node *right_child;
    int64_t key;
    int64_t height;

    node(int64_t key) {
        this->key = key;
        left_child = right_child = nullptr;
        height = 1;
    }
};


bool exists(node *p, int64_t key) {
    if (p == nullptr)
        return false;
    if (key == p->key)
        return true;
    if (key < p->key) {
        if (p->left_child == nullptr)
            return false;
        return exists(p->left_child, key);
    } else if (key > p->key) {
        if (p->right_child == nullptr)
            return false;
        return exists(p->right_child, key);
    }
    return false;
}

int64_t height(node *p) {
    return p != nullptr ? p->height : 0;
}

int64_t balance_factor(node *p) {
    return height(p->right_child) - height(p->left_child);
}

void fix_height(node *p) {
    int64_t hl = height(p->left_child);
    int64_t hr = height(p->right_child);
    p->height = (hl > hr ? hl : hr) + 1;
}

node *small_right_rotate(node *p) {
    node *q = p->left_child;
    p->left_child = q->right_child;
    q->right_child = p;
    fix_height(p);
    fix_height(q);
    return q;
}

node *small_left_rotate(node *q) {
    node *p = q->right_child;
    q->right_child = p->left_child;
    p->left_child = q;
    fix_height(q);
    fix_height(p);
    return p;
}

node *balance(node *p) {
    fix_height(p);
    if (balance_factor(p) == 2) {
        if (balance_factor(p->right_child) < 0)
            p->right_child = small_right_rotate(p->right_child);
        return small_left_rotate(p);
    }
    if (balance_factor(p) == -2) {
        if (balance_factor(p->left_child) > 0)
            p->left_child = small_left_rotate(p->left_child);
        return small_right_rotate(p);
    }
    return p;
}

node *ins(node *p, int64_t k, bool first) {
    if (p == nullptr)
        return new node(k);
    if (p->height == 0)
        return new node(k);
    if (first) {
        if (exists(p, k))
            return p;
    }

    if (k < p->key)
        p->left_child = ins(p->left_child, k, false);
    else
        p->right_child = ins(p->right_child, k, false);
    return balance(p);
}

node *find_min(node *p) {
    return p->left_child != nullptr ? find_min(p->left_child) : p;
}

node *find_max(node *p) {
    return p->right_child != nullptr ? find_min(p->right_child) : p;
}


node *remove_min(node *p) {
    if (p->left_child == nullptr)
        return p->right_child;
    p->left_child = remove_min(p->left_child);
    return balance(p);
}

node *remove(node *p, int64_t k, bool first) {
    if (first) {
        if (!(exists(p, k)))
            return p;
    }
    if (p == nullptr)
        return nullptr;
    if (k < p->key)
        p->left_child = remove(p->left_child, k, false);
    else if (k > p->key)
        p->right_child = remove(p->right_child, k, false);
    else {
        node *q = p->left_child;
        node *r = p->right_child;
        delete p;
        if (r == nullptr)
            return q;
        node *min = find_min(r);
        min->right_child = remove_min(r);
        min->left_child = q;
        return balance(min);
    }
    return balance(p);
}


node* next(node *p, int64_t key) {
    if (p == nullptr)
        return nullptr;
    node *tmp = p;
    node *suc = nullptr;
    while (tmp != nullptr) {
        if (tmp->key >= key) {
            suc = tmp;
            tmp = tmp->left_child;
        } else {
            tmp = tmp->right_child;
        }
    }
    if (suc == nullptr) {
        return nullptr;
    } else
        return suc;
}

node* prev(node *p, int64_t key) {
    if (p == nullptr)
        return nullptr;
    node *tmp = p;
    node *suc = nullptr;
    while (tmp != nullptr) {
        if (tmp->key <= key) {
            suc = tmp;
            tmp = tmp->right_child;
        } else {
            tmp = tmp->left_child;
        }
    }
    if (suc == nullptr) {
        return nullptr;
    } else
        return suc;
}












const int64_t ARRAY_SIZE = (int64_t) 137000*3;

int64_t get_random(int64_t left, int64_t right) {
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int64_t> uniform_dist(left, right);
    return uniform_dist(e1);
}

struct Node {
    Node *left;
    Node *right;
    int64_t value;
    int64_t key;
    int64_t size;

    Node(int64_t key, int64_t value) {
        left = right = nullptr;
        this->value = value;
        this->key = key;
        size = 1;
    }

    void recalc() {
        int64_t new_size = 0;
        if (left != nullptr)
            new_size += left->size;
        if (right != nullptr)
            new_size += right->size;
        size = new_size;
        ++size;
    }

    void print() {
        std::cout << value << ' ';
    }

    int64_t get_index() {
        int64_t index = 0;
        if (left != nullptr)
            index += left->size;
        return ++index;
    }

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

    void split(Node *root, int64_t x, Node *&left, Node *&right) {
        if (root == nullptr) {
            left = nullptr;
            right = nullptr;
            return;
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

    void insert(Node *&root, Node* new_node, int64_t value) {
        Node *left = nullptr;
        Node *right = nullptr;
        split(root, value - 1, left, right);
        merge(left, new_node, left);
        merge(left, right, root);
    }

    void erase(Node *&root, int64_t value) {
        int64_t pos = root->get_index();
        if (pos == value)
            merge(root->left, root->right, root);
        else if (value < pos)
            erase(root->left, value);
        else
            erase(root->right, value - pos);
        if (root) root->recalc();
    }

};

void print(Node* v) {
    if (!v)
        return;
    print(v->left);
    std::cout << v->value << ' ';
    print(v->right);
}

void print(Node* root, int64_t from, int64_t to) {
//    Node *l = 0, *m = 0, *r = 0;
//    split(root, from - 1, l, r);
//    split(r, to - from, m, r);
//    Node::Print(m);
//    merge(l, m, l);
//    merge(l, r, root);
    Node* left = nullptr, *middle = nullptr, *right = nullptr;
    root->split(root, from - 1, left, right);
    root->split(right, to - from, middle, right);
    print(middle);
    root->merge(left, middle, left);
    root->merge(left, right, root);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

//    std::freopen("input.txt", "r", stdin);

    int64_t n, m;
    std::cin >> n >> m;

    Node *root = nullptr;
    int64_t nodes = 0;
    int64_t prs[ARRAY_SIZE];
    for (int64_t &pr : prs)
        pr = get_random(1, INT64_MAX);

    node *root_for_avl = nullptr;
    for (int64_t i = 1; i <= m; ++i) {
        root->insert(root, new Node(prs[nodes++], 0), i);
        root_for_avl = ins(root_for_avl, i, true);
    }

    int64_t max_pos = 0;
    for (int64_t i = 1; i <= n; ++i) {
        int64_t pos;
        std::cin >> pos;
        node *it = next(root_for_avl, pos); //node* it
        if (it == nullptr || it->key > max_pos)
            ++max_pos;

        if (it != nullptr) {
            root->erase(root, it->key); //ошибка здесь хыыыы, а может и не здесь хыыыыыы
            root_for_avl = remove(root_for_avl, it->key, true);
        }

        if (pos > max_pos)
            max_pos = pos;

        root->insert(root, new Node(prs[nodes++], i), pos);

    }
    std::cout << max_pos << '\n';
    print(root, 1, max_pos + 1);
//    std::cout << 6 << '\n';
//    std::cout << "4 0 5 2 3 1";
    return 0;
}
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


std::string next(node *p, int64_t key) {
    if (p == nullptr)
        return "none";
    node *tmp = p;
    node *suc = nullptr;
    while (tmp != nullptr) {
        if (tmp->key > key) {
            suc = tmp;
            tmp = tmp->left_child;
        } else {
            tmp = tmp->right_child;
        }
    }
    if (suc == nullptr) {
        return "none";
    } else
        return std::to_string(suc->key);
}

std::string prev(node *p, int64_t key) {
    if (p == nullptr)
        return "none";
    node *tmp = p;
    node *suc = nullptr;
    while (tmp != nullptr) {
        if (tmp->key < key) {
            suc = tmp;
            tmp = tmp->right_child;
        } else {
            tmp = tmp->left_child;
        }
    }
    if (suc == nullptr) {
        return "none";
    } else
        return std::to_string(suc->key);
}

int main() {
//    std::freopen("input.txt", "r", stdin);

    std::string str;
    int64_t value = 0;

    node *root = nullptr;
    char* buffer;

    //while (std::cin >> str >> value) {
    while (std::getline(std::cin, str)) {
        std::string tmp = "";
        std::string svalue = "";
        size_t i = 0;
        while(str[i] != ' ')
            tmp += str[i++];
        ++i;
        while(str[i] != ' ' && str[i] != EOF && i < str.length() && str[i] != '\n')
            svalue += str[i++];
        str = tmp;
        value = std::stoll(svalue);

        if (str == "insert") {
            root = ins(root, value, true);
        } else if (str == "delete") {
            root = remove(root, value, true);
        } else if (str == "exists") {
            if (exists(root, value))
                std::cout << "true\n";
            else
                std::cout << "false\n";
        } else if (str == "next") {
            std::cout << next(root, value) << '\n';
        } else if (str == "prev") {
            std::cout << prev(root, value)<< '\n';
        }
    }

    return 0;
}
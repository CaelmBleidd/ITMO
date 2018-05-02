////
//// Created by Alexey Menshutin on 01.05.2018.
////
//
//#include <iostream>
//#include <random>
//#include <set>
//#include <algorithm>
//#include <cmath>
//
//
//struct node {
//    node *left_child;
//    node *right_child;
//    int64_t key;
//    int64_t height;
//
//    node(int64_t key) {
//        this->key = key;
//        left_child = right_child = nullptr;
//        height = 1;
//    }
//};
//
//
//
//int64_t height(node *p) {
//    return p != nullptr ? p->height : 0;
//}
//
//int64_t balance_factor(node *p) {
//    return height(p->right_child) - height(p->left_child);
//}
//
//void fix_height(node *p) {
//    int64_t hl = height(p->left_child);
//    int64_t hr = height(p->right_child);
//    p->height = (hl > hr ? hl : hr) + 1;
//}
//
//node *small_right_rotate(node *p) {
//    node *q = p->left_child;
//    p->left_child = q->right_child;
//    q->right_child = p;
//    fix_height(p);
//    fix_height(q);
//    return q;
//}
//
//node *small_left_rotate(node *q) {
//    node *p = q->right_child;
//    q->right_child = p->left_child;
//    p->left_child = q;
//    fix_height(q);
//    fix_height(p);
//    return p;
//}
//
//node *balance(node *p) {
//    fix_height(p);
//    if (balance_factor(p) == 2) {
//        if (balance_factor(p->right_child) < 0)
//            p->right_child = small_right_rotate(p->right_child);
//        return small_left_rotate(p);
//    }
//    if (balance_factor(p) == -2) {
//        if (balance_factor(p->left_child) > 0)
//            p->left_child = small_left_rotate(p->left_child);
//        return small_right_rotate(p);
//    }
//    return p;
//}
//
//node *ins(node *p, int64_t k, bool first) {
//    if (p == nullptr)
//        return new node(k);
//    if (p->height == 0)
//        return new node(k);
//    if (first) {
////        if (exists(p, k))
////            return p;
//    }
//
//    if (k < p->key)
//        p->left_child = ins(p->left_child, k, false);
//    else
//        p->right_child = ins(p->right_child, k, false);
//    return balance(p);
//}
//
//node *find_min(node *p) {
//    return p->left_child != nullptr ? find_min(p->left_child) : p;
//}
//
//node *find_max(node *p) {
//    return p->right_child != nullptr ? find_min(p->right_child) : p;
//}
//
//
//node *remove_min(node *p) {
//    if (p->left_child == nullptr)
//        return p->right_child;
//    p->left_child = remove_min(p->left_child);
//    return balance(p);
//}
//
//node *remove(node *p, int64_t k, bool first) {
//    if (first) {
////        if (!(exists(p, k)))
////            return p;
//    }
//    if (p == nullptr)
//        return nullptr;
//    if (k < p->key)
//        p->left_child = remove(p->left_child, k, false);
//    else if (k > p->key)
//        p->right_child = remove(p->right_child, k, false);
//    else {
//        node *q = p->left_child;
//        node *r = p->right_child;
//        delete p;
//        if (r == nullptr)
//            return q;
//        node *min = find_min(r);
//        min->right_child = remove_min(r);
//        min->left_child = q;
//        return balance(min);
//    }
//    return balance(p);
//}
//
//
//node* next(node *p, int64_t key) {
////    if (p == nullptr)
////        return nullptr;
//    node *tmp = p;
//    node *suc = nullptr;
//    while (tmp != nullptr) {
//        if (tmp->key >= key) {
//            suc = tmp;
//            tmp = tmp->left_child;
//        } else {
//            tmp = tmp->right_child;
//        }
//    }
//    if (suc == nullptr) {
//        return nullptr;
//    } else
//        return suc;
//}
//
//node* prev(node *p, int64_t key) {
//    if (p == nullptr)
//        return nullptr;
//    node *tmp = p;
//    node *suc = nullptr;
//    while (tmp != nullptr) {
//        if (tmp->key <= key) {
//            suc = tmp;
//            tmp = tmp->right_child;
//        } else {
//            tmp = tmp->left_child;
//        }
//    }
//    if (suc == nullptr) {
//        return nullptr;
//    } else
//        return suc;
//}
//
//
//
//
//using namespace std;
//
//typedef long li;
//
//int64_t get_random(int64_t left, int64_t right) {
//    std::random_device r;
//    std::default_random_engine e1(r());
//    std::uniform_int_distribution<int64_t> uniform_dist(left, right);
//    return uniform_dist(e1);
//}
//
//template <class T>
//T Maximize (T &v, T nv) { if (nv > v) v = nv; return v; }
//
//template <class T>
//T Minimize (T &v, T nv) { if (nv < v) v = nv; return v; }
//
//
//class Treap
//{
//    static const int64_t N = (li)3e5 + 1;
//
//    struct Node
//    {
//        int64_t pr, size, v;
//        Node *l, *r;
//
//        Node (int64_t pr, int64_t v) : pr(pr), v(v), l(0), r(0), size(1) {}
//
//        void Update ()
//        {
//            size = SizeOf(l) + SizeOf(r) + 1;
//        }
//
//        void Print ()
//        {
//            printf("%ld", v);
//        }
//
//        int64_t Index ()
//        {
//            return SizeOf(l) + 1;
//        }
//
//        inline static int64_t SizeOf (Node *v)
//        {
//            return v ? v->size : 0;
//        }
//
//        static void Update (Node *v)
//        {
//            if (!v) return;
//            v->Update();
//        }
//
//        static void Print (Node *v)
//        {
//            if (!v) return;
//            Print(v->l);
//            v->Print(), printf(" ");
//            Print(v->r);
//        }
//    };
//
//private:
//    Node *root;
//    int64_t prs[N], nodes;
//
//    void merge (Node *l, Node *r, Node *&v)
//    {
//        if (!l || !r) return void(v = l ? l : r);
//
//        if (l->pr > r->pr)
//        {
//            v = l;
//            merge(l->r, r, v->r);
//        }
//        else
//        {
//            v = r;
//            merge(l, r->l, v->l);
//        }
//        Node::Update(v);
//    }
//
//    void split (Node *v, int64_t x, Node *&l, Node *&r)
//    {
//        if (!v) return void(l = r = 0);
//
//        int64_t key = v->Index();
//        if (key <= x)
//        {
//            l = v;
//            split(v->r, x - key, l->r, r);
//            Node::Update(l);
//        }
//        else
//        {
//            r = v;
//            split(v->l, x, l, r->l);
//            Node::Update(r);
//        }
//    }
//
//    void insert (Node *v, int64_t x)
//    {
//        Node *l = 0, *r = 0;
//        split(root, x - 1, l, r);
//        merge(l, v, l);
//        merge(l, r, root);
//    }
//
//    void erase (Node *&v, int64_t x)
//    {
//        int64_t pos = v->Index();
//        if (pos == x) merge(v->l, v->r, v);
//        else if (x < pos) erase(v->l, x);
//        else erase(v->r, x - pos);
//        Node::Update(v);
//    }
//
//    void generatePriorities ()
//    {
//        for (int64_t i = 0; i < N; ++ i)
//        {
//            prs[i] = get_random(1, INT64_MAX);
//        }
//    }
//public:
//    Treap () : root(0), nodes(0)
//    {
//        generatePriorities();
//    }
//
//    void Insert (int64_t v, int64_t x)
//    {
//        insert(NewNode(v), x); //i, pos
//    }
//
//    void Erase (int64_t x)
//    {
//        erase(root, x);
//    }
//
//    void Print ()
//    {
//        Node::Print(root);
//    }
//
//    void Print (int64_t from, int64_t to)
//    {
//        Node *l = 0, *m = 0, *r = 0;
//        split(root, from - 1, l, r);
//        split(r, to - from, m, r);
//        Node::Print(m);
//        merge(l, m, l);
//        merge(l, r, root);
//    }
//
//    Node* NewNode (int64_t v)
//    {
//        return new Node(prs[nodes++], v);
//    }
//};
//
//
//
//void solve ()
//{
//    int64_t n, m;
//    scanf("%ld %ld", &n, &m);
//
//    srand(time(0));
//
//    Treap *t = new Treap(); // создал массив приоритетов, возможно что-то инициализировал
//    set <int64_t> zeros;    // создал сет какой-то хуйни, предположительно индексов
//    node* tooo = nullptr;
//    for (int64_t i = 1; i <= m; ++ i) // заполняем дерево и сет какой-то хуйни нулями и позициями (индексами)
//    {
//        t->Insert(0, i);
//        zeros.insert(i);
//        tooo = ins(tooo, i, true);
//    }
//
//    int64_t maxpos = 0;     // хуй знает что
//    for (int64_t i = 1; i <= n; ++ i)   // начинаем обрабатывать инсерты
//    {
//        int64_t pos;
//        scanf("%ld", &pos); // смотрим, в какую позицию захуярить
//        set<int64_t>::iterator it = zeros.lower_bound(pos); // ставим итератор на первый элемент, не меньший нашего (индекс его либо такой же, либо больше)
//        node* it2 = next(tooo, pos);
//        if (it == zeros.end() || *it > maxpos)  // если итератор в самом конце предполагаемого массива либо мы уже даже ушли за его границы, разширяем макспос
////        if (it == nullptr || it->key > maxpos)
//        {
//            maxpos ++;
//        }
//        if (it != zeros.end())      // если же нет, удаляем какую-то хуйню почему-то
////        if (it != nullptr)
//        {
////            t->Erase(it->key);
//            zeros.erase(it);
//            tooo = remove(tooo, it, true);
//        }
//
//        Maximize(maxpos, pos);
//
//        //printf("%ld\n", maxpos);
//
//        t->Insert(i, pos);
//        //t->Print();
//        //printf("\n");
//    }
//
//    printf("%ld\n", maxpos);
//    t->Print(1, maxpos + 1);
//}
//int main()
//{
//    solve();
//    return 0;
//}
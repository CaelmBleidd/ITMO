#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>


int main() {
    freopen("markchain.in", "r", stdin);
    freopen("markchain.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;

    std::vector<std::vector<double> > chain;

    chain.reserve(n);
    for (int i = 0; i < n; ++i) {
        chain.push_back(std::move(std::vector<double>(n)));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double a;
            std::cin >> a;
            chain[i][j] = a;
        }
    }

    bool was_changed;
    std::vector<std::vector<double> > pre_chain(chain);
    for (int p = 0; p < 1000000; ++p) {
        std::vector<std::vector<double> > tmp(n);
        for (int i = 0; i < n; ++i) {
            tmp[i].assign(n, 0);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    tmp[i][j] += pre_chain[i][k] * pre_chain[k][j];
                }
            }
        }
        was_changed = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (abs(pre_chain[i][j] - tmp[i][j]) >= 0.0001)
                    was_changed = true;
            }
        }
        pre_chain = tmp;
        if (!was_changed)
            break;
    }

    for (int i = 0; i < pre_chain[0].size(); ++i) {
        printf("%.4f\n", pre_chain[0][i]);
    }

    return 0;
}

//#include <iostream>
//#include <vector>
//#include <cmath>
//
//void swap(long double &d, long double &d1);
//
//int main() {
//    freopen("markchain.in", "r", stdin);
//    freopen("markchain.out", "w", stdout);
//    std::ios::sync_with_stdio(false);
//    std::cin.tie(nullptr);
//
//    int32_t n;
//
//    std::cin >> n;
//
//    std::vector<std::vector<long double>> chain;
//
//    for (int i = 0; i < n; ++i) {
//        chain.emplace_back(std::vector<long double>(n));
//    }
//
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            long double a;
//            std::cin >> a;
//            chain[i][j] = a;
//        }
//    }
//
//    bool was_changed = false;
//
//
//    std::vector<std::vector<long double>> pre_chain(chain);
//    for (int32_t p = 0; p < 1000000; ++p) {
//        std::vector<std::vector<long double>> tmp(n);
//        for (int i = 0; i < n; ++i) {
//            tmp[i].assign(n, 0);
//        }
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                for (int k = 0; k < n; ++k) {
//                    tmp[i][j] += pre_chain[i][k] * pre_chain[k][j];
//                }
//            }
//        }
//        was_changed = false;
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                if (abs(pre_chain[i][j] - tmp[i][j]) >= 0.0001)
//                    was_changed = true;
//            }
//        }
//
//
//        pre_chain = tmp;
//
//        if (!was_changed)
//            break;
//    }
//
//    for (auto i : pre_chain[0]) {
//        std::cout << i << ' ';
//    }
//
//    return 0;
//}
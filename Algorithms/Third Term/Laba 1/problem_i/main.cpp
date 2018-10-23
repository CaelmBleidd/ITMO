#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

template<typename T>
T sqr(T amount) {
    return amount * amount;
}

int main() {
    uint64_t n{0};
    std::cin >> n;

    std::vector<int64_t> x_array(n + 1);
    std::vector<int64_t> y_array(n + 1);
    std::vector<double> d_array(n + 1, INT64_MAX);
    std::vector<uint16_t> used(n + 1, 0);

    for (uint64_t i = 0; i < n; ++i) {
        int64_t x{0}, y{0};
        std::cin >> x >> y;
        x_array[i] = x;
        y_array[i] = y;
    }

    double result = 0;
    int64_t next = 0;

    while (true) {
        used[next] = 1;
        double min = INT64_MAX;
        int64_t index = -1;
        bool is_ok = false;
        for (uint64_t i = 0; i < n; ++i) {
            if (used[i] == 0) {
                is_ok = true;
                double tmp = min;
                d_array[i] = std::min(d_array[i],
                                      std::sqrt(sqr(x_array[i] - x_array[next]) + sqr(y_array[i] - y_array[next])));
                min = std::min(min, d_array[i]);
                if (tmp != min)
                    index = i;
            }
        }
        if (!is_ok) break;
        result += min;
        next = index;
    }

    printf("%.20f", result);


    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>

#define ll int64_t

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    ll n = 0;
    ll w = 0;

    cin >> n >> w;

    ll INF = INT64_MAX / 2;
    vector<bool> used(n + 2, false);
    vector<ll> distances(n + 2, INF);
    vector<vector<ll>> vertex(n + 2, vector<ll>(n + 2));
    vector<ll> x1(n);
    vector<ll> y1(n);
    vector<ll> y2(n);
    vector<ll> x2(n);

    for (auto i = 0; i < n; ++i) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }

    vertex[0][n + 1] = vertex[n + 1][0] = w;

    for (auto i = 0; i < n; ++i) {
        auto min_y = min(y1[i], y2[i]);
        auto max_y = max(y1[i], y2[i]);
        auto w_max_y = w - max_y;
        vertex[0][i + 1] = vertex[i + 1][0] = w_max_y;
        vertex[n + 1][i + 1] = vertex[i + 1][n + 1] = min_y;

        for (auto j = 0; j < n; ++j) {
            if (i == j) continue;
            auto hor = x1[i] <= x1[j] ? x1[j] - x2[i] : x1[i] - x2[j];
            auto ver = y1[i] <= y1[j] ? y1[j] - y2[i] : y1[i] - y2[j];
            vertex[i + 1][j + 1] = vertex[j + 1][i + 1] = max((ll)0, max(ver, hor));
        }
    }

    distances[0] = 0;
    for (auto i = 0; i < n + 2; ++i) {
        ll v = -1;
        for (auto j = 0; j < n + 2; ++j) {
            if (!used[j] && (v == -1 || distances[j] < distances[v]))
                v = j;
        }
        if (distances[v] == INF) break;
        used[v] = true;
        for (auto u = 0; u < n + 2; ++u) {
            if (v == u) continue;
            auto d = vertex[v][u];
            if (distances[v] + d < distances[u])
                distances[u] = distances[v] + d;
        }
    }

    cout << (distances[n + 1] == INF ? 0 : distances[n + 1]);


    return 0;
}


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

vector<long long> v;

int main() {
	freopen("saloon.in", "r", stdin);
	freopen("saloon.out", "w", stdout);
	
	int n;
	cin >> n;
	int count = 0;
	deque<int> v;
	vector<int> poset(n);

	for (int i = 0; i < n; i++) {
		int h, m, l;
		cin >> h >> m >> l;
		m += h * 60;
		while (v.size() > 0 && v[0] <= m)
			v.pop_front();
		if (v.size() == 0) {
			v.push_back(m + 20);
			poset[i] = m + 20;
		}
		else {
			
			if (l >= v.size()) {
				v.push_back(*(v.end()-1) + 20);
				poset[i] = *(v.end()-1);
			}
			else
				poset[i] = m;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << poset[i] / 60 << ' ' << poset[i] % 60 << '\n';
	}
	return 0;
}
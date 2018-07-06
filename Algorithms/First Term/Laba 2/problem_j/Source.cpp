#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;


int main() {
	std::ios::sync_with_stdio(false);

	freopen("bureaucracy.in", "r", stdin);
	freopen("bureaucracy.out", "w", stdout);

	long long n,m;


	cin >> n >> m;
	
	long long sum = 0;
	long long size = n;
	long long zero = 0;
	long long tmp = m;
	long long a = 0;
	long long hy = 0;
	long long result = 0;

	vector < pair<long long, long long> > v(n);
	vector <long long> v_2(n);

	for (int i = 0; i < n; i++) {
		cin >> v[i].first;
		v[i].second = i;
		sum += v[i].first;
	}

	if (sum <= m) {
		cout << -1;
		return 0;
	}
	else {
		sort(v.begin(), v.end());

		while ((v[zero].first-hy)*(n-zero)<tmp) {
			tmp -= (v[zero].first-hy)*(n - zero);
			hy = v[zero].first;
		//	v[zero].first = 0;
	//		size--;
			zero++;
		}

 		a = tmp / (n - zero);
		hy += a;
		//tmp -= a*(n - zero);
		
		for (int i = 0; i < n; i++) {
			v_2[v[i].second] = v[i].first;

			if (v_2[v[i].second] > hy) {
				v_2[v[i].second] -= hy;
				m -= hy;
			}
			else {
				m -= v_2[v[i].second];
				v_2[v[i].second] = 0;
				size--;
			}
		}

		for (int i = 0; m > 0; i++) {
			if (v_2[i] != 0) {
				v_2[i]--;
				m--;
				if (v_2[i] == 0)
					size--;
				if (m == 0) {
					result = i + 1;
				}
			}
			else continue;
		}

		cout << size << '\n';

		for (int i = result; i < n; i++) {
			if (v_2[i] != 0)
				cout << v_2[i] << ' ';
		}
		for (int i = 0; i < result; i++) {
			if (v_2[i] != 0)
				cout << v_2[i] << ' ';
		}
		return 0;
	}
	
	
}
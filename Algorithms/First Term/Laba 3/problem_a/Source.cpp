#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <iomanip>  
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<long long> v(10001);
	vector<long long> a(10001);
	vector<long long> p(10001);
	vector<long long> ans;

	long long n, k; 

	cin >> n >> k;

	for (int i = 2; i < n; i++) {
		long long b; 
		cin >> b;
		a[i] = b;
	}

	v[1] = 0; 
	a[1] = 0; 
	a[n] = 0;

	for (long long i = 2; i <= n; i++) {
		long long max = i - 1;
		for (long long j = (i-k)>1 ? i-k : 1; j <= i - 1; j++) {
			if (v[j] > v[max]) {
				max = j;
			}
		}
		v[i] = v[max] + a[i];
		p[i] = max;
	}

	long long i = n;
	ans.push_back(i);
	do {
		i = p[i];
		ans.push_back(i);
	} while (i > 1);

	cout << v[n] << '\n';
	cout << ans.size() - 1 << '\n';
	reverse(ans.begin(), ans.end());
	for (long long i : ans) {
		cout << i << ' ';
	}


	return 0;
}
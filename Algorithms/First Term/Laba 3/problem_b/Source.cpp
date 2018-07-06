#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <iomanip>  
#include <algorithm>

using namespace std;

long long binsearch(vector<long long> a, long long key) {
	long long l = -1; 
	long long r = a.size(); 
	while (l < r - 1) {
		long long m = (l + r) / 2;
		if (a[m] <= key)
			l = m;
		else
			r = m;
	}
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	long long n; 
	cin >> n;

	vector<long long> v;
	vector<long long> d(n+1);
	vector<long long> pos(n+1); 
	vector<long long> prev(n);
	vector<long long> ans;

	long long length = 0;


	for (long long i = 0; i < n; i++) {
		long long a;
		cin >> a;
		v.push_back(a);
	}

	pos[0] = -1;
	d[0] = LLONG_MIN;
	for (long long i = 1; i <= n; i++) {
		d[i] = LLONG_MAX;
	}
	for (long long i = 0; i < n; i++) {
		long long j = binsearch(d, v[i]);
		if (d[j - 1] < v[i] && v[i] < d[j]) {
			d[j] = v[i];
			pos[j] = i;
			prev[i] = pos[j - 1];
			length = length > j ? length : j;
		}
	}

	long long p = pos[length];
	while (p != -1) {
		ans.push_back(v[p]);
		p = prev[p];
	}
	reverse(ans.begin(), ans.end());
	cout << length << '\n';
	for (long long i : ans) {
		cout << i << ' ';
	}


	return 0;
}
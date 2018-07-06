#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <algorithm>

using namespace std;

long long mini(long long a, long long b, long long c) {
	if (a <= b && a <= c)
		return a;
	else if (b <= a && b <= c)
		return b; 
	else return c;
}

int main() {
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);

	long long f = 0, s = 0, ans = 0;

	int n;
	cin >> n;
	vector<long long> a(10000,10000000000001);
	long long count = 0;

	for (long long i = 0; i < n; i++) {
		cin >> a[i];
		
	}
	sort(a.begin(), a.end());
	vector<long long> b(10000, 10000000000001);
	

	for (long long k = 0; k < n - 1; k++) {
		long long d = mini(a[f] + a[f + 1], a[f] + b[s], b[s] + b[s + 1]);
		
		if (d == a[f] + a[f + 1]) {
			b[k] = a[f] + a[f + 1];
			f += 2;
		}
		else if (d == a[f] + b[s]) {
			b[k] = a[f++] + b[s++];
		}
		else {
			b[k] = b[s] + b[s + 1];
			s += 2;
		}
		ans += d;
	}
	cout << ans;


	return 0;
}

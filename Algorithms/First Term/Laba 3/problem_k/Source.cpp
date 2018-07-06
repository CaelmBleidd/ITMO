#include <iostream> 
#include <vector> 
#include <algorithm>

using namespace std;

bool check(long long x, long long y,long long n, long long m) {
	vector<long long> a(m + 1);
	vector<long long> b(m + 1);

	for (int i = 1; i <= m; i++) {
		a[i] = x & 1; 
		b[i] = y & 1;
		x /= 2;
		y /= 2;

		if (i > 1 && a[i] == a[i - 1] && a[i] == b[i] && a[i] == b[i - 1])
			return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	freopen("nice.in", "r", stdin);
	freopen("nice.out", "w", stdout);

	long long n, m; 
	cin >> n >> m;

	long long nn = min(n, m);
	long long mm = max(n, m);

	n = mm;
	m = nn;

	long long x = 1;

	for (long long i = 0; i < m; i++) {
		x *= 2;
	}

	vector<vector<long long>> v;

	for (int i = 0; i <= n + 1; i++) {
		vector < long long> a(x + 1);
		v.push_back(a);
	}

	for (int i = 0; i < x; i++) {
		v[1][i] = 1;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < x; j++)
		{
			for (int k = 0; k < x; k++)
			{
				if (check(j, k,n,m)) {
					v[i][k] = v[i - 1][j] + v[i][k];
				}
			}
		}
	}

	long long res = 0; 

	for (int i = 0; i < x; i++) {
		res += v[n][i];
	}

	cout << res;
	
}
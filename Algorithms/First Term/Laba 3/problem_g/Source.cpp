#include <iostream> 
#include <vector>
#include <string>

using namespace std;

void print(long long l, long long r, vector<vector<long long>> d, vector<vector<long long>> e, string s) {
	if (d[l][r] == r - l + 1)
		return;
	if (d[l][r] == 0) {
		cout << s.substr(l, r - l + 1);
		return;
	}
	if (e[l][r] == -1) {
		cout << s[l];
		print(l + 1, r - 1, d, e, s);
		cout << s[r];
		return;
	}
	print(l, e[l][r], d, e, s);
	print(e[l][r] + 1, r, d, e, s);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	string s;
	cin >> s;

	vector<vector<long long>> d;

	long long n = s.size();

	for (int i = 0; i < n; i++) {
		vector<long long> v(n);
		d.push_back(v);
	}

	vector < vector < long long>> e = d;

	for (int i = 0; i < n; i++) {
		d[i][i] = 1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			i > j ? d[i][j] = 0 : d[i][j] = d[i][j];
		}
	}

	for (long long r = 0; r < n; r++) {
		for (long long l = r; l >= 0; l--) {

			long long best = LONG_MAX / 2;
			long long tmp = -1;

			if (s[l] == '('&& s[r] == ')' || s[l] == '['&& s[r] == ']' || s[l] == '{'&& s[r] == '}') {
				best = d[l + 1][r - 1];
			}

			for (long long k = l; k < r; k++) {
				if (d[l][k] + d[k + 1][r] < best) {
					best = d[l][k] + d[k + 1][r];
					tmp = k;
				}
				d[l][r] = best;
				e[l][r] = tmp;
			}
		}
	}

	print(0, n - 1, d, e, s);
	cin >> s;
	return 0;
}
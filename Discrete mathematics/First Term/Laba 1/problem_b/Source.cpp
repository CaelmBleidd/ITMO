#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

vector <int> arr[50];
vector <int> table[50];
int z[50], ans[50];
int two_pow[] = { 1,2,4,8,16,32,64,128 };


int dfs2(int n) {
	if (z[n] != -1)
		return z[n];
	else {
		int a = 0;
		int h = arr[n].size();
		for (int i = 0; i < h; i += 1)
			a += dfs2(arr[n][i])*two_pow[h - i - 1];
		return table[n][a];
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	vector <int> one;
	int n = 0, r = 0;

	cin >> n;

	for (int i = 1; i <= n; i += 1) {

		int a = 0;
		cin >> a;

		if (a == 0)
			one.push_back(i);

		arr[i].resize(a);

		for (int j = 0; j < a; j += 1) {
			int b;
			cin >> b;
			arr[i][j] = b;
			if (ans[i] < ans[b])
				ans[i] = ans[b];
		}

		ans[i] += 1;

		if (ans[r] < ans[i])
			r = i;

		int t = (int) pow(2, a);
		table[i].resize(t);

		if (a > 0) {
			for (int j = 0; j < t; j += 1) {
				int b;
				cin >> b;
				table[i][j] = b;
			}
		}
	}

	cout << ans[r] - 1 << '\n';

	for (int j = 1; j <= 40; j += 1)
		z[j] = -1;

	for (int i = 0; i < (int)pow(2, one.size()); i += 1) {
		int a = i;
		int ind = one.size() - 1;

		while (a > 0) {

			if (a % 2 == 1) {
				z[one[ind]] = 1;
				ind -= 1;
			}

			else {
				z[one[ind]] = 0;
				ind -= 1;
			}

			a /= 2;
		}

		while (ind >= 0) {
			z[one[ind]] = 0;
			ind -= 1;
		}

		cout << dfs2(r);
	}

	return 0;
}
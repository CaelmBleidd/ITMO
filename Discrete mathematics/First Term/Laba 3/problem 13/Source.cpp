#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std; 

long long factorial(long long a) {
	if (a == 0) {
		return 1;
	}
	else return a*factorial(a - 1);
}

int main() {

	std::ios::sync_with_stdio(false);

	freopen("num2perm.in", "r", stdin);
	freopen("num2perm.out", "w", stdout);

	long long n, k;
	cin >> n >> k;

	vector<bool> isTrue(n+1, false);
	vector<long long> v(n+1);

	for (int i = 1; i <= n; i++)
	{
		long long was = k / factorial(n - i);
		k %= factorial(n - i);
		long long tmp = 0;
		for (int j = 1; j <= n; j++) {
			if (!isTrue[j]) {
				tmp++;
				if (tmp == was + 1) {
					v[i] = j;
					isTrue[j] = !isTrue[j];
				}
			}
		}
		
	}

	for (int i = 1; i < v.size(); i++) {
		cout << v[i] << ' ';
	}
	
}
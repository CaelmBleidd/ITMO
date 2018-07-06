#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	long long n;
	cin >> n;

	vector<long long> price(n+1);
	for (int i = 1; i <= n; i++)
		cin >> price[i];

	vector<vector<long long>> money;
	
//	long long tickets = 0, long long days = 1;

	for (long long i = 0; i < n+2; i++)
	{
		vector<long long> v(n+2, LONG_MAX / 2);
		money.push_back(v);
	}



	money[0][0] = 0;
	if (price[1] > 100)
	{
		money[1][0] = price[1];
		money[1][1] = price[1];
	}
	else {
		money[1][0] = price[1];
	}

	for (int i = 2; i <= n; i++) {
		for(long long j = 0 ; j<=n; j++)
			if (price[i] > 100 && j>0) {
				money[i][j] = min(money[i - 1][j - 1], money[i - 1][j + 1]);
			}
			else 
				money[i][j] =  min(money[i - 1][j] + price[i], money[i - 1][j + 1]);
	}

	long long ans = money[n][0];

	for (int i = 1; i <= n; i++) {
		ans = min(ans, money[n][i]);
	}

	cout << ans;
	cin >> ans;
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<long long> hemo(75000);
vector<long long> sum(75000);
int amount = 1;
int need_sum = 1;

int main() {
	freopen("hemoglobin.in", "r", stdin);
	freopen("hemoglobin.out", "w", stdout);

	int n; 
	cin >> n;
	sum[0] = 0;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;

		if (s[0] == '+') {
			s = s.substr(1, s.length());
			hemo[amount] = stoi(s);
			sum[amount] = sum[amount - 1] + hemo[amount];
			amount++;
		}
		else if (s[0] == '-') {
			amount--;
			cout << hemo[amount] << '\n';
		}
		else {
			long long k;
			s = s.substr(1, s.length());
			k = stoi(s);
			long long summa = sum[amount-1] - sum[amount - k-1];
			cout << summa << '\n';
		}
							
	
	}
	return 0;
}

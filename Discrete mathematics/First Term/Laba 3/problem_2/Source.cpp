#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <iomanip>  

using namespace std;

vector<int> v;

void to_binary(long long a, long long n) {
	cout.width(log2(n));
	cout.fill(0);
	long long b = 0;
	v.clear();
	if (a == 0 || a == 1) {
		cout << setw(log2(n)) << setfill('0') << a;
		return;
	}
	else
		while (a != 1) {
			v.push_back(a % 2);
			a /= 2;
		}
	v.push_back(1);

	for (int i = v.size() - 1; i >= 0; i--) {
		b = b * 10 + v[i];
	}
	cout << setw(log2(n)) << setfill('0') << b;
	return;
}

long long factorial(long long a) {
	if (a == 0) {
		return 1;
	}
	else return a*factorial(a - 1);
}

long long gray(unsigned long long b) {
	return b ^ (b >> 1);
}

int main() {

	std::ios::sync_with_stdio(false);

	freopen("gray.in", "r", stdin);
	freopen("gray.out", "w", stdout);

	long long n;
	cin >> n;
	n = (long long)pow(2, n);

	for (long long i = 0; i < n; i++) {
		to_binary(gray(i), n);
		cout << '\n';
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <iomanip>  

using namespace std;

vector<int> v;

long long length;

string to_binary_string(long long n, long long length)
{
	string r = "";
	string result = "";
	if (n == 1 || n == 0)
		r = (char)n + 48;
	else
	{
		while (n != 1) {
			
			r += (char)(n % 2) +(48);
			n = n >> 1;
		}
		r += '1';
	}
	for (int i = r.size() - 1; i >= 0; i--) {
		result += r[i];
	}
	for (int i = result.size(); i < length; i++) {
		result = '0' + result;
	}
	return result;
}

string to_ternary_string(long long n, long long length)
{
	string r = "";
	string result = "";
	if (n == 1 || n == 0 || n == 2)
		r = (char)n + 48;
	else
	{
		while (n > 2) {
			int a = n % 3;
			char c = (char)a;
			r += (c + 48);
			n /= 3;
		}
		r += ((char)n + 48);
	}
	for (int i = r.size() - 1; i >= 0; i--) {
		result += r[i];
	}

	for (int i = result.size(); i < length; i++) {
		result = '0' + result;
	}

	return result;


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



string cycle(string s) {
	string result = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0')
			result += '1';
		else if (s[i] == '1')
			result += '2';
		else
			result += '0';
	}
	return result;
}

void antigray(long long a, long long length) {
	string s = to_ternary_string(a, length);
	cout << s << '\n';
	s = cycle(s);
	cout << s << '\n';
	s = cycle(s);
	cout << s << '\n';
}

void chaincode(long long n) {
	/*
	vector<string> v(pow(2, n));
	string result = "";
	for (int i = 0; i < n; i++) {
		result += "0";
	}
	v[0] = result;

	for (int i = 1; i < pow(2,n); i++) {
		string res = v[i - 1];
		res = res.substr(1, res.size() - 1);
		res += "1";
		auto p = find(v.begin(), v.end(), res);
		if (p == v.end()) {
			v[i] = res;
		}
		else {
			res = res.substr(0, res.size() - 1) + "0";
			p = find(v.begin(), v.end(), res);
			if (p == v.end()) {
				v[i] = res;
			}
			else
				break;
		}
	}
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << '\n';
	}
	*/
	vector<bool> v(pow(2, n)+1, true);
	vector<long long> a(pow(2, n));
	a[0] = 0;
	for (int i = 1; i < pow(2, n); i++) {
		long long tmp = (((a[i - 1] << 1)+1)&(long)(pow(2, n) - 1));
		if (v[tmp]) {
			a[i] = (tmp);
			v[tmp] = false;
		}
		else {
			tmp = ((a[i-1] << 1)&(long)(pow(2, n) - 1));
			if (v[tmp]) {
				a[i] = (tmp);
				v[tmp] = false;
			}
			else break;
		}

	}
	for (int i = 0; i < pow(2, n); i++) {
		cout << to_binary_string(a[i],n) << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("chaincode.in", "r", stdin);
	freopen("chaincode.out", "w", stdout);

	long long n;
	cin >> n;

	chaincode(n);

	cin >> n;
	return 0;
}
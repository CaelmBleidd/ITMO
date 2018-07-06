#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <iomanip>  

using namespace std;

string to_binary_string(long long n, long long length)
{
	string r = "";
	string result = "";
	if (n == 1 || n == 0)
		r = (char)n + 48;
	else
	{
		while (n != 1) {
			long long a = n % 2;
			r += (a + 48);
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
	vector<bool> v(pow(2, n) + 1, true);
	vector<long long> a(pow(2, n));
	a[0] = 0;
	for (int i = 1; i < pow(2, n); i++) {
		long long tmp = (((a[i - 1] << 1) + 1)&(long)(pow(2, n) - 1));
		if (v[tmp]) {
			a[i] = (tmp);
			v[tmp] = false;
		}
		else {
			tmp = ((a[i - 1] << 1)&(long)(pow(2, n) - 1));
			if (v[tmp]) {
				a[i] = (tmp);
				v[tmp] = false;
			}
			else break;
		}

	}
	for (int i = 0; i < pow(2, n); i++) {
		cout << to_binary_string(a[i], n) << '\n';
	}
}

string next_permutations(string s) {
	long long min;
	for (int i = s.size() - 2; i >= 0; i--) {
		if (s[i] < s[i + 1]) {
			min = i + 1;
			for (int j = i + 1; j < s.size(); j++) {
				if (s[j] < s[min] && s[j]>s[i]) {
					min = j;
				}
			}
			swap(s[i], s[min]);
			reverse(s.begin() + i + 1, s.end());
			return s;
		}

	}
	return s;
}
/*
string next_choose(string s, long long n, long long k) {
	string tmp = "";
	for (int i = 0; i < k ; i++) {
		tmp += s[i];
	}
	tmp += (n + 49);
	long long i = k - 1;
	while (i >= 0 && tmp[i + 1] - tmp[i] < 2) {
		i--;
	}
	tmp[i]++;
	for (int j = i + 1; j < k; j++) {
		tmp[j] = tmp[j - 1] + 1;
	}
	for (long long b = 0; b < k; b++) {
		s[b] = tmp[b];
	}
	return s;
}
*/

vector<long long> next_choose (vector<long long> Array, long long n, long long k) {

	vector<long long> tmp = Array;
	tmp.push_back(n + 1);
	long long i = k - 1;
	while (i >= 0 && tmp[i + 1] - tmp[i] < 2) {
		i--;
	}
	tmp[i]++;
	for (int j = i + 1; j < k; j++) {
		tmp[j] = tmp[j - 1] + 1;
	}
	vector<long long> result;
	for (long long b = 0; b < k; b++) {
		result.push_back(tmp[b]);
	}
	return result;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("choose.in", "r", stdin);
	freopen("choose.out", "w", stdout);

	long long n, k;
	cin >> n >> k;

	vector<vector<long long> > Array((1));

	for (int i = 1; i <= k; i++) {
		Array[0].push_back(i);
	}
	for (int j = 0; j < Array[0].size(); j++)
		cout << Array[0][j] << ' ';
	cout << '\n';

	long long amount = factorial(n) / (factorial(k)*(factorial(n - k)));
	for (int i = 1; i != amount; i++) {
		Array.push_back(next_choose(Array[i-1], n, k));
		for (int j = 0; j < Array[i].size(); j++)
			cout << Array[i][j] << ' ';
		cout << '\n';
	}
	return 0;
}
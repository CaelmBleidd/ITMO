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
	vector<long long> n(a + 1);
	n[0] = 1;
	for (int i = 1; i < a + 1; i++) {
		n[i] = n[i - 1] * i;
	}
	return n[a];
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

string next_brackets(string s) {
	long long close = 0, open = 0;

	for (long long i = s.size() - 1; i >= 0; i--) {
		if (s[i] == '(') {
			open++;
			if (close > open)
				break;
		}
		else
			close++;
	}
	s = s.substr(0, s.size() - open - close);
	if (s == "")
		return "No Solution";

	else {
		s += ')';
		for (long long j = 1; j <= open; j++) {
			s += '(';
		}
		for (long long j = 1; j < close; j++) {
			s += ')';
		}
		return s;
	}
}

vector<long long> next_choose(vector<long long> Array, long long n, long long k) {
	vector<long long> qqq(1, -1);
	vector<long long> tmp = Array;
	tmp.push_back(n + 1);
	long long i = k - 1;
	while (i >= 0 && tmp[i + 1] - tmp[i] < 2) {
		i--;
	}
	if (i >= 0) {
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
	else return qqq;
}

long long catalans(long long n) {
	vector<long long> a(1000);
	a[0] = 1;
	a[1] = 1;
	for (int i = 2; i < 15; i++) {
		for (int j = 0; j < i; j++) {
			a[i] += (a[j] * a[i - 1 - j]);
		}
	}
	return a[n];
}

vector<long long> next_partition(vector<long long> a) {
	a[a.size() - 1]--;
	a[a.size() - 2]++;

	if (a[a.size() - 2] > a[a.size() - 1]) {
		a[a.size() - 2] += a[a.size() - 1];
		a.pop_back();
	}
	else
		while (a[a.size() - 2] * 2 <= a[a.size() - 1]) {
			a.push_back(a[a.size() - 1] - a[a.size() - 2]);
			a[a.size() - 2] = a[a.size() - 3];
		}

	return a;
}

vector<long long> amount_perm(long long n) {
	vector<long long> a(n + 1);
	a[0] = 0;
	a[1] = 1;
	for (int i = 2; i <= n; i++) {
		a[i] = factorial(i);
	}
	return a;
}

long long perm2num(vector<long long> a, long long n) {
	vector<bool> was(19, false);
	vector<long long> p = amount_perm(n);

	long long number = 0;
	for (long long i = 1; i <= n; i++) {
		for (long long j = 1; j < a[i]; j++) {
			if (!was[j])
				number += p[n - i];
		}
		was[a[i]] = true;
	}
	return number;
}

long long amount_choose(long long n, long long k) {
	long long result = factorial(n) / (factorial(k)*(factorial(n - k)));
	return result;
}

vector<long long> num2choose(long long n, long long k, long long m) {
	vector<vector<long long> > C(k + 1);
	for (int i = 0; i < C.size(); i++)
		C[i].resize(n + 1);


	for (int i = 0; i <= k; i++) {
		for (int j = i; j <= n; j++) {
			C[i][j] = amount_choose(j, i);
		}
	}
	C[0][n] = 1;
	long long next = 1;

	vector <long long> choose;

	while (k > 0) {
		if (m < C[k - 1][n - 1]) {
			choose.push_back(next);
			k--;
		}
		else
		{
			m -= C[k - 1][n - 1];
		}
		n--;
		next++;
	}

	return choose;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("nextpartition.in", "r", stdin);
	freopen("nextpartition.out", "w", stdout);

	string s; 
	cin >> s; 

	int n = 0; 

	long long number;
	
	vector<long long> v;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '=') {
			n = i + 1;
			string d = s.substr(0, i);
			number = stoi(d); 
		}
		else if (s[i] == '+') {
			string d = s.substr(n, i - n);
			v.push_back(stoi(d));
			n = i + 1;
		}
	}
	v.push_back(stoi(s.substr(n, s.size()  - n)));

	if (v.size() == 1)
		cout << "No solution";
	else {
		v = next_partition(v);
		cout << number << '=';
		for (int i = 0; i < v.size()-1; i++) {
			cout << v[i] << '+';
		}
		cout << v[v.size() - 1];
	}
	return 0;
}
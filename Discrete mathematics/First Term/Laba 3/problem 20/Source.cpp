#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <iomanip>  
#include <algorithm>

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
/*
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
*/

vector <long long> next_permutations(vector<long long> v) {
	long long min;
	for (int i = v.size() - 2; i >= 0; i--) {
		if (v[i] < v[i + 1]) {
			min = i + 1;
			for (int j = i + 1; j < v.size(); j++) {
				if (v[j] < v[min] && v[j]>v[i]) {
					min = j;
				}
			}
			swap(v[i], v[min]);
			reverse(v.begin() + i + 1, v.end());
			return v;
		}

	}
	v.assign(v.size(), 0);
	return v;
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
	double res = 1;
	for (int i = 1; i <= k; ++i)
		res = res * (n - k + i) / i;
	return (long long)(res + 0.01);
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

vector<long long> subsets(long long a, long long n) {
	string str = to_binary_string(a, n);

	vector<long long> aa;
	for (int i = str.size() - 1; i >= 0; i--) {
		if (str[i] != '0') {
			aa.push_back(str.size() - i);
		}
	}

	return aa;
}

long long choose2num(vector<long long> choose, long long n, long long k) {
	long long number = 0;

	vector<vector<long long> > C(k + 1);
	for (int i = 0; i < C.size(); i++)
		C[i].resize(n + 1);


	for (int i = 0; i <= k; i++) {
		for (int j = i; j <= n; j++) {
			C[i][j] = amount_choose(j, i);
		}
	}
	C[0][n] = 1;

	for (long long i = 1; i <= k; i++) {
		for (long long j = choose[i - 1] + 1; j < choose[i]; j++) {
			number += C[k - i][n - j];
		}
	}
	return number;
}


string num2brackets(long long n, long long k) {
	k++;
	vector<vector<long long> > d;
	for (int i = 0; i < n * 2 + 1; i++) {
		vector<long long> v(n + 1);
		d.push_back(v);
	}
	for (int i = 0; i < 2 * n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			d[i][j] = 0;
		}
	}
	d[0][0] = 1;

	for (int i = 0; i<n * 2; ++i)
		for (int j = 0; j < n + 1; ++j) {
			if (j + 1 < n + 1)
				d[i + 1][j + 1] += d[i][j];
			if (j > 0)
				d[i + 1][j - 1] += d[i][j];
		}

	long long depth = 0;
	string s = "";
	for (long long i = 0; i < 2 * n; i++) {
		if (d[2 * n - (i + 1)][depth + 1] >= k) {
			s += '(';
			depth++;
		}
		else {
			k -= d[2 * n - (i + 1)][depth + 1];
			s += ')';
			depth--;
		}
	}
	return s;
}

vector<vector<long long>> fill_d(long long n) {
	vector<vector<long long> > d;
	for (int i = 0; i < n * 2 + 1; i++) {
		vector<long long> v(n + 1);
		d.push_back(v);
	}
	for (int i = 0; i < 2 * n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			d[i][j] = 0;
		}
	}

	d[0][0] = 1;
	for (int i = 0; i<n * 2; ++i)
		for (int j = 0; j < n + 1; ++j) {
			if (j + 1 < n + 1)
				d[i + 1][j + 1] += d[i][j];
			if (j > 0)
				d[i + 1][j - 1] += d[i][j];
		}
	return d;
}

string num2brackets2(long long n, long long k) {
	k++;
	vector<vector<long long> > d;
	d = fill_d(n);

	long long depth = 0;
	string s = "";
	vector<char> stack(2 * n);

	for (long long i = n * 2 - 1; i != -1; i--) {
		long long tmp;
		if (depth + 1 < n + 1)
			tmp = d[i][depth + 1] << ((i - depth - 1) / 2);
		else
			tmp = 0;
		if (tmp >= k) {
			s += '(';
			stack.push_back('(');
			depth++;
			continue;
		}
		k -= tmp;

		if (stack.size() > 0 && stack[stack.size() - 1] == '(' && depth > -1) {
			tmp = d[i][depth - 1] << ((i - depth + 1) / 2);
		}
		else tmp = 0;

		if (tmp >= k) {
			s += ')';
			stack.pop_back();
			depth--;
			continue;
		}
		k -= tmp;

		if (depth + 1 < n + 1) {
			tmp = d[i][depth + 1] << ((i - depth - 1) / 2);
		}
		else
			tmp = 0;
		if (tmp >= k) {
			s += '[';
			stack.push_back('[');
			depth++;
			continue;
		}
		k -= tmp;
		s += ']';
		stack.pop_back();
		depth--;
	}
	return s;
}

vector<int> next_binary_vector(vector<int> v) {
	long long i = v.size() - 1;
	while (i >= 0) {
		if (v[i] == 0) {
			v[i] = 1;
			for (int j = i + 1; j < v.size(); j++) {
				v[j] = 0;
			}
			return v;
		}
		else
			i--;
	}
	v.clear();
	return v;
}

vector<int> pre_binary_vector(vector<int> v) {
	long long i = v.size() - 1;
	while (i >= 0) {
		if (v[i] == 1) {
			v[i] = 0;
			for (int j = i + 1; j < v.size(); j++) {
				v[j] = 1;
			}
			return v;
		}
		else
			i--;
	}
	v.clear();
	return v;
}

vector <long long> prev_permutations(vector<long long> v) {
	long long max;
	for (int i = v.size() - 2; i >= 0; i--) {
		if (v[i] > v[i + 1]) {
			max = i + 1;
			for (int j = i + 1; j < v.size(); j++) {
				if (v[j] > v[max] && v[j]<v[i]) {
					max = j;
				}
			}
			swap(v[i], v[max]);
			reverse(v.begin() + i + 1, v.end());
			return v;
		}

	}
	v.assign(v.size(), 0);
	return v;
}

vector<long long> next_multi(vector<long long> v) {
	long long min;
	for (int i = v.size() - 2; i >= 0; i--) {
		if (v[i] < v[i + 1]) {
			min = i + 1;
			while (min<v.size() - 1 && v[min + 1]>v[i]) {
				min++;
			}
			swap(v[i], v[min]);
			reverse(v.begin() + i + 1, v.end());
			return v;
		}

	}
	v.assign(v.size(), 0);
	return v;
}



void part2sets(vector<long long> v, long long n, long long k, long long i, long long j) {

	if (i == n && j != k)
		return;
	else if (i == n)
	{
		vector<string> v_2(k);
		for (long long i = 0; i < k; i++) {
			string s = "";
			v_2.push_back(s);
		}
		for (long long i = 0; i < n; i++) {
			v_2[v[i]] += to_string(i + 1) + ' ';
		}
		sort(v_2.begin(), v_2.end());
		for (string i : v_2) {
			if (i.size() != 0) {
				cout << i << '\n';
			}
		}
		cout << '\n';
	}

	else {
		for (int b = 0; b < j + 1; b++) {
			v[i] = b;
			if (b == j) {
				part2sets(v, n, k, i + 1, j + 1);
			}
			else {
				part2sets(v, n, k, i + 1, j);
			}
		}
	}

}

long long brackets2num2(string s, long long n) {
	vector<vector<long long> > d;
	for (int i = 0; i < n * 2 + 1; i++) {
		vector<long long> v(n + 1);
		d.push_back(v);
	}
	for (int i = 0; i < 2 * n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			d[i][j] = 0;
		}
	}
	d[0][0] = 1;

	for (int i = 0; i<n * 2; ++i)
		for (int j = 0; j < n + 1; ++j) {
			if (j + 1 < n + 1)
				d[i + 1][j + 1] += d[i][j];
			if (j > 0)
				d[i + 1][j - 1] += d[i][j];
		}
	
	long long num, balance;
	num = 0, balance = 0;
	vector<char> v;
	long long dn = n * 2;

	for (int i = 0; i < dn; i++) {
		if (s[i] == '(') {
			v.push_back(s[i]);
			balance++;
			continue;
		}

		long long ndepth = balance + 1;
		if (balance < n) {
			num += d[2 * n - i - 1][ndepth] * pow(2, ((2 * n - i - 1 - ndepth )/ 2));
		}

		if (s[i] == ')') {
			v.pop_back();
			balance--;
			continue;
		}

		if (v.size() > 0 && v[v.size() - 1] == '(' && balance > 0) {
			ndepth = balance - 1;
			num += d[2 * n - i - 1][ndepth] * pow(2, ((2 * n - i - ndepth) / 2));
		}

		if (s[i] == '[') {
			v.push_back(s[i]);
			balance++;
			continue;
		}

		if (balance < n) {
			ndepth = balance + 1;
			num += d[2 * n - i - 1][ndepth] *pow(2, ((2 * n - i - 1 - ndepth) / 2));
		}

		if (s[i] == ']') {
			v.pop_back();
			balance--;
		}
	}
	return num;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("brackets2num2.in", "r", stdin);
	freopen("brackets2num2.out", "w", stdout);

	long long n = 0;
	string s; 
	cin >> s;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(' || s[i] == '[')
			n++;
	}
	
	cout << brackets2num2(s, n);


	return 0;
}
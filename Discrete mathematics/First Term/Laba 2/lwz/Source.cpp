#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;


int main() {
	freopen("lzw.in", "r", stdin);
	freopen("lzw.out", "w", stdout);

	string str;
	cin >> str;

	map<string, int> m;
	string tmp = "";
	int count = 25;
	char c;
	char d = 'a';
	for (int i = 0; i < 26; i++) {
		string ssss = "";
		ssss += d++;
		m[ssss] = i;
	}
	
	for (int i = 0; i < str.length(); i++) {
		c = str[i];
		tmp += c;
		if (m.count(tmp) == 0) {
			m[tmp] = ++count;

			tmp = tmp.substr(0, tmp.length() - 1);
			cout << m[tmp] << ' ';
			tmp = c;
		}
	}
	
	if (!m.empty()) {
		cout << m[tmp];
	}
	

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

vector<char> v(26);

int index(char a) {
	for (int i = 0; i < 26; i++) {
		if (v[i] == a)
			return i;
	}
}

void sdvig(int n) {
	int a = v[n]; 
	for (int i = n; i >0; i--)
	{
		v[i] = v[i - 1];
	}
	v[0] = a;
}

int main() {
	freopen("mtf.in", "r", stdin);
	freopen("mtf.out", "w", stdout);

	string s;
	cin >> s;
	char a = 'a';


	for (int i = 0; i < 26; i++)
	{
		v[i] = a++;
	}



	for (int i = 0; i < s.length(); i++) {
		int d = index(s[i])+1;
		cout << d  << ' ';
		sdvig(d-1);
	}

	return 0;
}
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int main() {
	freopen("postfix.in", "r", stdin);
	freopen("postfix.out", "w", stdout);

	vector<int> v;
	char s;
	while (cin >> s) {
		if (v.size() == 0 || v.size() == 1)
			v.push_back(s - 48);
		else if (s >= '0' && s <= '9')
			v.push_back(s - 48);
		else if (s == '+') {
			int a = v[v.size() - 2];
			int b = v[v.size() - 1];
			v.pop_back();
			v.pop_back();
			int c = a + b;
			v.push_back(c);
		}
		else if (s == '*') {
			int a = v[v.size() - 2];
			int b = v[v.size() - 1];
			v.pop_back();
			v.pop_back();
			int c = a * b;
			v.push_back(c);
		}
		else if (s == '-') {
			int a = v[v.size() - 2];
			int b = v[v.size() - 1];
			v.pop_back();
			v.pop_back();
			int c = a - b;
			v.push_back(c);
		}

		
	}
	cout << v[v.size()-1];

	return 0;
}

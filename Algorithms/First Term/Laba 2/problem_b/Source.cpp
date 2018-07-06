#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isOpen(char a) {
	if (a == '(' || a == '{' || a == '[')
		return true;
	else
		return false;
}

bool isSameType(char a, char b) {
	if (a == '(' && b == ')' || a == '{' && b == '}' || a == '[' && b == ']')
		return true;
	else return false;
}

int main() {
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);

	vector<char> v;
	string s;
	cin >> s;

	for (int i = 0; i < s.size(); i++) {
		if (v.size() == 0 && !(isOpen(s[i]))) {
			cout << "NO";
			return 0;
		}
		else if (isOpen(s[i])) {
			v.push_back(s[i]);
		}
		else if (isSameType(v[v.size() - 1], s[i])) {
			v.pop_back();
		}
		else if (!isSameType(v[v.size() - 1], s[i]))
		{
			cout << "NO";
			return 0;
		}
	}

	if(v.size()==0)
		cout << "YES";
	else cout << "NO";

	return 0;
}

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	freopen("decode.in", "r", stdin);
	freopen("decode.out", "w", stdout);
	vector<char> v;


	string s;
	cin >> s;

	for (int i = 0; i < s.size(); i++){
		if (v.size() == 0)
			v.push_back(s[i]);
		else {
			if (s[i] == v[v.size() - 1]) {
				v.pop_back();
			}
			else
				v.push_back(s[i]);
		}
	}

	for (char i : v)
		cout << i;

	

	return 0;
}

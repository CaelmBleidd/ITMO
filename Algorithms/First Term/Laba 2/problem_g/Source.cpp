#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <List>
#include <deque>

using namespace std;


int main() {
	std::ios::sync_with_stdio(false);
	freopen("hospital.in", "r", stdin);
	freopen("hospital.out", "w", stdout);
	long long n;

	cin >> n;
	deque<long long> first;
	deque<long long> second;


	for (long long p = 0; p < n; p++) {
		char c;
		cin >> c;

		if (c == '+') {
			long long a;
			cin >> a;
			second.push_back(a);
		}
		else if (c == '*') {
			long long a;
			cin >> a;
			second.push_front(a);
		}
		else if (c == '-') {
			cout << *first.begin() << '\n';
			first.pop_front();
		//	first.push_back(*second.begin());
		//	second.pop_front();
		}
		if (first.size() < second.size()) {
			first.push_back(*second.begin());
			second.pop_front();
		}
	}



	return 0;
}
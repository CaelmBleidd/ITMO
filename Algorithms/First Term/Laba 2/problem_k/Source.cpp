#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;



int main() {
	freopen("kenobi.in", "r", stdin);
	freopen("kenobi.out", "w", stdout);
	int size = 0;
	long long n; 
	cin >> n;
	deque<long long> first;
	deque<long long> second;
	int k = 0; 

	for (int i = 0; i < n; i++) {
		string s; 
		cin >> s;
		if (k % 2 == 0) {
			if (s == "add") {
				int d;
				cin >> d;
				second.push_back(d);
				if (first.size() < second.size()-1) {
					first.push_back(*second.begin());
					second.pop_front();
				}
				size++;
			}
			else if (s == "take") {
				if (size > 0) {
					second.pop_back();
					if (first.size() > second.size()) {
						second.push_front(*(first.end() - 1));
						first.pop_back();
					}
					size--;
				}
			}
			else if (s == "mum!"  ) {
				if (size>= 2) {
					k++;
					if (first.size() < second.size()) {
						first.push_front(*(second.end() - 1));
						second.pop_back();
					}
				}
			}
		}
		else {
			if (s == "add") {
				int d;
				cin >> d;
				first.push_back(d);
				if (second.size() < first.size()-1) {
					second.push_back(*first.begin());
					first.pop_front();
				}
				size++;
			}
			else if (s == "take") {
				if (size > 0) {
					first.pop_back();
					if (second.size() > first.size()) {
						first.push_front(*(second.end() - 1));
						second.pop_back();
					}
					size--;
				}
			}
			else if (s == "mum!") {
				if (size >= 2) {
					k++;
					if (second.size() < first.size()) {
						second.push_front(*(first.end() - 1));
						first.pop_back();
					}
				}
			}
		}
		
		
	}




	cout << size << '\n';
	if (k % 2 == 0) {
		for (int i = 0; i < first.size(); i++) {
			cout << first[i] << ' ';
		}
		for (int i = 0; i < second.size(); i++) {
			cout << second[i] << ' ';
		}
	}
	else {
		for (int i = 0; i < second.size(); i++) {
			cout << second[i] << ' ';
		}
		for (int i = 0; i < first.size(); i++) {
			cout << first[i] << ' ';
		}
	}
	return 0;
}
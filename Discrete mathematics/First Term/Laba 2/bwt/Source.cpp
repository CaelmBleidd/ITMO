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
	freopen("bwt.in", "r", stdin);
	freopen("bwt.out", "w", stdout);

	string str;
	cin >> str;
	
	vector<vector<char>> arr(str.size());
	long long count = 0;
	long long length = str.size();

	for (long long i = 0; i < str.size(); i++) {
		arr[i].resize(str.size());
		for (long long j = 0; j < str.size(); j++) {
			arr[i][j] = str[(long long)(j+count)%length];
		}
		count++;
	}
	vector<string> v(length);
	for (long long i = 0; i < length; i++) {
		for (long long j = 0; j < length; j++) {
			v[i] += arr[i][j];
		}
	}
	sort(v.begin(), v.end());
	string stroka;
	for (long long i = 0; i < length; i++) {
		stroka += v[i][length - 1];
	}
	cout << stroka;
	return 0;
}

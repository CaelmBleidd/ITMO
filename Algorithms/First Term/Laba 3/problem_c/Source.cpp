#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <iomanip>  
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	const long long MOD = 1e9;

	long long n; 
	cin >> n;
	long long s = 0;
	vector<vector<long long>> can = { {4,6,-1},
								{6,8,-1},
								{7,9,-1},
								{4,8,-1},
								{0,3,9},
								{-1,-1,-1},
								{0,1,7},
								{2,6,-1},
								{1,3,-1},
								{2,4,-1} };
	vector<long long> ends = { 0,1,1,1,1,1,1,1,0,1 };
	vector<long long> tmp(10);

	for (long long i = 0; i < n; i++) {
		s = 0;
		for (long long j = 0; j < 10; j++) {
			
			s += ends[j];
			tmp[j] = 0;
			
		}

		for (long long j = 0; j < 10; j++) {
			long long l;
			if (ends[j])
				l = 0;
			else
				l = 3;

			for (; l < 3; l++) {
				if (can[j][l] == -1) {
					continue;
				}
				else {
					tmp[can[j][l]] += ends[j];
					tmp[can[j][l]];
				}
			}
		}

		for (long long j = 0; j < 10; j++) {
			ends[j] = tmp[j];
			ends[j] %= MOD;
		}
	}
	s %= MOD;
	cout << s;
	cin >> s;
	return 0;
}
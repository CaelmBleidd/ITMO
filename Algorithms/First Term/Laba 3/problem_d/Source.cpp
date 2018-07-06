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

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	string first, second; 

	cin >> first; 
	cin >> second; 

	long long first_length = first.size(); 
	long long second_length = second.size();
	long long left, dia, above, amount; 

	if (first_length == 0)
		cout << second_length;
	else if (second_length == 0)
		cout << first_length; 
	else {
		vector<vector<long long>> d;
		for (long long i = 0; i <= first_length; i++) {
			vector<long long> a(second_length+1); 
			d.push_back(a);
		}
		for (long long i = 0; i <= second_length; i++) {
			d[0][i] = i;
		}
		for (long long i = 0; i <= first_length; i++) {
			d[i][0] = i;
		}
		for (long long i = 1; i <= first_length; i++) {
			for (long long j = 1; j <= second_length; j++) {
				if (first[i - 1] != second[j - 1])
					amount = 1;
				else
					amount = 0;
				dia = d[i - 1][j - 1], above = d[i - 1][j], left = d[i][j - 1];
				d[i][j] = dia + amount > min(above + 1, left + 1) ? min(above + 1, left + 1) : dia + amount;
			}
		}
		cout << d[first_length][second_length];
	}
	return 0;
}
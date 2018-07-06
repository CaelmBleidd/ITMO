#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm> 

using namespace std;
long stack[1000001];
long min_stack[1000001];


int main() {
	freopen("stack-min.in", "r", stdin);
	freopen("stack-min.out", "w", stdout);


	long n;
	cin >> n;
	long stack_size = 0;
	long min_size = 0;

	for (int i = 0; i < n; i++) {
		long a;
		cin >> a;
		if (a == 1) {
			long b;
			cin >> b;
			stack[stack_size++] = b;

			if (stack_size == 1) {
				min_stack[min_size++] = b;
			}
			else {
				 min_stack[min_size] = min(b,min_stack[min_size-1]);
				 min_size++;
			}
		}
		if (a == 2) {
			stack_size--;
			min_size--;
		}
		if (a == 3) {
			cout << min_stack[min_size - 1] << '\n';
		}
	}

	return 0;
}

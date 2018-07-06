#include <vector> 
#include <iostream>
#include <string>
#include <fstream> 
#include <iomanip>  

using namespace std;



int main() {
	
	int n;
	cin >> n;
	int size = pow(2, n);
	vector<int> v(size);
	vector<int> fo(size);
	vector<int> result(size);

	int count = size - 1;

	for (int i = 0; i < size; i++)
	{
		int a, b;
		cin >> a >> b;
		fo[i] = a;
		v[i] = b;
	}

	for (int i = 0; i < size; i++) {
		int j = 0; 
		result[i] = v[0];
		while (j < count)
		{
			v[j] = v[j] ^ v[j + 1];
			j++;
		}
		count--;
	}

	for (int i = 0; i < size; i++) {
		cout << setw(n) << setfill('0') << fo[i] << " " << result[i] << '\n';
	}
	return 0;




}
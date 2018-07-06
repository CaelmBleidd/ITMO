#include <vector> 
#include <iostream>
#include <string>
#include <fstream> 
#include <iomanip>  

using namespace std;

bool one = true, two = true, three = true, four = true, five = true;

void zero(int a, string b) {
	if (b[0] != '0')
		one = false;	
}

void edinica(int a, string b) {
	if (b[a - 1] != '1')
		two = false;
		
}

void self(int a, string b) {
	int i = 0;
	int j = a - 1;
	if (a == 1)
		three = false;
	while (i < j) {
		if (b[i++] == b[j--])
		{
			three = false;
			break;
		}
	}
}

void mono( string b) {
	int shift = b.size() / 2;
	if(b.size()!=1)
	{
		string left = b.substr(0, shift);
		string right = b.substr(shift, shift);
		for (int i = 0; i < shift; i++) {
			if (left[i] > right[i])
				four = false;
		}
		//if (left > right)
	//		four = false;
		if (b.size() > 2) {
			mono(left);
			mono(right);
		}
	}

}

void lin(int a, string b) {

	vector<int> result(a);
	string d = b;
	int count = a - 1;
	vector<int> v(a);
	for (int i = 0; i < a; i++)
		v[i] = b[i] - 48;

	for (int i = 0; i < a; i++) {
		int j = 0;
		result[i] = v[0];
		while (j < count)
		{
			v[j] = v[j] ^ v[j + 1];
			j++;
		}
		count--;
	}

	for (int i = 0; i < a; i++)
	{
		if ((i != 0 && i != 1 && i != 2 && i != 4 && i != 8 && i != 16) && result[i] == 1)
			five = false;

	}

}

int main() {
	
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int c;
		cin >> c;
		int a = pow(2, c);
		string b;
		cin >> b;
		if (one)
			 zero(a, b);
		if (two)
			 edinica(a, b);
		if (three)
			 self(a, b);
		if (four)
			mono( b);
		if (five)
			lin(a, b);
		
	}
	if (!one && !two && !three && !four && !five) {
		cout << "YES";
		return 0;
	}
	else {
		cout << "NO";
		return 0;
	}
}
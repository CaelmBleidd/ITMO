 #include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {
	freopen("formation.in", "r", stdin);
	freopen("formation.out", "w", stdout);


	long long n, m;
	cin >> n >> m;
	
	vector<pair<long long, long long> > v(n+50);

	//left I J Ч соответствует команде ЂI, встать в строй слева от J.ї
	//Х right I J Ч ЂI, встать в строй справа от J.ї
	//	Х leave I Ч ЂI, выйти из стро€.ї
	//	Х name I Ч ЂI, назвать соседей.ї

	for (int p = 0; p < m; p++) {
		string s; 
		cin >> s;
		if (s == "left") {
			long long i, j;
			cin >> i >> j;
			v[i].second = j;
			v[i].first = v[j].first;
			v[v[j].first].second = i;
			v[j].first = i;
		}
		else if (s == "right") {
			long long i, j;
			cin >> i >> j;
			v[i].first = j;
			v[i].second = v[j].second;
			v[v[j].second].first = i;
			v[j].second = i;
		}

		else if (s == "leave") {
			long long i;
			cin >> i;

			v[v[i].second].first = v[i].first;
			v[v[i].first].second = v[i].second;
			v[i].first = 0;
			v[i].second = 0;

		}
		else {
			long long i;
			cin >> i;
			cout << v[i].first << ' ' << v[i].second << '\n';
		}
	}



	return 0;
}
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int parent[1000000];
int siz[1000000];


class hyyy {
public:
	int min;
	int max; 
	int count;
};
vector<hyyy> r(1000000);

void make_set(int v) {
	parent[v] = v;
	siz[v] = 1;
	r[v].count = 1;
	r[v].min = v;
	r[v].max = v;
}

int find_set(int v) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a != b) {
		if (siz[a] < siz[b])
			swap(a, b);
		parent[b] = a;
		siz[a] += siz[b];
		r[a].count = siz[a];
		if (r[a].min > r[b].min)
			r[a].min = r[b].min;
		if (r[a].max < r[b].max)
			r[a].max = r[b].max;
	}
}

void get(int n) {
	int a = find_set(n);
	cout << r[a].min << ' ' << r[a].max << ' ' << r[a].count << '\n';
}


int main() {
	freopen("dsu.in", "r", stdin);
	freopen("dsu.out", "w", stdout);

	int n;
	cin >> n;
	for (int i = 0; i <= n; i++) {
		make_set(i);
	}

	string s;
	while(cin >> s) {
		int n; 
		cin >> n;
		if (s == "union") {
			int b; 
			cin >> b;
			union_sets(n, b);
		}
		else {
			get(n);
		}
	}


	return 0;
}
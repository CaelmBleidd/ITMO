#include <vector> 
#include <iostream>
#include <string>
#include <fstream> 

using namespace std;
vector <vector<int> > g, gr;
vector <int> used, list, Color, Answer;

void dfs1(int v)
{
	int i, to;
	used[v] = 1;
	for (i = 0; i < g[v].size(); i++)
	{
		to = g[v][i];
		if (!used[to]) dfs1(to);
	}
	list.push_back(v);
}

void dfs2(int v, int c)
{
	int i, to;
	Color[v] = c;
	for (i = 0; i < gr[v].size(); i++)
	{
		to = gr[v][i];
		if (Color[to] == -1) dfs2(to, c);
	}
}

int Conv(int v)
{
	if (v >= 0) return 2 * v - 2;
	return 2 * (-v) - 1;
}

int main() {
	int n, m;
	cin >> n >> m;
	g.resize(2 * n); 
	gr.resize(2 * n);

	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		a = Conv(a); b = Conv(b);
		g[a ^ 1].push_back(b);   g[b ^ 1].push_back(a);
		gr[b].push_back(a ^ 1);  gr[a].push_back(b ^ 1);
	}

	used.assign(2 * n, 0);
	for (int i = 0; i < 2 * n; i++)
		if (!used[i]) dfs1(i);

	Color.assign(2 * n, -1);
	for (int i = 0, c = 0; i < 2 * n; i++)
	{
		int v = list[2 * n - i - 1];
		if (Color[v] == -1) dfs2(v, c++);
	}

	for (int i = 0; i < 2 * n; i += 2)
		if (Color[i] == Color[i ^ 1])
		{
			cout << "YES";
			return 0;
		}
	cout << "NO";
	return 0;
}
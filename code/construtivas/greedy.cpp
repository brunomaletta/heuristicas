#include <bits/stdc++.h>

using namespace std;

// O(n^2)
vector<int> solve(int n, vector<vector<int> >& g, vector<int>& label) {
	vector<vector<int> > adj(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) for (int j : g[i]) adj[i][j] = 1;
	vector<int> deg(n, 0);
	for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++)
		if (adj[i][j]) deg[i]++, deg[j]++;
	
	vector<pair<int, int> > v;
	for (int i = 0; i < n; i++) v.push_back({deg[i], i});
	sort(v.begin(), v.end());

	vector<int> ans;
	for (int i = 0; i < n; i++) {
		bool bom = true;
		for (int j : ans) if (adj[v[i].second][j]) bom = false;
		if (bom) ans.push_back(v[i].second);
	}

	vector<int> anss;
	for (int i : ans) anss.push_back(label[i]);
	return anss;
}

int main() {
	int n, m; cin >> n >> m;
	vector<vector<int> > g(n);
	while (m--) {
		int a, b; cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	vector<int> label;
	for (int i = 0; i < n; i++) label.push_back(i);

	auto ans = solve(n, g, label);
	//for (auto i : ans) cout << i << " ";
	cout << ans.size() << endl;
}

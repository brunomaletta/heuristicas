#include <bits/stdc++.h>

using namespace std;

// O(2^n * m)
vector<int> solve(int n, vector<vector<int> >& g, vector<int>& label) {
	// testa todos os subconjuntos
	vector<pair<int, int> > ar;
	for (int i = 0; i < n; i++) for (int j : g[i]) ar.push_back({i, j});
	vector<int> best;
	for (int i = 0; i < (1<<n); i++) {
		bool ci = true;
		for (auto edge : ar) if (i>>edge.first&1 and i>>edge.second&1) ci = false;
		if (ci and __builtin_popcount(i) > best.size()) {
			best.clear();
			for (int j = 0; j < n; j++) if (i>>j&1) best.push_back(label[j]);
		}
	}
	return best;
}

int main() {
	int n, m; cin >> n >> m;
	vector<vector<int> > g(n);
	while (m--) {
		int a, b; cin >> a >> b; a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	vector<int> label;
	for (int i = 0; i < n; i++) label.push_back(i+1);

	auto ans = solve(n, g, label);
	for (auto i : ans) cout << i << " ";
	cout << endl;
}

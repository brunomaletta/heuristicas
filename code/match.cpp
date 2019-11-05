#include <bits/stdc++.h>

using namespace std;

struct graph {
	vector<vector<int> > g;
	int n;
	vector<int> label, match, pai, base, vis;
	queue<int> q;

	graph(int n_) : n(n_) {
		g.resize(n);
		label.resize(n);
		for (int i = 0; i < n; i++) label[i] = i;
		match.resize(n);
		pai.resize(n);
		base.resize(n);
		vis.resize(n);
	}

	void setLabel(int i, int l) {
		label[i] = l;	
	}

	void addEdge(int a, int b) {
		g[a].push_back(b);
		g[b].push_back(a);
	}

	void contract(int u, int v, bool first = 1) {
		static vector<bool> bloss;
		static int l;
		if (first) {
			bloss = vector<bool>(n, 0);
			vector<bool> teve(n, 0);
			int k = u; l = v;
			while (1) {
				teve[k = base[k]] = 1;
				if (match[k] == -1) break;
				k = pai[match[k]];
			}
			while (!teve[l = base[l]]) l = pai[match[l]];
		}
		while (base[u] != l) {
			bloss[base[u]] = bloss[base[match[u]]] = 1;
			pai[u] = v;
			v = match[u];
			u = pai[match[u]];
		}
		if (!first) return;
		contract(v, u, 0);
		for (int i = 0; i < n; i++) if (bloss[base[i]]) {
			base[i] = l;
			if (!vis[i]) q.push(i);
			vis[i] = 1;
		}
	}

	int getpath(int s) {
		for (int i = 0; i < n; i++) base[i] = i, pai[i] = -1, vis[i] = 0;
		vis[s] = 1; q = queue<int>(); q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int i : g[u]) {
				if (base[i] == base[u] or match[u] == i) continue;
				if (i == s or (match[i] != -1 and pai[match[i]] != -1))
					contract(u, i);
				else if (pai[i] == -1) {
					pai[i] = u;
					if (match[i] == -1) return i;
					i = match[i];
					vis[i] = 1; q.push(i);
				}
			}
		}
		return -1;
	}

	int blossom() {
		int ans = 0;
		match = vector<int>(n, -1);
		for (int i = 0; i < n; i++) if (match[i] == -1)
			for (int j : g[i]) if (match[j] == -1) {
				match[i] = j;
				match[j] = i;
				ans++;
				break;
			}
		for (int i = 0; i < n; i++) if (match[i] == -1) {
			int j = getpath(i);
			if (j == -1) continue;
			ans++;
			while (j != -1) {
				int p = pai[j], pp = match[p];
				match[p] = j;
				match[j] = p;
				j = pp;
			}
		}
		return ans;
	}

	vector<pair<int, int> > getMatchingEdges() {
		blossom();
		vector<pair<int, int> > ret;
		for (int i = 0; i < n; i++) if (match[i] > i) ret.push_back({i, match[i]});
		return ret;
	}
};

vector<int> solveGreedy(graph g) {
	vector<vector<int> > adj(g.n, vector<int>(g.n, 0));
	for (int i = 0; i < g.n; i++) for (int j : g.g[i]) adj[i][j] = 1;
	vector<int> deg(g.n, 0);
	for (int i = 0; i < g.n; i++) for (int j = i+1; j < g.n; j++)
		if (adj[i][j]) deg[i]++, deg[j]++;
	
	vector<pair<int, int> > v;
	for (int i = 0; i < g.n; i++) v.push_back({deg[i], i});
	sort(v.begin(), v.end());

	vector<int> ans;
	for (int i = 0; i < g.n; i++) {
		bool bom = true;
		for (int j : ans) if (adj[v[i].second][j]) bom = false;
		if (bom) ans.push_back(v[i].second);
	}

	vector<int> anss;
	for (int i : ans) anss.push_back(g.label[i]);
	return anss;
}

vector<int> solve(graph g) {
	auto match = g.getMatchingEdges();
	vector<int> ci(g.n, 1);
	for (auto i : match) ci[i.first] = ci[i.second] = 0;

	vector<int> ans;
	for (int i = 0; i < g.n; i++) if (ci[i]) ans.push_back(g.label[i]);
	if (!ans.size()) return solveGreedy(g);

	// tira vizinhanca fechada do CI
	vector<int> bom(g.n, 1);
	for (int i = 0; i < g.n; i++) if (ci[i]) {
		bom[i] = 0;
		for (int j : g.g[i]) bom[j] = 0;
	}

	vector<int> caras;
	for (int i = 0; i < g.n; i++) if (bom[i]) caras.push_back(i);

	// cria grafo
	graph newg((int)caras.size());
	map<int, int> newid;
	for (int i = 0; i < caras.size(); i++) newid[caras[i]] = i;
	for (int i : caras) for (int j : g.g[i])
		if (bom[j]) newg.addEdge(newid[i], newid[j]);
	for (int i : caras) newg.setLabel(newid[i], g.label[i]);

	vector<int> newans = solve(newg);
	for (int i : newans) ans.push_back(i);

	return ans;
}

int main() {
	int n, m; cin >> n >> m;
	graph g(n);
	while (m--) {
		int a, b; cin >> a >> b;
		g.addEdge(a, b);
	}

	auto ans = solve(g);
	for (auto i : ans) cout << i << " ";
	cout << endl;
}

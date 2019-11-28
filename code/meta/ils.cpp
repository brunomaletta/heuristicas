#include <bits/stdc++.h>

using namespace std;

struct graph {
	vector<set<int> > g;
	int n;

	graph(int n_) : n(n_), g(n_) {}

	void addEdge(int a, int b) {
		g[a].insert(b);	
		g[b].insert(a);	
	}

	void local(set<int>& S) {
		for (int a : S) for (int b : S) {
			if (a == b) continue;
			auto S2 = S;
			S2.erase(a);
			S2.erase(b);
			vector<int> A;
			for (int i = 0; i < n; i++) {
				if (S2.count(i)) continue;
				bool bom = 1;
				for (int j : S2) if (g[i].count(j)) bom = 0;
				if (bom) A.push_back(i);
			}
			for (int i = 0; i < A.size(); i++)
				for (int j = i+1; j < A.size(); j++)
					for (int k = j+1; k < A.size(); k++) {
						int ii = A[i], jj = A[j], kk = A[k];
						if (g[ii].count(jj)) continue;
						if (g[ii].count(kk)) continue;
						if (g[kk].count(jj)) continue;
						S2.insert(ii);
						S2.insert(jj);
						S2.insert(kk);
						S = S2;
						local(S);
						return;
					}
		}
	}

	void disturb(set<int>& S) {
		int tira = max(0, min(int(S.size())-2, rand() % int(S.size())));

		for (int j = 0; j < tira; j++) {
			vector<int> cara;
			for (int i : S) cara.push_back(i);
			S.erase(cara[rand()%cara.size()]);
		}

		int coloca = 0;
		vector<int> v;
		for (int i = 0; i < n; i++) v.push_back(i);
		random_shuffle(v.begin(), v.end());
		for (int i : v) {
			if (S.count(i)) continue;
			bool bom = 1;
			for (int j : S) if (g[i].count(j)) bom = 0;
			if (!bom) continue;
			coloca++;
			S.insert(i);
			if (coloca == tira) break;
		}
	}

	set<int> greedy() {
		vector<pair<int, int> > v;
		for (int i = 0; i < n; i++) v.push_back({g[i].size(), i});
		sort(v.begin(), v.end());

		vector<int> ans;
		for (int i = 0; i < n; i++) {
			bool bom = true;
			for (int j : ans) if (g[v[i].second].count(j)) bom = false;
			if (bom) ans.push_back(v[i].second);
		}
		return set<int>(ans.begin(), ans.end());
	}

	int ils() {
		auto S = greedy();
		int ans = 0;
		for (int i = 0; i < 10; i++) {
			disturb(S);
			local(S);
			ans = max(ans, int(S.size()));
		}
		return ans;
	}
};

int main() {
	int n, m; cin >> n >> m;
	graph g(n);
	while (m--) {
		int a, b; cin >> a >> b;
		g.addEdge(a, b);
	}

	cout << g.ils() << endl;
}

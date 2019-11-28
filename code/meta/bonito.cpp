#include <bits/stdc++.h>

using namespace std;

struct graph {
	vector<vector<int> > g;
	vector<vector<int> > mat;
	int n;

	graph(int n_) : n(n_), g(n_) {
		mat = vector<vector<int> >(n, vector<int>(n, 0));	
	}

	void addEdge(int a, int b) {
		g[a].push_back(b);	
		g[b].push_back(a);	
		mat[a][b] = mat[b][a] = 1;
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
				for (int j : S2) if (mat[i][j]) bom = 0;
				if (bom) A.push_back(i);
			}
			for (int i = 0; i < A.size(); i++)
				for (int j = i+1; j < A.size(); j++)
					for (int k = j+1; k < A.size(); k++) {
						int ii = A[i], jj = A[j], kk = A[k];
						if (mat[ii][jj]) continue;
						if (mat[ii][kk]) continue;
						if (mat[kk][jj]) continue;
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
			for (int j : S) if (mat[i][j]) bom = 0;
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
			for (int j : ans) if (mat[v[i].second][j]) bom = false;
			if (bom) ans.push_back(v[i].second);
		}
		return set<int>(ans.begin(), ans.end());
	}

	int ils(int it) {
		auto S = greedy();
		int ans = 0;
		while (it--) {
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

	cout << g.ils(50) << endl;
}

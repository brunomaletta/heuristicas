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

	vector<pair<int, int> > gentup(int nlow, int ntup) {
		vector<pair<int, int> > v;
		for (int i = 0; i < n; i++) v.push_back({g[i].size(), i});
		sort(v.begin(), v.end());

		vector<pair<int, pair<int, int> > > P;
		for (int i = 0; i < min(nlow, (int)v.size()); i++)
			for (int j = i+1; j < min(nlow, (int)v.size()); j++) {
				int vi = v[i].second, vj = v[j].second;
				if (mat[vi][vj]) continue;
				int sigma = 0;
				for (int ii = 0; ii < n; ii++)
					if (!mat[vi][ii] and !mat[vj][ii]) sigma++;
				P.push_back({sigma, {vi, vj}});
			}
		
		sort(P.rbegin(), P.rend());
		vector<pair<int, int> > lambda;
		for (int i = 0; i < min(ntup, int(P.size())); i++)
			lambda.push_back(P[i].second);
		return lambda;
	}

	void updatedeg(map<int, int>& deg, set<int>& A, set<int>& S) {
		for (auto i : A) {
			deg[i] = 0;
			for (int j = 0; j < n; j++) if (!S.count(j) and mat[i][j])
				deg[i]++;
		}
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

	int mis(int nlow, int ntup, int niter, int iscoeff, double alpha) {
		auto lambda = gentup(nlow, ntup);
		set<int> Sstar;
		map<int, int> deg;
		for (int k = 0; k < lambda.size(); k++) {
			int v1k = lambda[k].first, v2k = lambda[k].second;
			for (int i = 0; i < niter; i++) {
				set<int> S = {v1k, v2k};
				set<int> A;
				for (int j = 0; j < n; j++) {
					if (j == v1k or j == v2k) continue;
					if (mat[j][v1k] or mat[j][v2k]) continue;
					A.insert(j);
				}
				while (A.size()) {
					updatedeg(deg, A, S);
					vector<int> C;
					int mindeg = 0x3f3f3f3f;
					for (int i : A) mindeg = min(mindeg, deg[i]);
					for (int i : A) if (deg[i] <= (1+alpha)*mindeg)
						C.push_back(i);
					if (!C.size()) break;
					int vstar = C[rand()%int(C.size())];
					A.erase(vstar);
					for (int w : g[vstar]) A.erase(w);
					S.insert(vstar);
					updatedeg(deg, A, S);
				}
				if (S.size() > iscoeff)  local(S);
				if (S.size() > Sstar.size()) Sstar = S;
			}
		}
		return Sstar.size();
	}
};

int main() {
	int n, m; cin >> n >> m;
	graph g(n);
	while (m--) {
		int a, b; cin >> a >> b;
		g.addEdge(a, b);
	}

	cout << g.mis(50, 20, 10, 11, 0.1) << endl;
}

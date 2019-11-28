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

	vector<pair<int, int> > gentup(int nlow, int ntup) {
		vector<pair<int, int> > v;
		for (int i = 0; i < n; i++) v.push_back({g[i].size(), i});
		sort(v.begin(), v.end());

		vector<pair<int, pair<int, int> > > P;
		for (int i = 0; i < min(nlow, (int)v.size()); i++)
			for (int j = i+1; j < min(nlow, (int)v.size(); j++) {
				int vi = v[i].second, vj = v[j].second;
				if (g[vi].count(vj)) continue;
				int sigma = 0;
				for (int ii = 0; ii < n; ii++)
					if (!g[vi].count(ii) and !g[vj].count(ii)) sigma++;
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
			for (int j = 0; j < n; j++) if (!S.count(j) and g[i].count(j))
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
					if (g[j].count(v1k) or g[j].count(v2k)) continue;
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

//	int a = -1, b;
//	for (int i = 0; i < n and a == -1; i++)
//		for (int j = i+1; j < n; j++) if (!g.g[i].count(j)) {
//			a = i, b = j;
//			break;
//		}
//
//	set<int> S = {a, b};
//	g.local(S);
//	cout << S.size() << endl;

	cout << g.mis(20, 5, 3, 11, 0.1) << endl;
}

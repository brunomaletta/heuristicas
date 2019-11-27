#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

void imprime(vector<vector<int> > g){
	for(int i = 0; i < g.size(); i++){
		cout << i << ":";
		for(int j : g[i])
			cout << " " << j;
		cout << endl;
	}
}

void imprime(vector<pair<int, pair<int, int> > > v){
	for(int i = 0; i < v.size(); i++)
		cout << "(" << v[i].second.first << ", " << v[i].second.second << ") -> " << v[i].first << endl;
}

vector<vector<int> > floyd(vector<vector<int> > g){
	int n = g.size();
	vector<vector<int> > ret (n, vector<int> (n, 0));

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			if(i == j)
				ret[i][j] = 0;
			else if(g[i][j] == 1)
				ret[i][j] = 1;
			else
				ret[i][j] = INF;
		}

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				ret[j][k] = min(ret[j][k], ret[j][i] + ret[i][k]);

	return ret;
}
vector<pair<int, pair<int, int> > > to_pair(vector<vector<int> > g){
	vector<pair<int, pair<int, int> > > ret;
	for(int i = 1; i < g.size(); i++)
		for(int j = 0; j < i; j++)
			ret.push_back(make_pair(g[i][j] , make_pair(i, j)));
	return ret;
}

bool pode(int u, set<int> &vis, set<int> &ret, vector<vector<int> > &g){
	if(vis.count(u))
		return false;
	vis.insert(u);
	for(int i : ret)
		if(g[i][u])
			return false;
	return true;
}

set<int> select(vector<vector<int> > g, vector<pair<int, pair<int, int> > > v){
	set<int> ret, vis;
	for(auto i : v){
		int u = i.second.first;
		if(pode(u, vis, ret, g))
			ret.insert(u);

		u = i.second.second;
		if(pode(u, vis, ret, g))
			ret.insert(u);
	}

	return ret;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<int> > g(n, vector<int> (n, 0));
	for(int i = 0; i < m; i++){
		int a, b; cin >> a >> b;
		g[a][b] = g[b][a] = 1;
	}

	vector<vector<int> > a = floyd(g);
	vector<pair<int, pair<int, int> > > v = to_pair(a);
	sort(v.rbegin(), v.rend());
	set<int> s = select(g, v);

	cout << s.size() << endl;
	//for(int i : s)
	//	cout << i << " "; cout << endl;

	return 0;
}

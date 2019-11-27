#include <bits/stdc++.h>
using namespace std;

struct graph{
	int n;
	vector<vector<int> > m;
	map<int, set<int> > g;

	void print(){
		for(auto i : g){
			cout << i.first << ":";
			for(auto j : i.second)
				cout << " " << j; cout << endl;
		}
		cout << endl;
	}

	void build(int size){
		n = size;
		m.resize(n);
		for(int i = 0; i < n; i++)
			m[i].resize(n, 0);
		for(int i = 0; i < n; i++){
			g[i].insert(i);
			g[i].erase(i);
		}

	}

	void add(int a, int b){
		m[a][b] = m[b][a] = 1;
		g[a].insert(b);
		g[b].insert(a);
	}

	void hide(int v){
		for(int i : g[v])
			g[i].erase(v);
		g.erase(v);
	}

	void show(int v){
		//just to make sure it exists
		g[v].insert(v);
		g[v].erase(v);

		for(auto &i : g){
			if(m[v][i.first] == 0)
				continue;

			g[i.first].insert(v);
			g[v].insert(i.first);
		}
			
	}

	set<int> ramsey(){
		if(g.size() == 0)
			return set<int> ();

		//remove the first element and its neighborhood
		int v = g.begin() -> first;
		set<int> neighborhood = g[v];
		neighborhood.insert(v);
		for(int i : neighborhood)
			this->hide(i);
		set<int> i1 = ramsey();
		i1.insert(v);

		//insert everyone back and remove the rest
		set<int> nonNeighbors;
		for(auto &i : g)
			nonNeighbors.insert(i.first);
		for(int i : nonNeighbors)
			g.erase(i);
		for(int i : neighborhood)
			this->show(i);
		this->hide(v);
		set<int> i2 = ramsey();

		for(int i : neighborhood)
			this->show(i);

		if(i1.size() > i2.size())
			return i1;
		return i2;
	}

	void indSet(){
		set<int> ind = ramsey();

		//for(int i : ind)
		//	cout << i << " "; cout << endl;
		cout << ind.size() << endl;
	}

};

int main(){
	int n, m;
	cin >> n >> m;
	graph g;
	g.build(n);
	for(int i = 0; i < m; i++){
		int a, b; cin >> a >> b;
		g.add(a, b);
	}

	g.indSet();

	return 0;
}

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

	set<int> hideNeighbors(int v){
		set<int> neighborhood = g[v];
		neighborhood.insert(v);
		for(int i : neighborhood)
			this->hide(i);
		return neighborhood;
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

	void showAll(){
		for(int i = 0; i < n; i++)
			if(g.count(i) == 0)
				show(i);
	}

	set<int> greedy(){
		if(g.size() == 0)
			return set<int> ();

		int v = g.begin() -> first;
		for(auto &i : g)
			if(i.second.size() < g[v].size())
				v = i.first;

		auto neighborhood = hideNeighbors(v);
		auto i1 = greedy();
		i1.insert(v);

		for(int i : neighborhood)
			show(i);

		return i1;
	}

	set<int> removeOne(set<int> s0){
		auto best = s0;

		for(int i : s0){
			showAll();
			hideNeighbors(i);
			auto curr = greedy();

			if(curr.size() > best.size())
				best = curr;
		}

		return best;
	}

	set<int> insertOne(set<int> s0){
		auto best = s0;

		for(int i = 0; i < n; i++){
			if(s0.count(i)) continue;

			auto curr = s0;
			for(int j = 0; j < n; j++)
				if(m[i][j]) curr.erase(j);


			g.clear();
			curr.insert(i);
			for(int j = 0; j < n; j++){
				if(curr.count(j)) continue;
				bool add = true;
				for(int k : curr)
					if(m[j][k]){
						add = false;
						break;
					}
				if(add)
					show(j);
			}

			set<int> aux = greedy();
			for(int j : aux)
				curr.insert(j);
			
			if(curr.size() > best.size())
				best = curr;
		}
		return best;
	}

	set<int> vnd(set<int> s0){
		auto best = s0;
		bool stop = false;

		while(!stop){
			stop = true;

			auto insert = insertOne(best);
			if(best != insert){
				best = insert;
				stop = false;
				continue;
			}

			if(best != removeOne(best)){
				best = removeOne(best);
				stop = false;
			}
		}

		return best;
	}

	set<int> perturb(set<int> s0){
		int q = rand() % s0.size();
		vector<int> v(s0.begin(), s0.end());
		for(int i = 0; i < q; i++)
			s0.erase(v[i]);

		showAll();
		for(int i : s0)
			hideNeighbors(i);
		auto s1 = greedy();
		for(int i : s1)
			s0.insert(i);
		return s0;
	}

	void maxIndSet(int maxIter){
		auto s = greedy();
		auto best = s;

		for(int i = 0; i < maxIter; i++){
			s = perturb(s);
			auto curr = vnd(s);
			if(curr.size() > best.size())
				best = curr;
		}
		cout << best.size() << endl;
	}

};


int main(){
	int n, m;
	cin >> n >> m;
	graph g; g.build(n);
	for(int i = 0; i < m; i++){
		int a, b; cin >> a >> b;
		g.add(a, b);
	}

	g.maxIndSet(10);

	return 0;
}

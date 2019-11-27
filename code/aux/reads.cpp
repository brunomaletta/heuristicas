#include <bits/stdc++.h>
using namespace std;

#define NUM 20

int main(){
	vector<double> v(NUM);
	for(int i = 0; i < NUM; i++){
		int a; double b; cin >> a >> b;
		cout << a << endl;
		v[i] = b/1e6;
	}
	for(double i : v)
		cout << i << endl;

	return 0;
}

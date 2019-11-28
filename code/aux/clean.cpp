#include <bits/stdc++.h>
using namespace std;

int main(){
	string s; int S;
	
	cin >> s >> s >> s;
	cout << s << " ";
	cin >> S;
	cout << S << endl;

	for(int i = 0; i < S; i++){
		cin >> s >> S;
		cout << S-1 << " ";
		cin >> S;
		cout << S-1 << endl;
	}

	return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main(){
	string s; int S;
	
	cin >> s >> s >> s;
	cout << s << " ";
	cin >> S;
	cout << S << endl;

	int ss = S;
	for(int SS = 0; SS < ss; SS++){
		cin >> s >> S;
		cout << S-1 << " ";
		cin >> S;
		cout << S-1 << endl;
	}

	return 0;
}

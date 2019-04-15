#include <iostream>
#include <string>
#include <vector>

using namespace std;

void prefix(vector<int> &z, const string &P) {
	z.resize(P.size());
	z[0] = 0;
	for (unsigned int i = 1; i < z.size(); ++i) {
		int k = z[i - 1];
		while (k > 0 && P[k] != P[i])
			k = z[k - 1];
		z[i] = k + (P[k] == P[i] ? 1 : 0);
	}
}

int main() {
	string P, T;
	vector<int> answer, z;
	unsigned int k = 0;
	cin >> P >> T;
	prefix(z, P);
	for (unsigned int i = 0; i < T.size(); ++i) {
		while (k > 0 && (k >= P.size() || P[k] != T[i]))
			k = z[k - 1];
		if (T[i] == P[k]) 
			k++;
		if (k == P.size())
			answer.push_back(i - k + 1);
	}
	if (answer.size() > 0) {
		for (unsigned int i = 0; i < answer.size() - 1; i++)
			cout << answer[i] << "," ;
		cout << answer.back();
	}
	else cout << -1 << endl;
	return 0;
}

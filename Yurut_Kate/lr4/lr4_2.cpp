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
	string A, B;
	vector<int> z;
	cin >> A >> B;
	if (A.length() == B.length()) {
		string a = A + A;
		prefix(z, B);
		int k = 0;
		int answer = -1;
		for (int i = 0; i < a.size(); ++i) {
			while (k > 0 && B[k] != a[i])
				k = z[k - 1];
			if (B[k] == a[i])
				k++;
			if (k == B.length()) {
				answer = (i + 1 - B.length());
				break;
			}
		}
		cout << answer;
	}
	else cout << -1;
	return 0;
}

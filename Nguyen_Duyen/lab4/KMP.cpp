#include <iostream>
#include <vector>
#include <string>

using namespace std;

void computeLPSArray(string pat, int index, vector<int> &lps) {
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while (i < index) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if (len != 0)
				len = lps[len - 1];
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
}

void KMPseach(string pat, string txt, vector<int> *res) {
	int m = pat.length();
	int n = txt.length();
	vector<int> lps(m);
	computeLPSArray(pat, m, lps);
	int i = 0, j = 0;
	while (i < n) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == m) {
			res->push_back(i - j);
			j = lps[j - 1];	
		}

		else if (i < n && pat[j] != txt[i]) {
			if (j != 0)
				j = lps[j - 1];
			else
				i++;
		}
	}
}

int main()
{
	string P, T;
	vector<int> res;

	cin >> P >> T;

	KMPseach(P, T, &res);

	if (res.size() == 0) 
		cout << -1;

	else {
		for (size_t i = 0; i < res.size() - 1; i++) {
			cout << res[i] << ",";
		}cout << res.back();
	}
	system("pause");
	return 0;
}
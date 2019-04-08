#include <iostream>
#include <vector>
#include <string>

using namespace std;

void computeLPSArray(string pat, int index, vector<int> lps) {
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

int KMPseach(string pat, string txt) {
	int m = pat.length();
	int n = txt.length();
	if (m == n) {
		bool flag = false;
		vector<int> lps(m);
		computeLPSArray(pat, m, lps);
		int i = 0, j = 0;
		while (i < n) {
			if (pat[j] == txt[i]) {
				j++;
				i++;
				if (i == n && flag == false) {
					i = 0;
					flag = true;
				}
			}

			if (j == m)
				return i;

			else if (i < n && pat[j] != txt[i]) {
				if (j != 0)
					j = lps[j - 1];
				else
					i++;
			}
		}
		return -1;
	}
	else
		return -1;
}

int main()
{
	string P, T;

	cin >> P >> T;

	cout << KMPseach(T, P) << endl;
	system("pause");
	return 0;
}

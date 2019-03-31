#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector <int> prefix(string arr) {
	vector <int> p(arr.size());
	size_t j = 0;
	size_t i = 1;
	p[0] = 0;
	while (i < arr.length()) {
		if (arr[i] == arr[j]) {
			p[i] = j + 1;
			i++;
			j++;
		}
		else if (j == 0) {
			p[i] = 0;
			i++;
		}
		else {
			j = p[j - 1];
		}
	}
	return p;
}

int CYCLE_KMP(string s1, string s2) {
	vector <int> p = prefix(s2);
	size_t i = 0;
	size_t j = 0;
	if (s1.length() != s2.length()) {
		return -1;
	}
	else if (s1 == s2) {
		return 0;
	}
	else {
		while (true) {
			if (s1[i] == s2[j]) {
				i++;
				if (i==s1.length()) {
					i -= s1.length();
				}
				j++;
				if (j == s2.length()) {
					return s2.length() - i;
				}
			}
			else if (j != 0) {
				j = p[j - 1];
			}
			else {
				i++;
				if (i == s1.length()) {
					return -1;
				}
			}
		}
	}
}

int main() {
	string a;
	string b;
	getline(cin, a);
	getline(cin, b);
	cout<<CYCLE_KMP(b, a);
	return 0;
}
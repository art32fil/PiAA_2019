#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector <size_t> prefix_func(const string & s)
{
	vector <size_t> p(s.length());
	for (int i = 1; i < s.length(); i++)
	{
		int k = p[i - 1];
		while (k > 0 && s[i] != s[k]) 
			k = p[k - 1];
		if (s[i] == s[k]) 
			k++;
		p[i] = k;
	}
	return p;
}

int Shift(const string & s, const string & t)
{
	if (s.length() != t.length()) return -1;
	string temp = s + s;
	vector <size_t> q = prefix_func(t);
	int j = 0;
	int k = 0;
	int mean = -1;
	for (int i = 0; i < temp.length(); i++)
	{
		while (j > 0 && t[j] != temp[i]) j = q[j - 1];
		if (t[j] == temp[i]) j++;
		if (j == t.length())
		{
			mean = (i + 1 - t.length());
			break;
		}
	}
	return mean;
}

int main()
{
	string s, t;
	cin >> t;
	cin >> s;
	cout << Shift(t, s);
	return 0;
}

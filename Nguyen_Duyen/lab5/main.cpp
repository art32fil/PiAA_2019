#include <iostream>
#include <cstring>
#include <queue>
#include <bitset>
#include <algorithm>

using namespace std;

const int MAX = 150000;
const int alpb = 26;

bitset<4500> out[MAX];
int f[MAX];
int g[MAX][alpb];

struct result {
	int id;
	int num;
};

vector<result*> res;
result* resAdd(int i, int p) {
	result *temp = new result();
	temp->id = i;
	temp->num = p;
	return temp;
}

bool compare(result* a, result* b) {
	if (a->id == b->id)	return a->num < b->num;
	return(a->id < b->id);
}

int buildMatching(vector<string> str) {
	memset(out, 0, sizeof out);
	memset(g, -1, sizeof g);
	memset(f, -1, sizeof f);
	int states = 1;

	for (size_t i = 0; i < str.size(); i++) {
		string word = str[i];
		int cur_state = 0;

		for (size_t j = 0; j < word.size(); j++) {
			int id = word[j] - 'A';
			if (g[cur_state][id] == -1)
				g[cur_state][id] = states++;
			cur_state = g[cur_state][id];
		}
		out[cur_state].set(i);
	}

	for (int i = 0; i < alpb; i++) {
		if (g[0][i] == -1)
			g[0][i] = 0;
	}

	queue<int> q;
	for (int i = 0; i < alpb; ++i) {
		if (g[0][i] != 0) {
			f[g[0][i]] = 0;
		q.push(g[0][i]);
		}
	}

	while (!q.empty()) {
		int state = q.front();
		q.pop();

		for (int i = 0; i <= alpb; ++i) {
			if (g[state][i] != -1) {
				int fail = f[state];

				while (g[fail][i] == -1)
					fail = f[fail];

				fail = g[fail][i];
				f[g[state][i]] = fail;
				out[g[state][i]] = out[g[state][i]] | out[fail];
				q.push(g[state][i]);
			}
		}
	}
	 return states;
}

int findNextState(int cur_state, char nextInput) {
	int id = nextInput - 'A';
	while (g[cur_state][id] == -1)
		cur_state = f[cur_state];
	return g[cur_state][id];
}

void searchWords(vector<string> str, string text) {
	buildMatching(str);

	int cur_state = 0;
	for (size_t i = 0; i < text.size(); i++) {
		cur_state = findNextState(cur_state, text[i]);
		if (out[cur_state] != 0) {
			for (size_t j = 0; j < str.size(); j++) {
				if (out[cur_state].test(j)) {
					res.push_back(resAdd(i - str[j].size() + 2, j + 1));
				}
			}
		}
	}
	sort(res.begin(), res.end(), compare);
	for (size_t i = 0; i < res.size(); i++) {
		cout << res[i]->id << " " << res[i]->num << endl;
	}
}

int main()
{
	string T;
	int n;

	cin >> T >> n;
	vector<string> P;
	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;
		P.push_back(str);
	}

	searchWords(P, T);

	system("pause");
	return 0;
}

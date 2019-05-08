#include <iostream>
#include <cstring>
#include <queue>
#include <bitset>
#include <algorithm>

using namespace std;

const int MAX = 10000;
const int alpb = 26;

bitset<40> out[MAX]; 
int f[MAX]; 
int g[MAX][alpb];

struct result {
	int id;
	int num;
};

result* resAdd(int i, int p) {
	result *temp = new result();
	temp->id = i;
	temp->num = p;
	return temp;
}

bool compare(result* a, result* b) {
	if (a->id == b->id)	return a->num < b->num;
	return a->id < b->id;
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

void searchWords(vector<string> str, string text, vector<result*> &res) {
	buildMatching(str);

	int cur_state = 0;
	for (size_t i = 0; i < text.size(); i++) {
		cur_state = findNextState(cur_state, text[i]);
		if (out[cur_state] != 0) {
			for (size_t j = 0; j < str.size(); j++) {
				if (out[cur_state].test(j) ) {
					res.push_back(resAdd(i - str[j].size() + 2, j + 1));
				}
			}
		}
	}
	sort(res.begin(), res.end(), compare);
}

bool check(string text, vector<string> &str, vector<int> &j_len, vector<result*> &res, int cur_res, int depth, int cur_pos) {
	if (depth > str.size()) {
		if ((int)text.length() - cur_pos + 1 >= 0) {
			return true;
		}
		else
			return false;
	}
	for (int i = cur_res; i < res.size(); i++) {
		if (depth != 1 && res[i]->id > cur_pos)
			break;
		if (res[i]->num == depth && (depth == 1 && res[i]->id >= cur_pos || res[i]->id == cur_pos)) {
			bool flag = check(text, str, j_len, res, i + 1, depth + 1, res[i]->id + str[depth - 1].length() + j_len[depth - 1]);
			if (flag) {
				if (depth != 1) {
					return flag;
				}
				else {
					cout << res[i]->id << endl;
				}
			}
		}
	}
	return false;
}

int main()
{
	string T,key;
	char joker;
	cin >> T >> key >> joker;

	vector<result*> res;
	vector<string> P;
	
	vector<int> j_len;
	vector<int> pos_sub;
	int start_pos = 0;
	for (int i = 0; i < key.length(); i++) {
		if (key[i] != joker) {
			string pat;
			pos_sub.push_back(i + 1);
			for (int j = i; key[j] != joker && j < key.length(); j++) {
				pat += key[j];
				i++;
			}i--;
			if(pat.length()!=0)
				P.push_back(pat);
		}
		else {
			int k = 0;
			for (int j = i; key[j] == joker && j < key.length(); j++) {
				k++; i++;
			}i--;
			if (k != 0)
				j_len.push_back(k);
		}
	}
	if (pos_sub[0] != 1) {
		start_pos = pos_sub[0];
		j_len.erase(j_len.begin());
	}
	if (P.size() != j_len.size()) {
		j_len.push_back(0);
	}

	searchWords(P, T, res);

	check(T, P, j_len, res, 0, 1, start_pos);
	
	system("pause");
	return 0;
}

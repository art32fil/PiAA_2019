// PIAA_LR5_WildCard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <cstring>

using namespace std;

const int k = 5;
const string first_alphabet = "ACGTN";

struct bohr_vrtx
{
	int next_vrtx[k];           //next_vrtx[i] Ч номер вершины, в которую мы придем по символу с номером i в алфавите
	int pat_num;                //номер строки-образца, обозначаемого этой вершиной
	bool flag;                  //бит, указывающий на то, €вл€етс€ ли наша вершина исходной строкой
	int suff_link;              //суффиксна€ ссылка
	int auto_move[k];           //запоминание перехода
	int par;                    //вершина-отец в дереве
	unsigned char symb;         //символ на ребре от par к этой вершине
	int suff_flink;             //"хороша€" ссылка
	int pattern_num[40];
};

struct WildCardPattern
{
	size_t index;
	int pattern_num;

	explicit WildCardPattern(long long int o_index, int o_pat_num) : index(o_index), pattern_num(o_pat_num)
	{}
};

vector<bohr_vrtx> bohr;
vector<string> pattern;
vector<WildCardPattern> wc_patterns;

bohr_vrtx make_bohr_vrtx(int p, unsigned char c)
{
	bohr_vrtx v;
	memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
	memset(v.auto_move, 255, sizeof(v.auto_move));
	v.flag = false;
	v.suff_link = -1;
	v.par = p;
	v.symb = c;
	v.suff_flink = -1;
	memset(v.pattern_num, 255, sizeof(v.pattern_num));
	return v;
}

void bohr_init()
{
	bohr.push_back(make_bohr_vrtx(0, '\0'));
}

unsigned char get_number_from_alhabet(unsigned char symbol)
{
	for (size_t i = 0; i < first_alphabet.length(); i++)
	{
		if (symbol == first_alphabet[i])
		{
			return static_cast<unsigned char>(i);
		}
	}
	return 0;
}

void add_string_to_bohr(const string& s)
{
	int num = 0;
	for (size_t i = 0; i<s.length(); i++)
	{
		unsigned char ch = get_number_from_alhabet(s[i]);
		if (bohr[num].next_vrtx[ch] == -1)
		{
			bohr.push_back(make_bohr_vrtx(num, ch));
			bohr[num].next_vrtx[ch] = bohr.size() - 1;
		}
		num = bohr[num].next_vrtx[ch];
	}
	bohr[num].flag = true;
	pattern.push_back(s);
	//bohr[num].pat_num = pattern.size() - 1;
	for (size_t i = 0; i < 40; i++) 
	{
		if (bohr[num].pattern_num[i] == -1) {
			bohr[num].pattern_num[i] = pattern.size() - 1;
			break;
		}
	}
}

int get_auto_move(int v, unsigned char ch);

int get_suff_link(int v)
{
	if (bohr[v].suff_link == -1)
	{
		if (v == 0 || bohr[v].par == 0)
			bohr[v].suff_link = 0;
		else
			bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
	}
	return bohr[v].suff_link;
}

int get_auto_move(int v, unsigned char ch)
{
	if (bohr[v].auto_move[ch] == -1)
	{
		if (bohr[v].next_vrtx[ch] != -1)
		{
			bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
		}
		else
		{
			if (v == 0)
				bohr[v].auto_move[ch] = 0;
			else
				bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
		}
	}
	return bohr[v].auto_move[ch];
}

int get_suff_flink(int v)
{
	if (bohr[v].suff_flink == -1)
	{
		int u = get_suff_link(v);
		if (u == 0)
			bohr[v].suff_flink = 0;
		else
			bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);
	}
	return bohr[v].suff_flink;
}

void check(int v, int i)
{
	for (int u = v; u != 0; u = get_suff_flink(u))
	{
		if (bohr[u].flag)
		{
			for (size_t j = 0; j < 40; j++)
			{
				if (bohr[u].pattern_num[j] != -1) 
				{
					wc_patterns.push_back(WildCardPattern(i - pattern[bohr[u].pattern_num[j]].length(), bohr[u].pattern_num[j]));
				}
				else
					break;
			}
		}
	}
}

void find_all_pos(const string& s)
{
	int u = 0;
	for (size_t i = 0; i<s.length(); i++)
	{
		u = get_auto_move(u, get_number_from_alhabet(s[i]));
		check(u, i + 1);
	}
}

int divide_P(const string& P, char wild_card, vector<int>& patterns_pos)
{
	int counter_P = 0;
	string tmp;
	for (size_t i = 0; i<P.length(); i++)
	{
		if (P[i] == wild_card)
		{
			if (tmp.empty())
				continue;

			patterns_pos.push_back(i - tmp.length());
			counter_P++;
			add_string_to_bohr(tmp);
			tmp.clear();
		}
		else
		{
			tmp = tmp + P[i];
		}
	}

	if (!tmp.empty())
	{
		patterns_pos.push_back(P.length() - tmp.length());
		counter_P++;
		add_string_to_bohr(tmp);
	}

	return counter_P;
}

int main()
{
	vector<int> patterns_pos;
	char wild_card;
	string T, P;
	cin >> T >> P >> wild_card;
	
	bohr_init();
	int counter = divide_P(P, wild_card, patterns_pos);
	find_all_pos(T);

	int T_size = static_cast<int>(T.length());
	int P_size = static_cast<int>(P.length());

	vector<int> C(T_size, 0);

	for (size_t i = 0; i < wc_patterns.size(); i++)
	{
		if (wc_patterns[i].index < patterns_pos[wc_patterns[i].pattern_num])
			continue;
		C[wc_patterns[i].index - patterns_pos[wc_patterns[i].pattern_num]]++;
		if (C[wc_patterns[i].index - patterns_pos[wc_patterns[i].pattern_num]] == counter && wc_patterns[i].index - patterns_pos[wc_patterns[i].pattern_num] <= T_size - P_size)
			cout << wc_patterns[i].index - patterns_pos[wc_patterns[i].pattern_num] + 1 << endl;
	}

	system("pause");
	return 0;
}
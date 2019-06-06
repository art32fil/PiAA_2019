#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <sstream>
#define MAXSIZE 5

// Реализация Бора
struct bohr_vertex 
{
	int nextVertex[MAXSIZE];	 			// массив, где nextVertex[i] - номер вершины, в которую мы переходим по символу с номером i в алфавите
	bool isIt;								// бит, указывающий, я-я ли вершина исходной строкой
	int suffLink;							// суффиксная ссылка
	int autoMove[MAXSIZE];					// запоминание перехода автомата
	int parent;								// вершина - отец
	char symbol;							// символ на ребре от parent к этой вершине
    std::vector < int > patternNum;			// номер строки-образца, обозначающего вершиной nextVertex[i]
	bohr_vertex(){}
	bohr_vertex(int parent, char symbol)
	{
		for (int i = 0; i < MAXSIZE; i++)
		{
			nextVertex[i] = -1;
		}
        isIt = false;
		suffLink = -1;
        for (int i = 0; i < MAXSIZE; i++)
		{
			autoMove[i] = -1;
		}
		this->parent = parent;
		this->symbol = symbol;
		patternNum.resize(0);
	}
};

std::vector < bohr_vertex > bohr;
std::vector < std::string > pattern;

// Инициализация Бора
void ini()
{
    bohr_vertex v(0,0);
	bohr.push_back(v);
}


// Добавление образца в бор
void add(const std::string & s)
{
	int n = 0;
	for (int i = 0; i < s.length(); i++)
	{
		int ch;
		switch(s[i])
		{
			case 'A':
				ch = 0;
				break;
			case 'C':
				ch = 1;
				break;
			case 'G':
				ch = 2;
				break;
			case 'T':
				ch = 3;
				break;
			case 'N':
				ch = 4;
				break;
			default:
                ch = 5;
				break;
		}
		if (bohr[n].nextVertex[ch] == -1)	// нет ребра
		{   
			bohr_vertex v(n,ch);
			bohr.push_back(v);
			bohr[n].nextVertex[ch] = bohr.size() - 1;
		}
		n = bohr[n].nextVertex[ch];
	}
	bohr[n].isIt = true;
	pattern.push_back(s);
	bohr[n].patternNum.push_back(pattern.size() - 1);
	
}

int getAutoMove(int v, int ch);

// Получаем суффиксную ссылку
int getSuff(int v)
{
	if (bohr[v].suffLink == -1)
		if (v == 0 || bohr[v].parent == 0)
			bohr[v].suffLink = 0;
	else 
		bohr[v].suffLink = getAutoMove(getSuff(bohr[v].parent), bohr[v].symbol);
	return bohr[v].suffLink;
}

int getAutoMove(int v, int ch)
{
   if (bohr[v].autoMove[ch] == -1)
      if (bohr[v].nextVertex[ch] != -1)
         bohr[v].autoMove[ch] = bohr[v].nextVertex[ch];
      else
         if (v == 0)
            bohr[v].autoMove[ch] = 0;
         else
            bohr[v].autoMove[ch] = getAutoMove(getSuff(v), ch);
   return bohr[v].autoMove[ch];
}


void out(int v, int i, std::vector < int > & cnt, const std::vector < int > & len)
{
	 for(int u = v;u != 0;u = getSuff(u))
        if (bohr[u].isIt) 
		{
			//std::cout << i - pattern[bohr[u].patternNum].length() + 1 << " " << bohr[u].patternNum + 1 << std::endl;
			for (const auto &j : bohr[u].patternNum)
				if (i - len[j] < cnt.size()) cnt[i -len[j]]++;
		}
}

std::vector < int > patterns(std::stringstream& string_pattern, char joker)
{
	std::vector < int > len;
	int len_ = 0;
	std::string buf;
	while (getline(string_pattern, buf, joker))
	{
		if (buf.size() > 0)
		{
			len_ += buf.size();
			len.push_back(len_);
			add(buf);
		}
		len_++;
	}
	return len;
}

void out_2(const std::vector<int>& cnt, int t_size)
{
	for (int i = 0; i < t_size; i++)
		if ( cnt[i] == pattern.size())
			std::cout << i + 1 << std::endl;
}

void find(const std::string &s, std::vector < int > & cnt, const std::vector < int > & len)
{
	int u = 0;
	for(int i = 0; i < s.length(); i++)
	{
		int ch;
		switch(s[i])
		{
			case 'A':
				ch = 0;
				break;
			case 'C':
				ch = 1;
				break;
			case 'G':
				ch = 2;
				break;
			case 'T':
				ch = 3;
				break;
			case 'N':
				ch = 4;
				break;
			default:
				ch = 5;
				break;
		}
        u = getAutoMove(u, ch);
        out(u, i + 1, cnt, len);
    }
}
	
int main ()
{
   	ini();
	int n;
	std::string text, keyword;
	char j;
	std::cin >> text;
	std::cin >> keyword;
	std::cin >> j;
	std::stringstream str_stream(keyword);
	std::vector < int > cnt(text.size(), 0);
	std::vector < int > len = patterns(str_stream, j);
	find (text, cnt, len);
	out_2(cnt, text.size());
}

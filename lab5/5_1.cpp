#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#define MAXSIZE 6

	
// Реализация Бора
struct Bohr_v 
{
	int next_v[MAXSIZE];	 		// массив, где next_v[i] - номер вершины, в которую мы переходим по символу с номером i в алфавите
	int patternNum;					// номер строки-образца, обозначающего вершиной next_v[i]
	bool isIt;						// бит, указывающий, я-я ли вершина исходной строкой
	int suffLink;					// суффиксная ссылка
	int autoMove[MAXSIZE];			// запоминание перехода автомата
	int parent;						// вершина - отец
	char symbol;					// символ на ребре от parent к этой вершине
    Bohr_v(){}
	Bohr_v(int parent, char symbol)
	{
		for (int i = 0; i < MAXSIZE; i++)
		{
			next_v[i] = -1;
		}
        patternNum = 0;
        isIt = false;
		suffLink = -1;
        for (int i = 0; i < MAXSIZE; i++)
		{
			autoMove[i] = -1;
		}
		this->parent = parent;
		this->symbol = symbol;
	}
};

std::vector < Bohr_v > bohr;
std::vector < std::string > pattern;

// Инициализация Бора
void ini()
{
    Bohr_v v(0,0);
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
		if (bohr[n].next_v[ch] == -1)	// нет ребра
		{   Bohr_v v(n,ch);
			bohr.push_back(v);
			bohr[n].next_v[ch] = bohr.size() - 1;
		}
		n = bohr[n].next_v[ch];
	}
	bohr[n].isIt = true;
	pattern.push_back(s);
	bohr[n].patternNum = pattern.size() - 1;	
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
      if (bohr[v].next_v[ch] != -1)
         bohr[v].autoMove[ch] = bohr[v].next_v[ch];
      else
         if (v == 0)
            bohr[v].autoMove[ch] = 0;
         else
            bohr[v].autoMove[ch] = getAutoMove(getSuff(v), ch);
   return bohr[v].autoMove[ch];
}


void out(int v, int i)
{
	 for(int u = v;u != 0;u = getSuff(u))
        if (bohr[u].isIt) 
			std::cout << i - pattern[bohr[u].patternNum].length() + 1 << " " << bohr[u].patternNum + 1 << std::endl;
}

void find(const std::string &s)
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
        out(u, i + 1);
    }
}
	
int main ()
{
   	ini();
	int n;
	std::string text, keyword;
	std::cin >> text;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::cin >> keyword;
		add(keyword);
	}
	find (text);
}
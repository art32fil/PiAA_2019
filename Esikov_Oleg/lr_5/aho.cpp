#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct bohr_vertex
{
    int next_vertex[5]; //{A, C, G, T, N} алфавит
    bool flag;          //является ли концом подстроки
    int num;            //номер подстроки
    int parent;         //индекс родителя
    int sufflink;       //индекс перехода по суффиксальной ссылке
    int gotosymbol[5];  //индекс перехода по каждому символу
    int symboltoparent; //возвращает индекс символа, по которому переходится из родителя
    int goodsufflink;   //индекс перехода по хорошей суффиксальной ссылке
};

class Bohr
{
private:
    vector<bohr_vertex> bohr;
    string text;


public:
    Bohr()
    {
        bohr.push_back({{-1, -1, -1, -1, -1}, false, 0, 0, -1, {-1, -1, -1, -1, -1}, -1, -1});
        cin >> text;
        int N;
        cin >> N;
        for(int i(0); i < N; i++)
        {
            string temp;
            cin >> temp;
            push(temp, i+1);
        }
    }

    void push(string str, int number)
    {
        int len = str.size();
        int index = 0;
        int symbol;
        for(int i(0); i < len; i++)
        {
            switch(str.at(i))
            {
                case 'A':
                            symbol = 0;
                            break;
                case 'C':
                            symbol = 1;
                            break;
                case 'G':
                            symbol = 2;
                            break;
                case 'T':
                            symbol = 3;
                            break;
                case 'N':
                            symbol = 4;
                            break;
            }
            if(bohr[index].next_vertex[symbol] == -1)
            {
                bool isEnd = false;
                if(i == len-1)
                    isEnd = true;
                bohr.push_back({{-1, -1, -1, -1, -1}, isEnd, number, index, -1, {-1, -1, -1, -1, -1}, symbol, -1});
                bohr[index].next_vertex[symbol] = bohr.size() - 1;
            }
            index = bohr[index].next_vertex[symbol];
        }
    }

    int getSuffLink(int vertex)
    {
        if(bohr.at(vertex).sufflink == -1)
        {
            if(vertex == 0 || bohr.at(vertex).parent == 0)
                bohr.at(vertex).sufflink = 0;
            else
                bohr.at(vertex).sufflink = getLink(getSuffLink(bohr.at(vertex).parent), bohr.at(vertex).symboltoparent);
        }
        return bohr.at(vertex).sufflink;
    }

    int getLink(int vertex, int symbol)
    {
        if(bohr.at(vertex).gotosymbol[symbol] == -1)
        {
            if(bohr.at(vertex).next_vertex[symbol] != -1)
                bohr.at(vertex).gotosymbol[symbol] = bohr.at(vertex).next_vertex[symbol];
            else
                bohr.at(vertex).gotosymbol[symbol] = (vertex == 0) ? 0 : getLink(getSuffLink(vertex), symbol);
        }
        return bohr.at(vertex).gotosymbol[symbol];
    }

    int getGoodSuffLink(int vertex)
    {
        if(bohr.at(vertex).goodsufflink == -1)
        {
            int temp = getSuffLink(vertex);
            if(temp == 0)
                bohr.at(vertex).goodsufflink = 0;
            else
                bohr.at(vertex).goodsufflink = (bohr.at(temp).flag) ? temp : getGoodSuffLink(temp);
        }
        return bohr.at(vertex).goodsufflink;
    }

    void check(int v, int i)
    {
        for(int u(v); u != 0; u = getGoodSuffLink(u))
        {
            if(bohr.at(u).flag)
            {
                int delta = 0;
                int temp = u;
                while(bohr.at(temp).parent != 0)
                {
                    temp = bohr.at(temp).parent;
                    delta++;
                }
                cout << i - delta << " " << bohr.at(u).num << endl;
            }
        }
    }

    void AHO()
    {
        int vertex = 0, symbol = 0;
        for(int i(0); i < text.length(); i++)
        {
            switch(text.at(i))
            {
                case 'A':
                            symbol = 0;
                            break;
                case 'C':
                            symbol = 1;
                            break;
                case 'G':
                            symbol = 2;
                            break;
                case 'T':
                            symbol = 3;
                            break;
                case 'N':
                            symbol = 4;
                            break;
            }
            vertex = getLink(vertex, symbol);
            check(vertex, i + 1);
        }
    }
};

int main()
{
    Bohr object;
    object.AHO();
    return 0;
}

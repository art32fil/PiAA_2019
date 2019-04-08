#include <iostream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

const string sym = "ACGTN";

struct numbers
{
    long long int index;
    int pattern_num;
};

struct bohr_vrtx
{
    int next_vrtx[5];
    int pattern_num[40];
    int suff_link;
    int auto_move[5];
    int par;
    int suff_flink;
    bool flag;
    char symb;
};

class Bohr
{
private:
    vector <bohr_vrtx> bohr;
    string text;
    string pattern_str;
    vector <string> patterns;
    vector <int> patterns_pos;
    vector<numbers> num;

public:
    Bohr()
    {
        bohr.push_back(make_bohr_vrtx(-1,-1));
        char joker;
        cin >> text >> pattern_str >> joker;
        for(int i(0); i < pattern_str.size(); i++)
        {
            string pat;
            if(pattern_str[i] != joker)
            {
                patterns_pos.push_back(i + 1);
                for(int j(i); pattern_str[j] != joker && j != pattern_str.length(); j++)
                {
                    pat += pattern_str[j];
                    i++;
                }
                patterns.push_back(pat);
                add_string_to_bohr(pat);
            }
        }
    }

    bohr_vrtx make_bohr_vrtx(int p, char c)
    {
        bohr_vrtx v;
        memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
        memset(v.auto_move, 255, sizeof(v.auto_move));
        memset(v.pattern_num, 255, sizeof(v.pattern_num));
        v.flag = false;
        v.suff_link = -1;
        v.par = p;
        v.symb = c;
        v.suff_flink = -1;
        return v;
    }

    void add_string_to_bohr(string& s)
    {
        int num = 0;
        for(int i(0); i < s.size(); i++)
        {
            char ch = sym.find(s[i]);
            if(bohr[num].next_vrtx[ch] == -1)
            {
                bohr.push_back(make_bohr_vrtx(num,ch));
                bohr[num].next_vrtx[ch] = bohr.size() - 1;
            }
            num = bohr[num].next_vrtx[ch];
        }
        bohr[num].flag = true;
        for(int i(0); i < 40; i++)
        {
            if(bohr[num].pattern_num[i] == -1)
            {
                bohr[num].pattern_num[i] = patterns.size() - 1;
                break;
            }
        }
    }

    int get_suff_link(int v)
    {
        if(bohr[v].suff_link == -1)
            if(v == 0 || bohr[v].par == 0)
                bohr[v].suff_link = 0;
            else
                bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
        return bohr[v].suff_link;
    }

    int get_auto_move(int v, char ch)
    {
        if(bohr[v].auto_move[ch] == -1)
            if(bohr[v].next_vrtx[ch] != -1)
                bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
            else
                if(v == 0)
                    bohr[v].auto_move[ch] = 0;
                else
                    bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
        return bohr[v].auto_move[ch];
    }

    int get_suff_flink(int v)
    {
        if(bohr[v].suff_flink == -1)
        {
            int u = get_suff_link(v);
            if(u == 0)
                bohr[v].suff_flink = 0;
            else
                bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);
        }
        return bohr[v].suff_flink;
    }

    void check(int v, int i)
    {
        struct numbers s;
        for(int u(v); u != 0; u = get_suff_flink(u))
        {
            if(bohr[u].flag)
            {
                for(int j(0); j < 40; j++)
                {
                    if(bohr[u].pattern_num[j] != -1)
                    {
                        s.index = i - patterns[bohr[u].pattern_num[j]].size();
                        s.pattern_num = bohr[u].pattern_num[j];
                        num.push_back(s);
                    }
                    else
                        break;
                }
            }
        }
    }

    void find_all_pos()
    {
        int u = 0;
        for(int i(0); i < text.size(); i++)
        {
            u = get_auto_move(u, sym.find(text[i]));
            check(u, i + 1);
        }
    }

    void out()
    {
        vector <int> c(text.size(), 0);
        for(int i(0); i < num.size(); i++)
        {
            if(num[i].index < patterns_pos[num[i].pattern_num] - 1)
                continue;
            c[num[i].index - patterns_pos[num[i].pattern_num] + 1]++;
            if(c[num[i].index - patterns_pos[num[i].pattern_num] + 1] == patterns.size() &&
               num[i].index - patterns_pos[num[i].pattern_num] + 1 <= text.size() - pattern_str.size())
                cout << num[i].index - patterns_pos[num[i].pattern_num] + 2 << endl;
        }
    }
};

int main()
{
    Bohr obj;
    obj.find_all_pos();
    obj.out();
    return 0;
}
#include <iostream>
#include <map>
#include <vector>
#include <cstring>

using namespace std;


struct Vertex
{
    int next_vrtx[5];
    int auto_move[5]; //
    int par; // parrent of this vertex
    char symb; // transfer symbol from parrent
    int pat_num[40]; // number of pattern designated by this vertex
    bool flag;
    int suff_link;
    int suff_flink; // good suffix link which has flag = true
};


struct EntryPattern
{
    EntryPattern(int index, int pat_num) : index(index), pat_num(pat_num) {}

    int index;
    int pat_num;
};

vector<Vertex> bohr;
vector<string> pattern;

map<char, char> alpha_idx{
    {'A', 0},
    {'C', 1},
    {'G', 2},
    {'N', 3},
    {'T', 4},
};


//p - parrent, c - symbol of transfer
Vertex make_bohr_vrtx(int p, char c)
{
   Vertex v;

   memset(v.next_vrtx, 255, sizeof(v.next_vrtx)); // filling all bytes of next_vrtx by -1
   memset(v.auto_move, 255, sizeof(v.auto_move));
   memset(v.pat_num, 255, sizeof(v.pat_num));
   v.flag=false;
   v.suff_link=-1; //изначально - суф. ссылки нет
   v.par=p;
   v.symb=c;
   v.suff_flink=-1;

   return v;
}


void bohr_ini()
{
   //добавляем единственную вершину - корень
   bohr.push_back(make_bohr_vrtx(-1, -1));
}


void add_string_to_bohr(const string& s)
{
   int num=0; //начинаем с корня

   for(int i = 0; i < s.length(); i++)
   {
      char ch = alpha_idx[s[i]]; //получаем номер в алфавите

      if(bohr[num].next_vrtx[ch]==-1)
      {
         bohr.push_back(make_bohr_vrtx(num, ch));
         bohr[num].next_vrtx[ch]=bohr.size()-1;
      }

      num=bohr[num].next_vrtx[ch];
   }

   bohr[num].flag=true;
   pattern.push_back(s);

   // if pattern has same subpatterns
   for(int i = 0; i < 40; ++i)
       if(bohr[num].pat_num[i] == -1)
       {
           bohr[num].pat_num[i] = pattern.size() - 1;
           break;
       }
}


int get_auto_move(int v, char ch);

int get_suff_link(int v)
{
   if (bohr[v].suff_link==-1) //если еще не считали
      if (v==0||bohr[v].par==0) //если v - корень или предок v - корень
         bohr[v].suff_link=0;
      else
         bohr[v].suff_link=get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);

   return bohr[v].suff_link;
}


int get_auto_move(int v, char ch)
{
   if (bohr[v].auto_move[ch]==-1)
   {
      if (bohr[v].next_vrtx[ch]!=-1)
         bohr[v].auto_move[ch]=bohr[v].next_vrtx[ch];
      else
      {
         if (v==0)
            bohr[v].auto_move[ch]=0;
         else
            bohr[v].auto_move[ch]=get_auto_move(get_suff_link(v), ch);
      }
   }

   return bohr[v].auto_move[ch];
}


int get_suff_flink(int v)
{
   if (bohr[v].suff_flink==-1)
   {
      int u=get_suff_link(v);
      if (u==0) //либо v - корень, либо суф. ссылка v указывает на корень
         bohr[v].suff_flink=0;
      else
         bohr[v].suff_flink=(bohr[u].flag) ? u : get_suff_flink(u);
   }

   return bohr[v].suff_flink;
}


//implemenation of searching by automation
void check(int v, int i, vector<EntryPattern> &ep)
{
    for(int u=v; u!=0; u=get_suff_flink(u))
        if (bohr[u].flag)
            for(int j = 0; j < 40; ++j)
            {
                if(bohr[u].pat_num[j]!= -1)
                    ep.push_back(EntryPattern(i - pattern[bohr[u].pat_num[j]].length(), bohr[u].pat_num[j]));
                else
                    break;
            }
}


void aho_corasik(const string& s, vector<EntryPattern> &ep){
    int u=0;

    for(int i=0 ; i < s.length(); i++)
    {
        u=get_auto_move(u, alpha_idx[s[i]]);
        check(u, i+1, ep);
    }
}


int main()
{
    bohr_ini();

    string text, pattern_str;
    char joker;

    cin >> text >> pattern_str >> joker;

    std::vector<int> matches(text.length(), 0);
    std::vector<std::string> patterns;
    std::vector<int> patterns_pos;



    for (int i = 0; i < pattern_str.length(); i++)
    {
        std::string pat;

        if (pattern_str[i] != joker)
        {
            patterns_pos.push_back(i + 1);

            for (int j = i; pattern_str[j] != joker && j != pattern_str.length(); j++)
            {
                pat += pattern_str[j];
                    i++;
            }

            patterns.push_back(pat);
        }
    }

    for(string &el : patterns)
        add_string_to_bohr(el);

    vector<EntryPattern> ep;
    aho_corasik(text, ep);

    for(int i = 0; i < ep.size(); ++i)
    {
        if(ep[i].index < patterns_pos[ep[i].pat_num] - 1)
            continue;

        //increment i + j - 1 position in vector of mathes
        matches[ep[i].index - patterns_pos[ep[i].pat_num] + 1]++;

        /*
         * if in position i + j - 1 has count of matches = count of subpatterns of pattern_str
         * second condition check that pattern does not go beyond the text
        */
        if(matches[ep[i].index - patterns_pos[ep[i].pat_num] + 1] == patterns.size() &&
                ep[i].index - patterns_pos[ep[i].pat_num] + 1 <= text.length() - pattern_str.length())
            cout << ep[i].index - patterns_pos[ep[i].pat_num] + 2 << endl;
    }

    return 0;
}

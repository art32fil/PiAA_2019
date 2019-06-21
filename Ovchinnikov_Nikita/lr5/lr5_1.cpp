#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

using namespace std;

const int k=5;
const string first_alphabet = "ACGTN";

struct bohr_vrtx
{
    int next_vrtx[k];           //next_vrtx[i] — номер вершины, в которую мы придем по символу с номером i в алфавите
    int pat_num;                //номер строки-образца, обозначаемого этой вершиной
    bool flag;                  //бит, указывающий на то, является ли наша вершина исходной строкой
    int suff_link;              //суффиксная ссылка
    int auto_move[k];           //запоминание перехода
    int par;                    //вершина-отец в дереве
    unsigned char symb;         //символ на ребре от par к этой вершине
    int suff_flink;             //"хорошая" ссылка
};

vector<bohr_vrtx> bohr;
vector<string> pattern;

bohr_vrtx make_bohr_vrtx(int p, unsigned char c)
{
   bohr_vrtx v;
   memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
   memset(v.auto_move, 255, sizeof(v.auto_move));
   v.flag=false;
   v.suff_link=-1;
   v.par=p;
   v.symb=c;
   v.suff_flink=-1;
   return v;
}

void bohr_init()
{
   bohr.push_back(make_bohr_vrtx(0,'\0'));
}

unsigned char get_number_from_alhabet(unsigned char symbol)
{
    for(size_t i = 0; i < first_alphabet.length(); i++)
    {
        if(symbol == first_alphabet[i])
        {
            return static_cast<unsigned char>(i);
        }
    }
    return 0;
}

void add_string_to_bohr(const string& s)
{
   int num=0;
   for (size_t i=0; i<s.length(); i++){
       unsigned char ch = get_number_from_alhabet(s[i]);
      if (bohr[num].next_vrtx[ch]==-1)
      {
         bohr.push_back(make_bohr_vrtx(num,ch));
         bohr[num].next_vrtx[ch]=bohr.size()-1;
      }
      num=bohr[num].next_vrtx[ch];
   }
   bohr[num].flag=true;
   pattern.push_back(s);
   bohr[num].pat_num=pattern.size()-1;
}

bool is_string_in_bohr(const string& s)
{
   int num=0;
   for (size_t i=0; i<s.length(); i++){
       unsigned char ch = get_number_from_alhabet(s[i]);
      if (bohr[num].next_vrtx[ch]==-1){
         return false;
         }
      num=bohr[num].next_vrtx[ch];
   }
   return true;
}

int get_auto_move(int v, unsigned char ch);

int get_suff_link(int v)
{
   if(bohr[v].suff_link==-1)
   {
      if (v==0||bohr[v].par==0)
         bohr[v].suff_link=0;
      else
         bohr[v].suff_link=get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
   }
   return bohr[v].suff_link;
}

int get_auto_move(int v, unsigned char ch)
{
   if (bohr[v].auto_move[ch]==-1)
   {
      if (bohr[v].next_vrtx[ch]!=-1)
      {
         bohr[v].auto_move[ch]=bohr[v].next_vrtx[ch];
      }
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
      int u = get_suff_link(v);
      if(u == 0)
         bohr[v].suff_flink=0;
      else
         bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);
   }
   return bohr[v].suff_flink;
}

void check(int v,int i)
{
    for(int u=v; u!=0; u=get_suff_flink(u))
    {
        if(bohr[u].flag)
            cout << i-pattern[bohr[u].pat_num].length() + 1 << " " << bohr[u].pat_num + 1 << endl;
    }
}

void find_all_pos(const string& s)
{
    int u=0;
    for(size_t i=0;i<s.length();i++)
    {
        u = get_auto_move(u, get_number_from_alhabet(s[i]));
        check(u,i+1);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    size_t n;
    string text, pat;
    cin >> text >> n;

    bohr_init();
    for(size_t i = 0; i < n; i++)
    {
        cin >> pat;
        add_string_to_bohr(pat);
        pat.clear();
    }
    find_all_pos(text);

    return a.exec();
}

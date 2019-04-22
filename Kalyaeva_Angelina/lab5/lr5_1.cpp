#include <iostream>
#include <vector>
#include <string>

#define ALP 6

using namespace std;

struct bohr_vertex {
    int next_vertex[ALP];
    int path_num;
    bool flag;
    int suff_link;
    int auto_move[ALP];
    int par;
    char symbol;
    int suff_flink;
};

vector <bohr_vertex> bohr;
vector <string> pattern;

bohr_vertex make_bohr_vertex(int par, char symbol) {
    bohr_vertex vertex;
    memset(vertex.next_vertex, 255, sizeof(vertex.next_vertex));
    vertex.flag = false;
    vertex.suff_link = -1;
    memset(vertex.auto_move, 255, sizeof(vertex.auto_move));
    vertex.par = par;
    vertex.symbol = symbol;
    vertex.suff_flink = -1;
    return vertex;
}

void init_bohr() {
    bohr.push_back(make_bohr_vertex(-1, -1));
}

int find(char symbol) {
    int ch;
    switch (symbol)
    {
    case 'A':
        ch = 0;
        break;
    case 'C':
        ch = 1;
        break;
    case'G':
        ch = 2;
        break;
    case 'T':
        ch = 3;
        break;
    case 'N':
        ch = 4;
        break;
    default:
        break;
    }
    return ch;
}

void add_string_to_bohr(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char ch = find(s[i]);
        if (bohr[num].next_vertex[ch] == -1) {
            bohr.push_back(make_bohr_vertex(num, ch));
            bohr[num].next_vertex[ch] = bohr.size() - 1;
        }
        num = bohr[num].next_vertex[ch];
    }
    bohr[num].flag = true;
    pattern.push_back(s);
    bohr[num].path_num = pattern.size() - 1;
}

bool is_strig_in_bohr(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char ch = find(s[i]);
        if (bohr[num].next_vertex[ch] == -1) {
            return false;
        }
        num = bohr[num].next_vertex[ch];
    }
    return true;
}

int get_auto_move(int v, char ch);

int get_suff_link(int v) {
    if (bohr[v].suff_link == -1) {
        if (v == 0 || bohr[v].par == 0) {
            bohr[v].suff_link = 0;
        }
        else {
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symbol);  //пройдем по суф.ссылке предка и запустим переход по символу.
        }
    }
    return bohr[v].suff_link;
}

int get_auto_move(int v, char ch) {             //вычисляемая функция переходов
    if (bohr[v].auto_move[ch] == -1) {
        if (bohr[v].next_vertex[ch] != -1) {            //если из текущей вершины еть ребро с символом ch
            bohr[v].auto_move[ch] = bohr[v].next_vertex[ch];    //то идем по нему
        }
        else {
            if (v == 0) {
                bohr[v].auto_move[ch] = 0;
            }
            else {
                bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);  //иначе перейдем по суффиксальной ссылке
            }
        }
    }
    return bohr[v].auto_move[ch];
}

int get_suff_flink(int v) {
    if (bohr[v].suff_flink == -1) {
        int u = get_suff_link(v);
        if (u == 0) {
            bohr[v].suff_flink = 0;
        }
        else {
            bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);  //если для вершины по суф.ссылке flag=true, то это искомая вершина, иначе рекурсия.
        }
    }
    return bohr[v].suff_flink;
}

void check(int v, int i) {  //хождение по хорошим суффиксальнм ссылкам из текущей позиции, учитывая, что эта позиция оканчивается на симво i
    for (int u = v; u != 0; u = get_suff_flink(u)) {
        if (bohr[u].flag) {
            cout << i - pattern[bohr[u].path_num].length() + 1 << " " << bohr[u].path_num +1<< endl;
        }
    }
}

void find_all_pos(string s) {
    int u = 0;
    for (int i = 0; i < s.length(); i++) {
        u = get_auto_move(u, find(s[i]));
        check(u, i + 1);
    }
}


int main() {
    string text;
    int n;
    init_bohr();
    cin >> text;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        add_string_to_bohr(temp);
    }
    find_all_pos(text);
    system("pause");
    return 0;
}
#include <iostream>
#include <vector>
#include <cstring>
#include <map>


using Vertex = struct {
    int next_vertex[5];
    int pattern_num[40];
    bool original;
    int suff_link;
    int suff_flink;
    int auto_move[5], par;
    char symb;
};
using Trie = std::vector<Vertex>;

using patternEntry = struct {
    unsigned long long int index;
    int pattern_num;
};

std::map<char, char> Char{
        {'A', 0},
        {'C', 1},
        {'G', 2},
        {'T', 3},
        {'N', 4},
};

Trie trie;
std::vector<std::string> pattern;

Vertex make_vertex(int p, char c) {
    Vertex v;
    memset(v.next_vertex, 255, sizeof(v.next_vertex));
    memset(v.auto_move, 255, sizeof(v.auto_move));
    memset(v.pattern_num, 255, sizeof(v.pattern_num));
    v.original = false;
    v.suff_link = -1;
    v.suff_flink = -1;
    v.par = p;
    v.symb = c;
    return v;
}

void trie_init() {
    trie.push_back(make_vertex(-1, -1));
}

void add_string_to_trie(std::string const &s) {
    int num = 0;
    for (char i : s) {
        char ch = Char[i];
        if (trie[num].next_vertex[ch] == -1) {
            trie.push_back(make_vertex(num, ch));
            trie[num].next_vertex[ch] = trie.size() - 1;
        }
        num = trie[num].next_vertex[ch];
    }
    trie[num].original = true;
    pattern.push_back(s);
    for(int i = 0; i < 40; i++) {
        if(trie[num].pattern_num[i] == -1) {
            trie[num].pattern_num[i] = pattern.size() - 1;
            break;
        }
    }
}

int get_auto_move(int v, char ch);

int get_suff_link(int v) {
    if (trie[v].suff_link == -1)
        if (v == 0 || trie[v].par == 0)
            trie[v].suff_link = 0;
        else
            trie[v].suff_link = get_auto_move(get_suff_link(trie[v].par), trie[v].symb);
    return trie[v].suff_link;
}

int get_auto_move(int v, char ch) {
    if (trie[v].auto_move[ch] == -1)
        if (trie[v].next_vertex[ch] != -1)
            trie[v].auto_move[ch] = trie[v].next_vertex[ch];
        else if (v == 0)
            trie[v].auto_move[ch] = 0;
        else
            trie[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
    return trie[v].auto_move[ch];
}


int get_suff_flink(int v) {
    if (trie[v].suff_flink == -1) {
        int u = get_suff_link(v);
        if (u == 0)
            trie[v].suff_flink = 0;
        else
            trie[v].suff_flink = (trie[u].original) ? u : get_suff_flink(u);
    }
    return trie[v].suff_flink;
}


void check(int v, int i, std::vector<patternEntry> &p) {
    patternEntry s;
    for (int u = v; u != 0; u = get_suff_flink(u)) {
        if (trie[u].original) {
            for(int j = 0; j < 40; j++) {
                if(trie[u].pattern_num[j] != -1) {
                    s.index = i - pattern[trie[u].pattern_num[j]].length();
                    s.pattern_num = trie[u].pattern_num[j];
                    p.push_back(s);
                } else
                    break;
            }
        }
    }
}


void aho_corasick(const std::string &s, std::vector<patternEntry> &p) {
    int u = 0;
    for (int i = 0; i < s.length(); i++) {
        u = get_auto_move(u, Char[s[i]]);
        check(u, i + 1, p);
    }
}

int main() {
    std::string text, pattern_str;
    char joker;

    std::cin >> text >> pattern_str >> joker;

    trie_init();

    std::vector<int> c(text.length(), 0);
    std::vector<std::string> patterns;
    std::vector<int> patterns_pos;

    for (int i = 0; i < pattern_str.length(); i++) {
        std::string pat;
        if (pattern_str[i] != joker) {
            patterns_pos.push_back(i + 1);
            for (int j = i; pattern_str[j] != joker && j != pattern_str.length(); j++) {
                pat += pattern_str[j];
                i++;
            }
            patterns.push_back(pat);
        }
    }

    for (auto const &el : patterns) {
        add_string_to_trie(el);
    }

    std::vector<patternEntry> p;
    aho_corasick(text, p);

    for (int i = 0; i < p.size(); i++) {
        if(p[i].index < patterns_pos[p[i].pattern_num] - 1) continue;
        c[p[i].index - patterns_pos[p[i].pattern_num] + 1]++;
        if (c[p[i].index - patterns_pos[p[i].pattern_num] + 1] == patterns.size() &&
            p[i].index - patterns_pos[p[i].pattern_num] + 1 <= text.length() - pattern_str.length())
            std::cout << p[i].index - patterns_pos[p[i].pattern_num] + 2 << std::endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

map<char, char> Alphabet
{
    {'A', 0},
    {'C', 1},
    {'G', 2},
    {'N', 3},
    {'T', 4}
};

struct Bohr_Vertex
{
    int next_vertex[5];
    int machine_transition[5];
    int parent;
    int pattern_number;
    int suffix_link;
    int suffix_good_link;
    bool is_already_pattern;
    char symbol;
};
struct Pattern_Entry
{
    unsigned long long int index;
    unsigned int pattern_number;
};
typedef Bohr_Vertex bohr_vertex;
typedef vector<bohr_vertex> Bohr;
typedef vector<Pattern_Entry> pattern_entry_table;

Bohr bohr;

bohr_vertex create_BohrVertex(int parent, char symbol)
{
    bohr_vertex vertex;
    memset(vertex.next_vertex, 255, sizeof(vertex.next_vertex));
    memset(vertex.machine_transition, 255, sizeof(vertex.machine_transition));
    vertex.is_already_pattern = false;
    vertex.suffix_link = -1;
    vertex.suffix_good_link = -1;
    vertex.parent = parent;
    vertex.symbol = symbol;
    return vertex;
}

void initialize_Bohr()
{
    bohr.push_back(create_BohrVertex(-1, -1));
}

void add_StringToBohr(const string &str, vector<string> &patterns)
{
    int number = 0;
    for (char symbol : str)
    {
        char alphabet_index = Alphabet[symbol];
        if (bohr[number].next_vertex[alphabet_index] == -1)
        {
            bohr.push_back(create_BohrVertex(number, alphabet_index));
            bohr[number].next_vertex[alphabet_index] = bohr.size() - 1;
        }
        number = bohr[number].next_vertex[alphabet_index];
    }
    bohr[number].is_already_pattern = true;
    patterns.push_back(str);
    bohr[number].pattern_number = patterns.size() - 1;
}

int get_MachineTransition(int vertex_index, char alphabet_index);

int get_SuffixLink(int vertex_index)
{
    if (bohr[vertex_index].suffix_link == -1)
    {
        if (vertex_index == 0 || bohr[vertex_index].parent == 0)
            bohr[vertex_index].suffix_link = 0;
        else
            bohr[vertex_index].suffix_link = get_MachineTransition(get_SuffixLink(bohr[vertex_index].parent),
                                                                   bohr[vertex_index].symbol);
    }
    return bohr[vertex_index].suffix_link;
}

int get_MachineTransition(int vertex_index, char alphabet_index)
{
    if (bohr[vertex_index].machine_transition[alphabet_index] == -1)
    {
        if (bohr[vertex_index].next_vertex[alphabet_index] != -1)
            bohr[vertex_index].machine_transition[alphabet_index] = bohr[vertex_index].next_vertex[alphabet_index];
        else
        {
            if (vertex_index == 0)
                bohr[vertex_index].machine_transition[alphabet_index] = 0;
            else
                bohr[vertex_index].machine_transition[alphabet_index] = get_MachineTransition(get_SuffixLink(vertex_index),
                                                                                              alphabet_index);
        }
    }
    return bohr[vertex_index].machine_transition[alphabet_index];
}

int get_SuffixGoodLink(int vertex_index){
    if (bohr[vertex_index].suffix_good_link == -1)
    {
        int next_vertex = get_SuffixLink(vertex_index);
        if (next_vertex == 0)
            bohr[vertex_index].suffix_good_link = 0;
        else
            bohr[vertex_index].suffix_good_link = (bohr[next_vertex].is_already_pattern) ?
                        next_vertex : get_SuffixGoodLink(next_vertex);
    }
    return bohr[vertex_index].suffix_good_link;
}

void check_IsPattern(vector<string> &patterns, pattern_entry_table &result_table,
                     int vertex_index, int symbol_index)
{
    Pattern_Entry pattern_table_element;
    for (int current_index = vertex_index; current_index != 0; current_index = get_SuffixGoodLink(current_index))
        if (bohr[current_index].is_already_pattern)
        {
            pattern_table_element.index = symbol_index - patterns[bohr[current_index].pattern_number].length() + 1;
            pattern_table_element.pattern_number = bohr[current_index].pattern_number + 1;
            result_table.push_back(pattern_table_element);
        }
}

void findAllSubstrs_AchoCorasick(const string &text, vector<string> &patterns,
                                 pattern_entry_table &result_table)
{
    int now_vertex = 0;
    for (int i = 0; i < text.length(); i++)
    {
        now_vertex = get_MachineTransition(now_vertex, Alphabet[text[i]]);
        check_IsPattern(patterns, result_table, now_vertex, i + 1);
    }
}

int main()
{
    pattern_entry_table result_table;
    vector<string> patterns;
    string text, now_pattern;
    int patterns_count;

    cin >> text >> patterns_count;
    initialize_Bohr();
    for (int i = 0; i < patterns_count; i++)
    {
        cin >> now_pattern;
        add_StringToBohr(now_pattern, patterns);
    }
    findAllSubstrs_AchoCorasick(text, patterns, result_table);
    for (int i = 0; i < result_table.size(); i++)
        cout << result_table[i].index << " " << result_table[i].pattern_number << endl;
    return 0;
}

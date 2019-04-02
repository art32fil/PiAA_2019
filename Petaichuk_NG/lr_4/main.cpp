#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefix_func(string &str)
{
    int str_length = str.size();
    vector<int> pi(str_length);

    pi[0] = 0;
    for (int index = 1; index < str_length; index++)
    {
        int PF_value = pi[index - 1];
        while ((PF_value > 0) && (str[index] != str[PF_value]))
            PF_value = pi[PF_value - 1];
        if (str[index] == str[PF_value])
            PF_value++;
        pi[index] = PF_value;
    }
    return pi;
}

vector<int> findSubstr_KMP(string &text, string &pattern)
{
    size_t pattern_length = pattern.size();
    vector<int> answer;
    vector<int> PF_values = prefix_func(pattern);
    int last_PF_value = 0;

    for (int index = 0; index < text.size(); index++)
    {
        while ((last_PF_value > 0) && (text[index] != pattern[last_PF_value]))
            last_PF_value = PF_values[last_PF_value - 1];
        if (text[index] == pattern[last_PF_value])
            last_PF_value++;
        if (last_PF_value == pattern_length)
            answer.push_back(index - pattern_length + 1);
    }
    return answer;
}

int check_isShiftedString(string &shifted, string &original)
{
    string concatinated = shifted + "@" + original;
    vector<int> PF_values = prefix_func(concatinated);
    int index = PF_values[PF_values.size() - 1];

    for (int i = index; i < shifted.size(); i++)
        if (shifted[i] != original[i - index])
            return -1;
    return index;
}

int main()
{
    /*string text, pattern;

    cin >> pattern >> text;

    vector<int> substr_indexes = findSubstr_KMP(text, pattern);
    if (substr_indexes.empty())
        cout << "-1";
    else
    {
        for (int i = 0; i < substr_indexes.size() - 1; i++)
            cout << substr_indexes[i] << ",";
        cout << substr_indexes[substr_indexes.size() - 1];
    }*/
    string shifted, original;

    cin >> shifted >> original;

    if (original.size() != shifted.size())
        cout << "-1";
    else if (original == shifted)
        cout << "0";
    else
    {
        int index = check_isShiftedString(shifted, original);
        cout << index;
    }
    return 0;
}

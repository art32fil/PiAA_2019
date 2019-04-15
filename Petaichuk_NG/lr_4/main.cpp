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
    string double_shifted = shifted + shifted;
    vector<int> original_indexes = findSubstr_KMP(double_shifted, original);
    return (original_indexes.empty()) ? -1 : original_indexes[0];
}

int main()
{
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

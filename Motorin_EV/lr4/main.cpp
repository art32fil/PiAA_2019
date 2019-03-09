#include <iostream>
#include <vector>
using namespace std;

vector<int> prefixFunction(string str) {
    vector<int> entries(str.length());
    
    for (int i = 1; i < str.length(); i++) {
        int j = entries[i - 1];
        
        while ((j > 0) && (str[i] != str[j]))
            j = entries[j - 1];
        
        if (str[i] == str[j])
            ++j;
        
        entries[i] = j;
    }
    
    return entries;
}

vector<int> KMPA(string str, string substr) {
    vector<int> result;
    vector<int> p = prefixFunction(substr + "+" + str);
    
    for (unsigned i = 0; i < p.size(); i++)
        if (p[i] == substr.length())
            result.push_back(i - 2 * int(substr.length()));
    
    return result.size() > 0 ? result : vector<int>(1, -1);
}

int cycleShiftIndex(string s1, string s2) {
    if (s1.length() != s2.length()) return -1;
    if (s1 == s2) return 0;
    vector<int> p = prefixFunction(s1 + "+" + s2);
    int shift = p[p.size() - 1];
    
    for (int i = shift; i < s1.length(); i++)
        if (s1[i] != s2[i - shift]) return -1;
    return shift;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    //cout << cycleShiftIndex(s1, s2);
    
    vector<int> res = KMPA(s2, s1);
    
    for (int i = 0; i < res.size(); i++) {
        cout << res[i];
        if (i != res.size() - 1) cout << ",";
    }
    
    return 0;
}

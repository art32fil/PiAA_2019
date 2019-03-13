#include <iostream>
#include <string>
#include <vector>

using namespace std;

 
vector<int> prefix_func(string str) {
    vector<int> entries(str.length());
    entries[0] = 0;
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
vector<int> KMP(string str, string substr) {
    vector<int> p;
    vector<int> result;
    p = prefix_func(substr);
    unsigned long k = 0, j = 0;
    while (k < str.length()){
        if (str[k] == substr[j]){
            k++;
            j++;
            if (j == substr.size()){
                result.push_back(k-substr.size());
            }
        }
        else if (j == 0){
            k++;
        }
             else{
                 j = p[j-1];
             }
        
    }
    return result;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    vector<int> res = KMP(s2, s1);
    if (res.size() > 0){
        for (int i = 0; i < res.size(); i++) {
            cout << res[i];
            if (i != res.size() - 1) cout << ","; 
        }
    }
    else cout << "-1";
    return 0;
}

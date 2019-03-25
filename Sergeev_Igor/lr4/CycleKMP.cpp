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
int KMP(string str, string substr) {
    vector<int> p;
    vector<int> result;
    p = prefix_func(substr);
    unsigned long k = 0, j = 0;
    while (true){
        if (str[k] == substr[j]){
            k++;
            j++;
            if (k == str.size())
                k = 0;
            if (j == substr.size()){
                return substr.size() - k;
            }
        }
        else if (j == 0){
            k++;
            if (k == str.size())
                return -1;
        }
             else{
                 j = p[j-1];
             }
        
    }
    return -1;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    if (s1.size() != s2.size()){
        cout << "-1";
    }
    else if (s1 == s2)
        cout << "0";
         else cout << KMP(s2,s1);
    return 0;
}
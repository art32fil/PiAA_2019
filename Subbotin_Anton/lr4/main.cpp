#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

vector<uint_least32_t> Prefix(string combo){
    uint_least32_t size = combo.length();
    vector<uint_least32_t> result(size);
    for(uint_least32_t i = 1; i < size; i++){
        uint_least32_t j = result[i - 1];
        while(j > 0 && combo[i] != combo[j])
            j = result[j - 1];
        if(combo[i] == combo[j])
            j++;
        result[i] = j;
    }
    return result;
}

void KMP(string substr, string str){
    vector<uint_least32_t> prefix = Prefix(substr + "$" + str);
    uint_least32_t subsize = (uint_least32_t)substr.length();
    uint_least32_t size = (uint_least32_t)str.length() + subsize + 1;
    bool flag = false;
    for(uint_least32_t i = subsize + 1; i < size; i++){
        if(prefix[i] == subsize){
            if(flag)
                cout << ',';
            cout << i - 2 * subsize;
            flag = true;
        }
    }
    if(!flag)
        cout << -1;
}

void Cycle(string substr, string str){
    uint_least32_t index = Prefix(substr + "$" + str).back();
    if(index == (uint_least32_t)substr.length())
        cout << 0;
    else
        if(index + Prefix(str + "$" + substr).back() == (uint_least32_t)substr.length())
            cout << index;
        else
            cout << -1;
}

int main()
{
    string substr, str;
    getline(cin, substr);
    getline(cin, str);
    //KMP(substr, str);
    Cycle(substr, str);
    return 0;
}

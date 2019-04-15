#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

vector<int> KMP(string str, string substr, int* pref_mas){
    vector<int> answer;
    int l=0;
    for(int k=0;k<str.size();){
        if(str[k]==substr[l]){
            k++;
            l++;
            if(l==substr.size()){
                answer.push_back(k-l);
            }
        }else{
            if(l==0){
                k++;
                if(k==str.size()) answer.push_back(-1);
            }
            else l = pref_mas[l-1];
        }
    }
    return answer;
}

int *prefix_fun(string substring){
int * pref_mas = new int[substring.size()];
int j=0;
pref_mas[0] = 0;
    for(int i=1;i<substring.size();){
        if(substring[i]!=substring[j]){
            if(j==0) {pref_mas[i]=0; i++;}
            else j = pref_mas[j-1];
        }else{pref_mas[i] = j+1;i++;j++; }
    }
    return pref_mas;
}

int isCircle(string str, string substr){
    string concatSTR = str + '|' + substr;
    int* pref_mas = prefix_fun(concatSTR);
    int index = pref_mas[concatSTR.size() - 1];
        for (int i = index; i < str.size(); i++)
            if (str[i] != substr[i - index]) return -1;
        return index;
}

int main(){
    string substring, str;
    getline(cin,substring);
    getline(cin,str);
    if(str.size() != substring.size()) {
                std::cout << -1;
                return 0;
            }

            if(str == substring){
                std::cout << 0;
                return 0;
            }
    cout<<isCircle(str, substring)<<endl;
    return 0;
}

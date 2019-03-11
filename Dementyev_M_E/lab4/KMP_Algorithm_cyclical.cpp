//
//  main.cpp
//  KMP_Algorithm
//
//  Created by Михаил Дементьев on 09/03/2019.
//  Copyright © 2019 Михаил Дементьев. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<int> prefix(string input);

int KMP(string pattern, string text, vector<int> P_mass);

int main() {
    string pattern, text;
    getline(cin, pattern);
    getline(cin, text);
    
    vector<int> P_mass = prefix(pattern);
    int indexOfAnswer = KMP(pattern, text, P_mass);
    
    if(pattern.size() != text.size()){
        cout << -1;
    } else if (pattern == text) {
        cout << 0;
    } else {
        cout << indexOfAnswer;
    }
    
    return 0;
}

vector<int> prefix(string pattern) {
    
    vector<int> P_mass;
    P_mass.push_back(0);
    for(int i = 1; i < pattern.size(); i++) P_mass.push_back(-1);
    
    int i = 1, j = 0;
    while(P_mass[pattern.size()-1] == -1){
        if(pattern[i] == pattern[j]){
            P_mass[i] = j + 1; i++; j++;
        } else if (j == 0) {
            P_mass[i] = 0; i++;
        } else {
            j = P_mass[j-1];
        }
    }
    
    return P_mass;
}

int KMP(string pattern, string text, vector<int> P_mass){
    unsigned long l = 0, k = 0;
    while(1){
        if (text[k] == pattern[l]){
            k++; l++;
            if(k == text.size()){
                k = 0;
            }
            if(l == pattern.size()){
                return (pattern.size() - k);
            }
        } else if (l == 0){
            k++;
            if(k == text.size()){
                return -1;
            }
        } else{
            l = P_mass[l-1];
        }
        
    }
}

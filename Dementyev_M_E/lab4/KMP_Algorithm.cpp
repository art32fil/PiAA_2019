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

vector<int> KMP(string pattern, string text, vector<int> P_mass);

int main() {
    string pattern, text;
    getline(cin, pattern);
    getline(cin, text);
    
    vector<int> P_mass = prefix(pattern);
    vector<int> indexOfAnswers = KMP(pattern, text, P_mass);
    
    
    if(indexOfAnswers.size() > 0){
        for (int i = 0; i < indexOfAnswers.size(); i++) {
            cout << indexOfAnswers[i];
            if(i < indexOfAnswers.size()-1){
                cout << ",";
            }
        }
    } else cout << -1;
    cout << endl;
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

vector<int> KMP(string pattern, string text, vector<int> P_mass){
    vector<int> indexOfAnswers;
    unsigned long l = 0, k = 0;
    while(k < text.size()){
        if (text[k] == pattern[l]){
            k++; l++;
            if(l == pattern.size()){
                indexOfAnswers.push_back(k-pattern.size());
            }
        } else if (l == 0){
            k++;
        } else{
            l = P_mass[l-1];
        }
        
    }
    return indexOfAnswers;
}

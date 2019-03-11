#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <algorithm>


using namespace std;

vector <int> prefix_function(string form){
    int n=form.size();
    vector<int> p(n);
    for(int i=1,j=0;i<n;i++){
        while(j>0&form[i]!=form[j])
            j=p[j-1];
        if(form[i]==form[j]) j++;
        p[i]=j;
    }
    return p;
}

int isCircle(string A,string B){
    int index=prefix_function(A+"|"+B).back();//на сколько префикс B равен суффиксу А
    if(index==A.size()) return 0;
    return index+prefix_function(B+"|"+A).back()==A.size() ? index:-1;
}

void algoritmKmp(string text,string substring){
    vector<int> P=prefix_function(substring+"|"+text);
    int n=substring.size();
    int m=text.size();
    bool flag=false;
    for(int i=n+1;i<n+m+1;i++)
        if(P[i]==n) {
            if(flag)
                cout<<",";
            cout<<(i - (n + 1) - (n - 1));
            flag=true;
        }
    if(!flag)
        cout<<-1<<endl;
}

int main() {
    string substring;
    string line;
    getline(cin,substring);
    getline(cin,line);
    cout<<isCircle(substring,line);
    return 0;
}


#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefixF(string str)
{
    size_t n = str.size();
    vector<int> result(n);
    for(int i = 1, j = 0; i < n; i++)
    {
        while((j > 0) && (str[i] != str[j]))
            j = result[j-1];
        if(str[i] == str[j])
            j++;
        result[i] = j;
     }
     return result;
}

void searchKMP(string substr, string str)
{
    vector<int> P = prefixF(substr + "@" + str);
    size_t n = substr.size();
    bool flag = false;
    for(size_t i = n + 1; i < n + str.size() + 1; i++)
    {
        if(P[i] == n)
        {
            if(flag)
                cout << ",";
            cout << (i - (n + 1) - (n - 1));
            flag = true;
        }
    }
    if(!flag)
        cout<< -1 <<endl;
}

void Cycle(string A, string B)
{
    int index = prefixF(A + "@" + B).back();
    if(index == A.size())
        cout << 0 << endl;
    else
        if(index + prefixF(B + "@" + A).back() == A.size())
            cout << index << endl;
        else
            cout << -1 << endl;
}

int main()
{
    string substr;
    string str;
    getline(cin, substr);
    getline(cin, str);
    //searchKMP(substr, str);
    Cycle(substr, str);
    return 0;
}

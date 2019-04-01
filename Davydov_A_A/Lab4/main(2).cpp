#include <iostream>
#include <vector>

using namespace std;

vector<int> prefix_function (string s)
{
    int n =  s.length();
    vector<int> pi(n);

    for (int i = 1; i < n; ++i)
    {
        int j = pi[i-1];
        while ((j > 0) && (s[i] != s[j]))
            j = pi[j-1];

        if (s[i] == s[j])
            ++j;

        pi[i] = j;
     }

     return pi;
}


// checking B is cyclic shift A
int CyclicShift(string A, string B)
{
    int idx = prefix_function(A + "|" + B).back(); //shows how prefix of A close to suffix B
    if(idx == A.size())
        return 0;
    else if(idx + prefix_function(B + "|" + A).back() == A.size())
        return idx;
    else
        return -1;
}


string KMP(string const &S, string const &pattern)
{
    string concat = pattern + "|" + S;
    vector<int> pi = prefix_function(concat);
    int n = pattern.size();
    string result = "";

    for(int i = n + 1; i < n + S.size() + 1; ++i)
        if(pi[i] == n)
        {
            if(result.size() == 0)
                 result += std::to_string(i - (n + 1) - (n - 1)); //(n + 1) is shift in concat str
            else
                 result += "," + std::to_string(i - (n + 1) - (n - 1));
        }

    if(result.size() == 0)
        result += "-1";

    return result;
}


int main()
{
    string S;
    string pattern;
    getline(cin, pattern);
    getline(cin, S);

    //cout << KMP(S, pattern);
    cout << CyclicShift(pattern, S);

    return 0;
}

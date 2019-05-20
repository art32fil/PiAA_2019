#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector<int> prefix_function (string s, char J) { //префикс-функция
    int n = (int) s.length();
    vector<int> p (n);
    for (int i=1; i<n; ++i) {
        int j = p[i-1];
        while (j > 0 && (s[i] != s[j] || s[j] != J))
            j = p[j-1];
        if (s[i] == s[j] || s[j] == J) ++j;
        p[i] = j;
    }
    return p;
}

queue<int> kmp(string P, string T, char J) //выбор нужных результатов префикс-функции
{
    int pl = P.length();
    int tl = T.length();
    queue<int> answer;
    if (J != '#')
        vector<int> p = prefix_function(P + "#" + T, J);
    else
        vector<int> p = prefix_function(P + "$" + T, J);
    for (int i=0; i<tl; i++){
        if (p[pl+i+1] == pl)
            answer.push(i - pl + 1);
    }
    return answer;
}

int main()
{
    string P, T;
    char J;
    queue <int> result;
    cin >> T;
    cin >> P;
    cin >> J;
    result = kmp(P, T, J);
    if (result.size())
    {
        while (!result.empty())
        {
            cout << result.front() << endl;
            result.pop();
        }
    }
    else
        cout << -1;
    return 0;
}


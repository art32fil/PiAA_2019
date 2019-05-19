#include <QCoreApplication>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>

using namespace std;

class KMP
{
private:
    string P;   //шаблон
    string T;   //текст
    size_t *pi; //массив значений префикс-функции шаблона
    vector<size_t> result_entrances;

    inline void prefix()
    {
        pi[0] = 0;
        for(size_t j=0, i=1; i<P.length();)
        {
            if(P[i]==P[j])
            {
                pi[i] = j+1;
                i++;
                j++;
            }
            else
            {
                if(j==0)
                {
                    pi[i++]=0;
                }
                else
                {
                    j = pi[j-1];
                }
            }
        }
    }

public:
    KMP(string P, string T)
    {
        this->P = P;
        this->T = T;

        pi = new size_t[P.length()];
    }

    ~KMP()
    {
        delete pi;
    }

    void find_entrances()
    {
        prefix();
        int index = -1;
        for(size_t k=0, i=0; k<T.length(); )
        {
            if(T[k] == P[i])
            {
                if(index == -1)
                    index = k;
                k++;
                i++;
                if(i == P.length())
                {
                    result_entrances.push_back(index);
                    index = -1;
                }
            }
            else
            {
                if(i==0)
                {
                    k++;
                    index = -1;
                }
                else
                {
                    i = pi[i-1];
                    index = k - i;
                }
            }
        }
    }

    void print_entrances()
    {
        if(result_entrances.size() == 0)
        {
            cout << -1 << endl;
            return;
        }
        cout << result_entrances.front();
        for(vector<size_t>::iterator it = result_entrances.begin()+1; it != result_entrances.end(); it++)
        {
            cout << "," << *it;
        }
        cout << endl;
    }

    int find_cyclic_shift()
    {
        if(P.length() != T.length())
            return -1;

        result_entrances.clear();
        string save_P = P;
        P = T;
        T = save_P + save_P;
        find_entrances();

        if(result_entrances.size() == 0)
            return -1;

        return result_entrances.at(0);
    }
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string P, T;
    cin >> P >> T;
    KMP kmp(P, T);
    cout << kmp.find_cyclic_shift() << endl;
//    kmp.find_entrances();
//    kmp.print_entrances();

    return a.exec();
}

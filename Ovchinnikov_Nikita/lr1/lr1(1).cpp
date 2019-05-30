#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <cstddef>
#include <stdio.h>

using namespace std;

typedef unsigned char cell;

class qdr
{
public:
    cell x = 0;
    cell y = 0;
    cell w = 0;

public:
    explicit qdr(cell xx = 0, cell yy = 0, cell ww = 0) : x(xx), y(yy), w(ww) {}

    qdr& init(cell xx, cell yy, cell ww)
    {
        x = xx; y = yy; w = ww;
        return *this;
    }
};

class Table
{
private:
    size_t N;
    cell **table;
    vector<qdr> bestArr;
    vector<qdr> singleArr;
    cell bestValue = 255;
    cell singleValue = 0;
    cell x, y;
    size_t max_w;
    bool key = false;

public:
    explicit Table(size_t N)
    {
        if (N > 40 || N < 2)
            N = 0;
        this->N = N;
        max_w = this->N;
        table = new cell*[N];
        for (cell i = 0; i<N; i++)
            table[i] = new cell[N]();
        x = y = 0;
        begin();
    }

    ~Table()
    {
        for (cell i = 0; i<N; i++)
            delete table[i];
        delete table;
    }

    void getResult()
    {
        go();
        printResult();
    }

private:
    void go()
    {
        if (key)
            return;
        if (!getFirstEmpty() || singleValue >= bestValue)
        {
            if (bestValue > singleValue)
            {
                bestValue = singleValue;
                bestArr = singleArr;
            }

            qdr *tmp = new qdr;
            do
            {
                *tmp = removeQdr();
                if ((*tmp).w == 255)
                {
                    key = true;
                    return;
                }
            } while ((*tmp).w < 2 && !singleArr.empty());

            if (singleArr.empty() && (*tmp).w == 1)
            {
                return;
            }

            (*tmp).w--;
            putQdr(*tmp, 1);
            delete tmp;

            go();
        }
        else
        {
            putQdr();
            go();
        }
    }

    bool getFirstEmpty()
    {
        x = y = 0;
        for (cell i = 0; i<N; i++)
            for (cell k = 0; k<N; k++)
                if (table[i][k] == 0)
                {
                    y = i;
                    x = k;
                    return true;
                }
        return false;
    }

    void putQdr()
    {
        cell max = 0;
        while (x + max < N && y + max < N && table[y][x + max] == 0 && table[y + max][x] == 0)
            max++;
        max = max == N ? max - 1 : max;
        max = max > max_w ? max_w : max;
        for (cell i = y; i < y + max; i++)
            for (cell k = x; k < x + max; k++)
                table[i][k] = 1;
        singleArr.push_back(qdr(x, y, max));
        singleValue++;
//printTable();
    }

    void putQdr(qdr &tmp, unsigned char number)
    {
        for (cell i = tmp.y; i < tmp.y + tmp.w; i++)
            for (cell k = tmp.x; k < tmp.x + tmp.w; k++)
                table[i][k] = number;
        singleArr.push_back(tmp);
        singleValue++;
//printTable();
    }

    qdr removeQdr()
    {
        qdr tmp = singleArr.back();
        if (table[tmp.y][tmp.x] == 2)
            return qdr(0, 0, 255);
        for (cell i = tmp.y; i < tmp.y + tmp.w; i++)
            for (cell k = tmp.x; k < tmp.x + tmp.w; k++)
                table[i][k] = 0;
        singleArr.pop_back();
        singleValue--;
//printTable();
        return tmp;
    }

    void begin()
    {
        qdr *tmp = new qdr;
        if (N % 2 == 0)
        {
            putQdr(tmp->init(0, 0, N / 2), 2);
            putQdr(tmp->init(0, N / 2, N / 2), 2);
            putQdr(tmp->init(N / 2, 0, N / 2), 2);
            putQdr(tmp->init(N / 2, N / 2, N / 2), 2);
        }
        else if (N % 3 == 0)
        {
            putQdr(tmp->init(0, 0, N/3*2), 2);
            putQdr(tmp->init(0, N / 3 * 2, N/3), 2);
            putQdr(tmp->init(N / 3, N / 3 * 2, N/3), 2);
            putQdr(tmp->init(N / 3 * 2, 0, N/3) , 2);
            putQdr(tmp->init(N / 3 * 2, N / 3, N / 3), 2);
            putQdr(tmp->init(N / 3 * 2, N / 3 * 2, N / 3), 2);
        }
        else
        {
            putQdr(tmp->init(0, 0, N / 2 + 1), 2);
            putQdr(tmp->init(N / 2 + 1, 0, N / 2), 2);
            putQdr(tmp->init(0, N / 2 + 1, N / 2), 2);
            max_w = N / 2 / 2 + 1;
        }
        delete tmp;
    }

    void printResult()
    {
        printf("%u\n", bestValue);
        for (vector<qdr>::iterator it = bestArr.begin(); it != bestArr.end(); it++)
            printf("%u %u %u\n", (*it).x+1, (*it).y+1, (*it).w);
    }

    void printTable()
    {
        for (cell i = 0; i< N; i++)
        {
            for (cell k = 0; k < N; k++)
                printf("%u ", table[i][k]);
            cout << endl;
        }
        cout << endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    size_t N;
    cin >> N;
    Table answer(N);
    answer.getResult();

    return a.exec();
}

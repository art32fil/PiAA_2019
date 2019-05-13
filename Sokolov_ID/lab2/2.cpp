#include <fstream>
#include <iostream>
#include <cfloat>
#include <vector>
using namespace std;
class Graph
{
private:
    vector<vector<double>>  mas;			// Граф
    double *dist;			// Дистанции от нач. вершины к такой-то вершине
    char *prew;			// Предыдущая вершина на пути следования ннач->конеч
    char *name;			// Вершины, исп.-е в графе
    char size;			// Количество вершин в графе
    bool *check;


    void print_way(char beg, char end);		// Напечатать существующий путь от beg к end
    char accordance(char h);				// Номер вершины в таблице имен

    char f(/*char end,*/ char *h);

public:
    Graph(istream &in):
            mas(28, vector<double>(28, -1)),
            size(0){

        while (!in.eof())
        {
            char a, b;
            double c;
            in >> a >> b >> c;
             if(a=='.')break;
            a -= 'a';
            b -= 'a';

            mas[a][b] = c;

            if (mas[a][a] == -1) { mas[a][a]--; size++; }
            if (mas[b][b] == -1) { mas[b][b]--; size++; }
        }
                
        dist = new double[size];// Дистанции от нач. вершины к такой-то вершине
        name = new char[size];// Вершины, исп.-е в графе
        prew = new char[size];// Предыдущая вершина на пути следования ннач->конеч
        check = new bool[size]();//были в вершине или нет


        int i;	// Гуляем по графу
        i = 0;
        for (int k = size; k > 0; k--)
        {
            while (mas[i][i] == -1) i++;

            dist[size - k] = DBL_MAX;
            name[size - k] = (char)i;

            mas[name[size - k]][name[size - k]] = -1;

            i++;
        }
    }
    void A_star(char beg, char end);		// Запуск A*

};

// Ищем соответсвие вершины графа месту в таблице имён
char Graph::accordance(char h)
{
    h -= 'a';
    for (int i = 0; i < size; i++)
    {
        if (h == name[i]) return i;
    }
    throw " ";
}

// Нарисовать путь от beg до end
void Graph::print_way(char beg, char end)
{
    if (end != beg)
    {
        print_way(beg, prew[end]);
    }

    std::cout << (char)(name[end] + 'a');
}


// Запуск A*
void Graph::A_star(char beg, char end)
{
    beg = accordance(beg);
    end = accordance(end);

    char *h = new char[size];
    for (int i = 0; i < size; i++)
    {
        h[i] = abs(name[end] - name[i]);//массив для эвристики по алфавиту
    }

    check[beg] = true;

    if (beg != end)
    {
        dist[beg] = 0;

        char s = 0;
        for (char i = 0; i < size; i++)		// Цикл "пока не най"
            if (mas[name[beg]][name[i]] != -1)
            {
                dist[i] = mas[name[beg]][name[i]];
                prew[i] = beg;
            }


        while ((s = f(h)) != end)//если вершина вернувшаяся не конечная то продолжаем поиск
        {
            check[s] = true;//отмечаем что вершина пройдена

            for (int i = 0; i < size; i++)
            {
                double d = mas[name[s]][name[i]];

                if ((d != -1) && !check[i] && (d + dist[s] < dist[i]))//если есть путь и мы не смотрели эту вершину и путь до неё меньше, то записываем вершину в предыдущую, а в в дистанцию, новую (по пути)
                {
                    prew[i] = s;
                    dist[i] = d + dist[s];
                }
            }
        }
    }

    print_way(beg, end);//выводим
}


// Эвристическая функция для A*
char Graph::f(char *h)
{
    char ret = -1;
    double d = DBL_MAX;


    for (char i = 0; i < size; i++)//ищем минимальное ребро из данной вершины
    {
        if (!check[i] && dist[i] + h[i] <= d)
        {
            // if (ret == i)
            // ret = h[ret] < h[i] ? ret : i;

            ret = i;
            d = dist[i] + h[i];
        }
    }
    return ret;//возвращает вершину куда двигаемся
}

int main()
{
    char a, b;

    std::cin >> a >> b;

    Graph qw(cin);

    qw.A_star(a, b);

    return 0;
}

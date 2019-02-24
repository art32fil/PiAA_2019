#include <iostream>

using namespace std;

struct Square
{
    int x;
    int y;
    int size;
};

typedef Square *square_list;

//Функции для работы с полем большого квадрата

bool is_enough_space(int **square_field, int square_size, int i, int j, int size)
{
    if ((i + size > square_size) || (j + size > square_size))
        return false;
    for (int x = i; x - i < size; x++)
        for (int y = j; y - j < size; y++)
            if (square_field[x][y] != 0)
                return false;
    return true;
}

bool is_full(int **square_field, int square_size)
{
    for (int i = 0; i < square_size; i++)
        for (int j = 0; j < square_size; j++)
            if (square_field[i][j] == 0)
                return false;
    return true;
}

void insert_square(int **square_field, Square &square)
{
    for (int i = square.x; i - square.x < square.size; i++)
        for (int j = square.y; j - square.y < square.size; j++)
            square_field[i][j] = 1;
}

void delete_square(int **square_field, Square &square)
{
    for (int i = square.x; i - square.x < square.size; i++)
        for (int j = square.y; j - square.y < square.size; j++)
            square_field[i][j] = 0;
}

void print_field(int ** square_field, int square_size)
{
    cout << "--------------" << endl;
    for (int i = 0; i < square_size; i++)
    {
        for (int j = 0; j < square_size; j++)
            cout << square_field[i][j] << " ";
        cout << endl;
    }
    cout << "--------------" << endl;
}

//-----------------------------------------------

//Функции, выполняющие разбиение квадрата на минимальное число обрезков
//Случай, сторона делится на 2
void formAnswer_multOf2(square_list &solution, int &min_count, int size)
{
    min_count = 4;
    int size_1 = size / 2;
    int coordinate_1 = size_1 + 1;
    solution[0] = {1, 1, size_1};
    solution[1] = {1, coordinate_1, size_1};
    solution[2] = {coordinate_1, 1, size_1};
    solution[3] = {coordinate_1, coordinate_1, size_1};
    return;
}

//Случай, когда сторона делится на 3
void formAnswer_multOf3(square_list &solution, int &min_count, int size)
{
    min_count = 6;
    int size_1 = size / 3;
    int size_2 = 2 * size_1;
    int coordinate_1 = size_1 + 1;
    int coordinate_2 = size_2 + 1;
    solution[0] = {1, 1, size_2};
    solution[1] = {1, coordinate_2, size_1};
    solution[2] = {coordinate_2, 1, size_1};
    solution[3] = {coordinate_1, coordinate_2, size_1};
    solution[4] = {coordinate_2, coordinate_1, size_1};
    solution[5] = {coordinate_2, coordinate_2, size_1};
    return;
}

//Случай, когда сторона делится на 5
void formAnswer_multOf5(square_list &solution, int &min_count, int size)
{
    min_count = 8;
    int size_1 = size / 5;
    int size_2 = 2 * size_1;
    int size_3 = 3 * size_1;
    int coordinate_1 = size_2 + 1;
    int coordinate_2 = size_3 + 1;
    int coordinate_3 = 4 * size_1 + 1;
    solution[0] = {1, 1, size_3};
    solution[1] = {1, coordinate_2, size_2};
    solution[2] = {coordinate_2, 1, size_2};
    solution[3] = {coordinate_2, coordinate_2, size_2};
    solution[4] = {coordinate_2, coordinate_1, size_1};
    solution[5] = {coordinate_3, coordinate_1, size_1};
    solution[6] = {coordinate_1, coordinate_2, size_1};
    solution[7] = {coordinate_1, coordinate_3, size_1};
    return;
}

//Функция перебора вариантов
void backtracking(square_list &solution, int &min_count,
                  square_list &now_solution, int now_count,
                  int **field, int field_size)
{
    if (now_count == min_count)
        return;
    if (is_full(field, field_size) && now_count < min_count)
    {
        min_count = now_count;
        for (int i = 0; i < min_count; i++)
            solution[i] = now_solution[i];
    }
    int start_size = 2 * field_size / 3;
    for (int i = 0; i < field_size; i++)
        for (int j = 0; j < field_size; j++)
            if (field[i][j] == 0)
            {
                for (int size = start_size; size >= 1; size--)
                    if (is_enough_space(field, field_size, i, j, size))
                    {
                        Square new_elem = {i, j, size};
                        now_solution[now_count] = new_elem;
                        insert_square(field, new_elem);
                        backtracking(solution, min_count, now_solution,
                                     now_count + 1, field, field_size);
                        delete_square(field, new_elem);
                    }
                return;
            }
    return;
}

//Обёртка на функцией выполнения бектрекинга, выполняющая приближение к ответу
void backtracking_main(square_list &solution, int &min_count, int size)
{
    square_list now_solution = new Square[min_count];

    //Первое приближение
    int size_1 = size / 2;
    int size_2 = size_1 + 1;
    int coordinate_1 = size_2;
    int coordinate_2 = size_2 + 1;
    now_solution[0] = {coordinate_1, coordinate_1, size_2};
    now_solution[1] = {1, coordinate_2, size_1};
    now_solution[2] = {coordinate_2, 1, size_1};

    //Подготовка к бектрекингу
    int field_size = size_2;
    int **square_field = new int *[field_size];
    square_field[0] = new int[field_size * field_size];
    for (int i = 1; i < field_size; i++)
        square_field[i] = square_field[i - 1] + field_size;
    for (int i = 0; i < field_size; i++)
        for (int j = 0; j < field_size; j++)
        {
            if ((i == field_size - 1) && j == (field_size - 1))
                square_field[i][j] = 1;
            else
                square_field[i][j] = 0;
        }

    //Перебор вариантов
    backtracking(solution, min_count, now_solution, 3, square_field, field_size);

    //Корректировка координат обрезков решения
    for (int i = 3; i < min_count; i++)
    {
        solution[i].x += 1;
        solution[i].y += 1;
    }

    delete [] square_field[0];
    delete [] square_field;
    delete [] now_solution;
    return;
}

int main()
{
    int min_count = 20; // Для рассматриваемого случая (square_size <= 40) оценка корректная
    square_list solution = new Square[min_count];
    int square_size;

    cin >> square_size;
    if (square_size % 2 == 0)
        formAnswer_multOf2(solution, min_count, square_size);
    else if (square_size % 3 == 0)
        formAnswer_multOf3(solution, min_count, square_size);
    else if (square_size % 5 == 0)
        formAnswer_multOf5(solution, min_count, square_size);
    else
        backtracking_main(solution, min_count, square_size);

    cout << min_count << endl;
    for (int i = 0; i < min_count; i++)
        cout << solution[i].x << " " << solution[i].y << " " << solution[i].size << endl;

    delete [] solution;
    return 0;
}

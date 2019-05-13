#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class Square {

	int N, minSquares, currentAmount, scale;
	vector<vector<int>> map;
	vector<vector<int>> answer;

public:

	Square(int size)
		: N(size)
		, map(size, vector<int>(size, 0))
		, minSquares(size*size + 1)
		, answer(size*size, vector<int>(3, 0))
		, currentAmount(0)
		, scale(1)
	{
		// оптимизация
		if (size % 2 == 0) {
			scale = size / 2;
			N = 2;
		}
		else if (size % 3 == 0) {
			scale = size / 3;
			N = 3;
		}
		else if (size % 5 == 0) {
			scale = size / 5;
			N = 5;//дальше перебирать смысла нет, если число не делится на 2,3,5 без остатка, то оно простое
		}
		else if (size % 2 == 1)
			opt();
	}

	void print()//вывод результата
	{
		cout << minSquares << char(10);

		for (int i = 0; i < minSquares; ++i)
			cout << answer[i][0] << " " << answer[i][1] << " " << answer[i][2] << char(10);
	}

	void backtracking(int x, int y)//бэктрекинг
	{
		if (currentAmount == minSquares)
		{
			return;
		}

		while (x < N)
		{
			while (y < N)
			{
				if (check_zero(x, y))
				{
					if (y > 0 && check_zero(x, y - 1)) return;

					for (int m = 1; m < N; ++m)
					{
						if (m == 1 ||
							(check_zero(x + m - 1, y + m - 1) &&//проверка на вместимость квадрата
								check_zero(x, y + m - 1) &&
								check_zero(x + m - 1, y)))
						{
							put_square(m, x, y);
							backtracking(x, y);
							remove_square(m, x, y);
						}
						else
						{
							return;
						}
					}
				}
				y++;
			}
			y = 0;
			x++;
		}

		if (is_map_filled())
		{
			if (currentAmount < minSquares) minSquares = currentAmount;
			update_result_table();
		}
	}

	void update_result_table()//обновление таблицы результатов
	{
		int m = 1;

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (map[i][j] == m)
				{
					int x = i;

					while (x < N && map[x][j] == m)
					{
						++x;
					}

					answer[m - 1][0] = scale * i + 1;
					answer[m - 1][1] = scale * j + 1;
					answer[m - 1][2] = scale * (x - i);

					++m;
					i = 0;
					j = 0;
				}
			}
		}
	}

	void opt()//оптимизация
	{
		// size , x      , y
		put_square((N + 1) / 2, 0, 0);
		put_square((N - 1) / 2, 0, (N + 1) / 2);
		put_square((N - 1) / 2, (N + 1) / 2, 0);
	}

	bool is_map_filled()//проверка на полное замащение
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (map[i][j] == 0) return false;
			}
		}
		return true;
	}

	void put_square(int m, int x, int y)//добавление квадрата
	{
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				map[i + x][j + y] = currentAmount + 1;
			}
		}

		++currentAmount;
	}

	void remove_square(int m, int x, int y)//очистка квадрата
	{
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				map[i + x][j + y] = 0;
			}
		}

		currentAmount--;
	}

	bool check_zero(int x, int y)//проверка на незаполненый элемент
	{
		if (x >= N || y >= N || map[x][y])
			return false;
		else
			return true;
	}
};

int main()
{
	int N;
	cin >> N;

	Square obj(N);
	obj.backtracking(0, 0);
	obj.print();

	return 0;
}


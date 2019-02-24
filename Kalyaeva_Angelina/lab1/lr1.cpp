#include <iostream>
#include<ctime>

using namespace std;

class Square {
	int size;
	int **square;
	int **best_square;
	int count;
	int best_count;
public:
	Square(int size, int count) :size(size), count(count), best_count(size*size) {
		square = new int*[size];
		best_square = new int *[size];
		for (int i = 0; i < size; i++) {
			square[i] = new int[size];
			best_square[i] = new int[size];
			for (int j = 0; j < size; j++) {
				square[i][j] = 0;
				best_square[i][j] = 0;
			}
		}
	}

	~Square() {
		for (int i = 0; i < size; i++) {
			delete[] square[i];
			delete[] best_square[i];
		}
		delete[] square;
		delete[] best_square;
	}

	void start() {	//начальная функция для вставки первых 3х квадратов
		int tmp = size / 2;
		insert(0, 0, tmp + 1);
		insert(0, tmp + 1, tmp);
		insert(tmp + 1, 0, tmp);
	}

	void insert(int x, int y, int number) { //вставка квадрата заданного размера
		for (int i = x; i <x + number; i++) {
			for (int j = y; j <y + number; j++) {
				square[i][j] = number;
			}
		}
		count++;
	}

	bool is_posible(int x, int y, int number) { //можно ли поставить квадрат заданного размера 
		if (x + number > size || y + number > size) {
			return false;
		}
		for (int i = x; i < x + number; i++) {
			for (int j = y; j < y + number; j++) {
				if (square[i][j] != 0) {
					return false;
				}
			}
		}
		return true;
	}

	bool is_empty(int & x, int & y) { //есть ли пустые клеточки
		while (square[x][y] != 0) {
			if (y == size - 1) {
				if (x == size - 1) {
					return false;
				}
				else {
					x++;
					y = size / 2;
					continue;
				}
			}
			y++;
		}
		return true;
	}

	void remove_square(int x, int y, int number, int **arr) {	//удаление квадрата заданной стороны
		for (int i = x; i <x + number; i++) {
			for (int j = y; j <y + number; j++) {
				arr[i][j] = 0;
			}
		}
	}

	void print_result(int k) {	//вывод результата
		cout << best_count << endl;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (best_square[i][j] != 0) {
					cout << i*k + 1 << " " << j*k + 1 << " " << best_square[i][j] * k << endl;
					remove_square(i, j, best_square[i][j], best_square);
				}
			}
		}
	}

	void my_print() {	//вывод квадрата
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << square[i][j] << " ";
			}
			cout << endl;
		}
	}

	void my_best_print() {	//вывод квадрата
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << best_square[i][j] << " ";
			}
			cout << endl;
		}
	}

	void copy_square() {	//сохранение лучшего квадрата
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				best_square[i][j] = square[i][j];
			}
		}
	}

	void backtracking(int x, int y) { //рекурсивная функция реализующая бектрекинг
		if (count >= best_count) {
			return;
		}
		for (int n = size / 2; n > 0; n--) {
			if (is_posible(x, y, n)) {
				insert(x, y, n);
				int next_x = x;
				int next_y = y;
				if (is_empty(next_x, next_y)) {
					backtracking(next_x, next_y);
				}
				else {
					if (count < best_count) {
						copy_square();
						best_count = count;
					}
					count--;
					remove_square(x, y, n, square);
					return;
				}
				count--;
				remove_square(x, y, n, square);
			}
		}
	}

};

void devided_by_two(int size) {
	cout << 4 << endl;
	cout << 1 << " " << 1 << " " << size << endl;
	cout << 1 + size << " " << 1 << " " << size << endl;
	cout << 1 << " " << 1 + size << " " << size << endl;
	cout << 1 + size << " " << 1 + size << " " << size << endl;
}

int main() {
	int size = 0, k = 1;
	cin >> size;
	if (size % 2 == 0) {
		devided_by_two(size / 2);
	}
	else {
		if (size % 3 == 0) {
			k = size / 3;
			size = 3;

		}
		else if (size % 5 == 0) {
			k = size / 5;
			size = 5;
		}
		Square A(size, 0);
		A.start();
		A.backtracking(size / 2, size / 2 + 1);
		A.print_result(k);
	}
	return 0;
}

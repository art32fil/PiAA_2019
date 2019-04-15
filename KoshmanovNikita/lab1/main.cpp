#include <iostream>
#include <vector>

using namespace std;

class Square{
public:
    int x, y, w;
    Square(int x, int y, int w) : x(x), y(y), w(w){}
    void out(int k){

        cout << x*k+1 << " " << y*k+1 << " " << w*k << endl;
    }
};

vector<Square> listSquare;
vector<Square> result;

bool start_square(int **square, int size, int &x, int &y){
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if(square[i][j] == 0){
                x = i;
                y = j;
                return true;
            }
    return false;
}

bool fill_square(int **square, int x, int y, int w, int size){
    if (x + w > size || y + w > size)
        return false;

    for(int i = x; i < x + w; i++)
        for(int j = y; j < y + w; j++)
            if(square[i][j] != 0)
                return false;

    return true;
}

void insert_square(int **square, int x, int y, int w, int var){
    for(int i = x; i < x + w; i++)
        for(int j = y; j < y + w; j++)
            square[i][j] = var;
}

void delete_square(int **square, int x, int y, int w){
    for(int i = x; i < x + w; i++)
        for(int j = y; j < y + w; j++)
            square[i][j] = 0;
}

int side_square(int x, int y, int size){
    if(size - x < size - y)
        return size - x;
    else
        return size - y;
}

void backtracking(int **square,int size, int &minS, int count){
    if(minS < count)
        return;

    int x_start = 0, y_start = 0;

    if(start_square(square, size, x_start, y_start) == false){
        if(count - 1 < minS){
            minS = count - 1;
            result = listSquare;
        }
    }
    else{
        int new_size = side_square(x_start, y_start, size);
        if(new_size > size - 1){
            new_size = size - 1;
        }
        for(int i = new_size; i > 0; i--){
            if(fill_square(square, x_start, y_start, i, size)){
                insert_square(square, x_start, y_start, i, count);
                Square sq(x_start, y_start, i);
                listSquare.push_back(sq);
                backtracking(square, size, minS, count+1);
                listSquare.pop_back();
                delete_square(square, x_start, y_start, i);
            }
        }
    }
}

int main()
{
    int N;
    cin >> N;
    int k = 0;
    for(int i = 2; i <= N; i++){
        if(N % i == 0){
            k = N/i;
            N = i;
            break;
        }
    }
     int minS = 20;

     int **square = new int*[N];
     for(int i = 0; i < N; i++){
         square[i] = new int[N];
         for(int j = 0; j < N; j++){
             square[i][j] = 0;
         }
     }

    int size1 = (N + 1) / 2,
        size2 = N - (N + 1) / 2;

    int count = 1;
    insert_square(square, 0, 0, size1, count); count++;
    insert_square(square, 0, size1, size2, count); count++;
    insert_square(square, size1, 0, size2, count); count++;

    listSquare.push_back(Square(0, 0, size1));
    listSquare.push_back(Square(0, size1, size2));
    listSquare.push_back(Square(size1, 0, size2));

     backtracking(square, N, minS, count);

     cout << minS << endl;
     for(int i = 0; i < result.size(); i++){
         result[i].out(k);
     }

     for (int i = 0; i < N; i++)
          delete[] square[i];
     delete[] square;

    return 0;
}

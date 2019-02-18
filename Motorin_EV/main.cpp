#include <iostream>
using namespace std;

int CONSTANTS[] = {0,6,8,9,6,11,11,6,12,13,6,13,8,6,15,15,6,8,15,6}; // константы

class Square {
    public:
    Square(int sideLength) {
        sideLen = sideLength;
        minCount = CONSTANTS[(sideLength - 1) / 2];
        
        //выделение памяти
        answerArr = new Data*[CONSTANTS[(sideLength - 1) / 2]];
        SQUARE = new int*[sideLength];
        for(int i = 0; i < sideLength; i++) {
            SQUARE[i] = new int[sideLength];
            for (int j = 0;j < sideLength; j++)
            SQUARE[i][j] = 0;
        }
    }
    
    void printResult() {
        if (sideLen % 2){ // если сторона не кратна 2м
            if (!(sideLen % 3))
                subLen = 2 * sideLen / 3;
            else if (!(sideLen % 5))
                subLen = 3 * sideLen / 5;
            else
                subLen = (sideLen + 1) / 2;
            
            searchSubSquares(SQUARE, subLen, 0, 0, 0, exitFlag);
            cout << minCount << endl;
            for (int i=0; i < CONSTANTS[(sideLen - 1) / 2]; i++) {
                cout << answerArr[i]->x << " " << answerArr[i]->y << " " << answerArr[i]->length << endl;
            }
        }
        else{ // если сторона кратна 2м
            subLen = sideLen / 2;
            evenSide(subLen,1,1);
        }
    }
    
    void clearMemory() {
        for(int i = 0; i < CONSTANTS[(sideLen - 1) / 2]; i++)
            delete [] answerArr[i];
        delete [] answerArr;
        
        for(int i = 0; i < sideLen; i++)
            delete[] SQUARE[i];
        delete[] SQUARE;
    }
    
    class Data {
        public:
        int x;
        int y;
        int length;
    };
    
    private:
    int sideLen; // длина стороный квадарата
    //int* dataArr; // массив [x, y, side]...[]
    Data** answerArr;
    int** SQUARE; // основной квадрат
    int color = 0; // цвет раскраски (количестов цветов должно быть меньше минимального количества подквадратов)
    bool exitFlag = false; // условие выхода
    int minCount; // минимальное количество подквадратов
    int subLen; // длина стороны первого подквадрата
    
    void evenSide(int size,int x,int y){
        printf("4\n%d %d %d\n", x, y, size);
        printf("%d %d %d\n", x+size, y, size);
        printf("%d %d %d\n", x, y+size, size);
        printf("%d %d %d\n", x+size, y+size, size);
    }
    
    inline void searchSubSquares(int** SQUARE, //основной квадрат (матрица с цветами)
                                 int subLen, // длина стороны подквадрата
                                 int x, int y, // координаты подквадрата
                                 int color, // цвет раскраски
                                 bool &exitFlag) {
        
        //условия выхода
        if (exitFlag || color == minCount || x+subLen > sideLen || y+subLen > sideLen) return;
        for (int j = y; j < y+subLen; j++)
            if (SQUARE[x][j] != 0) return; // если подквадрат уже закрашен
        
        //сохранение подквадрата
        Data* d = new Data();
        d->x = x+1;
        d->y = y+1;
        d->length = subLen;
        answerArr[color] = d;
        
        //раскраска
        color++;
        for (int i = x;i<x+subLen;i++)
            for (int j = y; j < y+subLen; j++)
                SQUARE[i][j] = color;
        
        
        // поиск начала нового подквадрата / выход
        int k = x,m = y;
        for (struct {int i=0; bool flag = true;} s; s.i<sideLen, s.flag;s.i++) for (int j=0;j<sideLen;j++) {
                if (SQUARE[s.i][j] == 0){
                    x = s.i;
                    y = j;
                    s.flag = false;
                    break;
                }
                if (s.i == sideLen-1 && j == sideLen-1){
                    if (minCount == color){
                        exitFlag = true;
                        s.flag = false;
                        break;
                    }
                }
            }
        
        
        int minLen = min(sideLen-x,sideLen-y);
        if ((x == (sideLen+1)/2 && y == 0) || (x == 0 && y == (sideLen+1)/2))
            searchSubSquares(SQUARE,minLen,x,y,color,exitFlag);
        else
            for (int i=minLen;i>0;i--){
                searchSubSquares(SQUARE,i,x,y,color,exitFlag);
        }
        
        for (int i = k;i<k+subLen;i++)
            for (int j = m;j<m+subLen;j++)
                SQUARE[i][j] = 0;
    }
};

int main() {
    cout << "Enter side length: ";
    int n;
    cin >> n;
    
    if (n < 2 || n > 40){
        cout << "Wrong Input!\n";
        return 0;
    }
    
    Square s = Square(n);
    s.printResult();
    
    return 0;
}

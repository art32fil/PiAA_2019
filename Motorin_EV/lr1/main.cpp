#include <iostream>
using namespace std;

class Square {
    public:
    Square(int sideLength) {
        sideLen = sideLength;
        MAX_LIMIT = 20;// верхняя граница
        
        //выделение памяти
        answerArr = new Data*[MAX_LIMIT];
        SQUARE = new int*[sideLength];
        
        for (int i = 0; i < MAX_LIMIT; i++) {
            Data* d = new Data();
            answerArr[i] = d;
        }
        
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
            
            searchSquares(SQUARE,subLen, 0, 0, MAX_LIMIT,color);
            
            cout << MAX_LIMIT << endl;
            for (int i=0; i < MAX_LIMIT; i++) {
                cout << answerArr[i]->x << " " << answerArr[i]->y << " " << answerArr[i]->length << "\n";
                
                if(answerArr[i+1]->length == 0) break;
            }
            
        }
        else{ // если сторона кратна 2м
            subLen = sideLen / 2;
            evenSide(subLen,1,1);
        }
    }
    
    void clearMemory() {
        for(int i = 0; i < MAX_LIMIT; i++)
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
    Data** answerArr;
    int** SQUARE; // основной квадрат
    int color = 0; // цвет раскраски (количестов цветов должно быть равно минимальному количеству приближений)
    bool exitFlag = false; // условие выхода
    int subLen; // длина стороны первого приближения
    
    int MAX_LIMIT; // верхняя граница приближений
    
    void evenSide(int size,int x,int y){
        printf("4\n%d %d %d\n", x, y, size);
        printf("%d %d %d\n", x+size, y, size);
        printf("%d %d %d\n", x, y+size, size);
        printf("%d %d %d\n", x+size, y+size, size);
    }
    
    
    inline void searchSquares(int** SQUARE, // главная область
                       int currentLen, // сторона приближения
                       int x,int y, // координаты приближения
                       int &squaresCount, // минимальное кол-во приближений
                       int color // текущий цвет
    ){ //
        
        if (color >= squaresCount) //Если кол-во итераций превысило минимум, выходим
        return;
        
        //приближение выходит за границу квадрата
        if (x + currentLen > sideLen || y + currentLen > sideLen)
        return;
        
        //закраска попдает на уже закаршенную область
        for (int j = y;j<y+currentLen;j++)  if (SQUARE[x][j] != 0)
        return;
        
        // Смена цвета
        color++;
        
        //Закраска квадрата
        for (int i = x;i < x + currentLen; i++) for (int j = y;j < y + currentLen; j++)
        SQUARE[i][j] = color;
        
        int nx = x,ny = y; // запоминаем для возврата, если новое приближение не подойдет
        bool flag = true; //усли начало следующего приближения найдено
        
        for (int i=0;i<sideLen;i++){
            if (!flag) break; // выходим, если найдено новое приближение
            
            for (int j=0;j<sideLen;j++){
                
                //Если находим пустое место то запоминаем координаты, идем по квадрату слева направо сверху вниз
                if (SQUARE[i][j] == 0){
                    x = i;y = j;
                    flag = false;
                    break;
                }
                
                // Если квадрат полность закрашен и количество цветов < количества приближений
                if (i == sideLen-1 && j == sideLen-1 && squaresCount > color){
                    cout << color << endl;
                    int len = 0; // ширина приближения
                    int numb = 1; // цвет за пределами приближения
                    int index = 0;
                    
                    //заполнение данных в массив (индексы углов и размеры квадратов)
                    for (int i=0;i<sideLen;i++){
                        for (int j=0;j<sideLen;j++){
                            if (SQUARE[i][j] == numb){
                                answerArr[index]->x = i+1;
                                answerArr[index]->y = j+1;
                                int z = j;
                                while(SQUARE[i][z]==numb){
                                    len++;
                                    z++;
                                }
                                answerArr[index]->length = len;
                                index++;
                                len = 0;
                                numb++;
                            }
                        }
                    }
                    squaresCount = color;
                    flag = false;
                    break;
                }
            }
        }
        
        // максимальный новый квадрат
        int subSquareLen = min(sideLen-x,sideLen-y);
        
        //максимальный квадрат берется для данных координат
        if ((x == (sideLen+1)/2 && y == 0) || (x == 0 && y == (sideLen+1)/2))
        searchSquares(SQUARE,subSquareLen, x,y,squaresCount,color);
        
        //в другом случае
        else for (int i=subSquareLen;i>0;i--){
            searchSquares(SQUARE,i,x,y,squaresCount,color);
        }
        //удаление неудовлетворяющих квадратов
        for (int i = nx;i<nx+currentLen;i++) for (int j = ny;j<ny+currentLen;j++)
        SQUARE[i][j] = 0;
    }
    
};

int main() {
    //cout << "Enter side length: ";
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


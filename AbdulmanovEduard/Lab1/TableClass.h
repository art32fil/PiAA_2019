#ifndef TABLECLASS_H_INCLUDED
#define TABLECLASS_H_INCLUDED
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

struct Cell{
    int c_lenght;
    int c_count;
};
class TableClass{
public:
    TableClass(int N){
        this->N=N;
        squareCount=0;
        squareOneLenght=0;
        maxSquareOneLenght=N*N;
        for(int i=0;i<N;i++){
            table.insert(table.end(),vector<Cell>(N));
        }
    }
    void Build(){
        int littleDivider=IsPrime();
        if(littleDivider){
            minSquare=N*N+1;
            startBuildNoPrimeTable(N*(littleDivider-1)/littleDivider,N/littleDivider);
        }
        else{
            minSquare=3+6*log2(N/2+1);
            squareCount=1;
            setSquare(0,0,N/2+1);
            squareCount=2;
            setSquare(N/2+1,0,N/2);
            squareCount=3;
            setSquare(0,N/2+1,N/2);
            startBuildPrimeTable(N/2,N/2,N/2);
        }
        writeTable(answerTable);
    }

    void writeTable(vector<vector<Cell>> matrix){
       cout<<minSquare<<"  "<<endl;
        for(int i=1;i<=minSquare;i++){
            for(int y=0;y<N;y++){
                int lenght=0;
                for(int x=0;x<N;x++){
                    if(matrix[y][x].c_count==i){
                        lenght=matrix[y][x].c_lenght;
                        cout<<x+1<<" "<<y+1<<" "<<lenght<<endl;
                        break;
                    }
                }
                if(lenght)
                    break;
            }
        }

    }
private:
    vector<vector<Cell>> table;
    int squareCount;
     int minSquare;
    vector<vector<Cell>> answerTable;
    int squareOneLenght;
    int maxSquareOneLenght;
    int N;
    //Проверяет простое число или нет, если не простое,то вовзращает наименьший делитель числа
    int IsPrime(){
        short int m_array[]={3,5,7,11,13,17,19,23,29,31,37};
        for(int element:m_array)
            if(element==N)
                return 0;

        for(int i=2;i<N;i++){
            if(N%i==0)
                return i;
        }
    }

    //Поиск пустой клетки на столе
   inline bool FindFreeCellForSquare(int &x,int &y,int startX,int startY){
        for(int yy=startY;yy<N;yy++){
            for(int xx=startX;xx<N;xx++){
                if(table[yy][xx].c_lenght==0){
                    x=xx;
                    y=yy;
                    return true;
                }
            }
        }
        return false;
    }

    inline void setSquare(int x,int y,int lenght){
        for(int yy=y;yy<y+lenght;yy++)
            for(int xx=x;xx<x+lenght;xx++){
                table[yy][xx].c_lenght=lenght;
                table[yy][xx].c_count=squareCount;

            }

    }

    inline void clearSquare(int x,int y,int lenght){
        for(int yy=y;yy<y+lenght;yy++)
            for(int xx=x;xx<x+lenght;xx++){
                table[yy][xx].c_lenght=0;
                table[yy][xx].c_count=0;
            }
        squareCount--;
        if(lenght==1)
            squareOneLenght--;
    }

   inline bool canSetSquareThisLenght(int x,int y,int lenght){
        if(x+lenght>N||y+lenght>N) return 0;
        for(int yy=y;yy<y+lenght;yy++){
            for(int xx=x;xx<x+lenght;xx++){
                if(table[yy][xx].c_lenght!=0){
                    return false;
                }
            }
        }
        if(lenght==1)
            squareOneLenght++;
        squareCount++;
        setSquare(x,y,lenght);
        return true;
    }

    void IsMinSquarePacking(){
        if(squareCount<minSquare){
            minSquare=squareCount;
            maxSquareOneLenght=squareOneLenght;
            answerTable=table;
        }
    }

    void startBuildNoPrimeTable(int lenght,int littleDivider){
        int x;
        int y;
        if(squareCount>minSquare){
            return;
        }
        if(FindFreeCellForSquare(x,y,0,0)){
            for(int lenghtIndex=lenght;lenghtIndex>=N/littleDivider-1;lenghtIndex-=littleDivider){
                if(canSetSquareThisLenght(x,y,lenghtIndex)){
                    startBuildNoPrimeTable(lenght,littleDivider);
                    clearSquare(x,y,lenghtIndex);
                }
            }
            return;
        }
        IsMinSquarePacking();
    }

    void startBuildPrimeTable(int lenght,int xx,int yy){
        //writeTable(table);
        int x;
        int y;
        if(squareCount>=minSquare||squareOneLenght>maxSquareOneLenght){
            return;
        }
        if(answerTable.size()!=0&&(answerTable[N-1][N/2].c_lenght==table[N/2][N-1].c_lenght))
                        return;
        if(FindFreeCellForSquare(x,y,xx,yy)){
            for(int lenghtIndex=lenght;lenghtIndex>0;lenghtIndex--){
                if(canSetSquareThisLenght(x,y,lenghtIndex)){
                    startBuildPrimeTable(lenght,xx,y);
                    clearSquare(x,y,lenghtIndex);
                }
            }
            return;
        }
        IsMinSquarePacking();
    }
};


#endif // TABLECLASS_H_INCLUDED

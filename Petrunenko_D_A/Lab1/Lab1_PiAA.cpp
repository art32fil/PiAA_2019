#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
class simpleNum{
public:
    simpleNum(const int Num = 0) : N(Num), best(0), Best_mas(NULL){
        Arr = new int*[N];
        for(int i=0;i<N;i++){
            Arr[i] = new int[N];
                for(int j=0;j<N;j++)
                    Arr[i][j] = 0;}
        Best_mas = new int*[N];
                for(int i=0;i<N;i++){
                    Best_mas[i] = new int[N];
                        for(int j=0;j<N;j++)
                            Best_mas[i][j] = 0;}

                Arr[0][0] = 1;
                Arr[1][0] = 1;
    }

    void cleanSQ(int **tmp, int x, int y){
        int n = tmp[y][x];
        for(int i=y;i<n+y;i++)
            for(int j=x;j<n+x;j++)
               tmp[i][j] = 0;}

    void WriteB(int min){
        if(best==0||best>min){ best = min;
                for(int i=0;i<N;i++)
                        for(int j=0;j<N;j++)
                            Best_mas[i][j] = Arr[i][j];
        }
    }

    void fillM(int x,int y,int size, int** tmp){
        for(int i=y;i<size+y;i++)
            for(int j=x;j<size+x;j++)
                tmp[i][j] = size;
    }

    void find(int min, int Sq) {
        if(Sq==0){
            WriteB(min);
            return;  }
        if(best!=0&&best<=min) return;
        if(min>=(2*N)) return;
        int S_size = N-1, size = 0;
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                if(Arr[i][j]==0){
                    while((size+j<N)&&Arr[i][size+j]==0){
                               if(N-i<size+1) break;
                               size++;}
                   if(size>S_size) size = S_size;
                        for(int k=size;k>=1;k--){
                            fillM(j, i, k, Arr);
                            ++min;
                            find(min, Sq-k*k);
                            cleanSQ(Arr, j, i);
                            min--;
                            size--;

                }
                        return;
         }
        return;
    }

    void print(){
        cout<<"1 "<<"1 "<<N<<endl;
        cout<<1+N<<" 1 "<<N-1<<endl;
        cout<<"1 "<<N+1<<" "<<N-1<<endl;
        Best_mas[0][0] = 0;
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++){
                if(Best_mas[i][j]!=0){
                    cout<<j+N<<" "<<i+N<<" "<<Best_mas[i][j]<<endl;
                    cleanSQ(Best_mas, j, i);}
            }
        }

    void del(int ** Del_mas, int n){
        for(int i=0;i<n;i++)
            delete [] Del_mas[i];
        delete [] Del_mas;
    }
    ~simpleNum(){
    del(Arr, N);
    del(Best_mas, N);}
    int Best(){
        return best;
    }
private:
    int ** Best_mas;
    int best;
    int N;
    int ** Arr;
};

void multiple5(int N){
int min = 8, i = 1;
cout<<min<<endl;
cout<<i<<" "<<i<<" "<<3*N/5<<endl;
cout<<i<<" "<<i+3*N/5<<" "<<2*N/5<<endl;
cout<<i+2*N/5<<" "<<i+3*N/5<<" "<<N/5<<endl;
cout<<i+2*N/5<<" "<<i+4*N/5<<" "<<N/5<<endl;
cout<<i+3*N/5<<" "<<i<<" "<<2*N/5<<endl;
cout<<i+3*N/5<<" "<<i+2*N/5<<" "<<N/5<<endl;
cout<<i+4*N/5<<" "<<i+2*N/5<<" "<<N/5<<endl;
cout<<i+3*N/5<<" "<<i+3*N/5<<" "<<2*N/5<<endl;}

void multiple3(int N){
int min = 6, i = 1;
cout<<min<<endl;
cout<<i<<" "<<i<<" "<<2*N/3<<endl;
cout<<i<<" "<<i+2*N/3<<" "<<N/3<<endl;
cout<<i+N/3<<" "<<i+2*N/3<<" "<<N/3<<endl;
cout<<i+2*N/3<<" "<<i<<" "<<N/3<<endl;
cout<<i+2*N/3<<" "<<i+N/3<<" "<<N/3<<endl;
cout<<i+2*N/3<<" "<<i+2*N/3<<" "<<N/3<<endl;}

void multiple2(int N){
int min = 4, i = 1;
cout<<min<<endl;
cout<<i<<" "<<i<<" "<<N/2<<endl;
cout<<i<<" "<<i+N/2<<" "<<N/2<<endl;
cout<<i+N/2<<" "<<i<<" "<<N/2<<endl;
cout<<i+N/2<<" "<<i+N/2<<" "<<N/2<<endl;}


int main(){
    int N;
    cin>>N;
    if(N>=2&&N<=40){
    if(N%2==0) multiple2(N);
    else if(N%3==0) multiple3(N);
        else if(N%5==0) multiple5(N);
                else{
        simpleNum A(N/2+1);
        A.find(0, (N/2+1)*(N/2+1)-2);
        cout<<A.Best()+4<<endl;
        A.print();}
    }else cout<<"Wrong N!"<<endl;
    return 0;
}

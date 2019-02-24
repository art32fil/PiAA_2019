#include <iostream>
using namespace std;

class simpleNum{
public:
    simpleNum(const int Num = 0) : N(Num), best(0), Best_mas(NULL){
        Arr = new int*[(N/2)+1];
        for(int i=0;i<(N/2)+1;i++){
            Arr[i] = new int[(N/2)+1];
                for(int j=0;j<(N/2)+1;j++)
                    Arr[i][j] = 0;}
        Arr[0][0] = 1;
        Arr[1][0] = 1;}

    void cleanSQ(int **tmp, int x, int y){
        int n = tmp[y][x];
        for(int i=y;i<n+y;i++)
            for(int j=x;j<n+x;j++)
               tmp[i][j] = 0;}

    void Zero(int &x, int &y, int min){
        while(Arr[y][x]!=0)
            if((x+1)<(N/2)+1) x++;
            else if(x==y) { WriteB(min);
                break;}
                 else{ x=0; if((y+1)<(N/2)+1) y++;}
    }

    void WriteB(int min){
        if(best==0) best = min;
        if(best>min){ best = min;
        if(Best_mas!=NULL) del(Best_mas, best);
        Best_mas = new int*[best];
            for(int i=0;i<best;i++)
                Best_mas[i] = new int[3];
        int **tmp = new int*[(N/2)+1];
                for(int i=0;i<(N/2)+1;i++){
                    tmp[i] = new int[(N/2)+1];
                        for(int j=0;j<(N/2)+1;j++)
                            tmp[i][j] = Arr[i][j];}
            tmp[0][0] = 0;
            tmp[1][0] = 0;
            int k=0;
            for(int i=0;i<(N/2)+1;i++)
                for(int j=0;j<(N/2)+1;j++){
                    if(tmp[i][j]!=0){
                        Best_mas[k][0] = j;
                        Best_mas[k][1] = i;
                        Best_mas[k][2] = tmp[i][j];
                        cleanSQ(tmp, j, i);
                        k++;
                        if(k==best) break;
                    }
                    if(k==best) break;
                }
            del(tmp, (N/2)+1);}
    }

    void find(int x, int y, int min) {
        if(best!=0&&best<=min) return;
        if(min>=(2*N-1)) return;
        if((x>(N/2)+1)||y>(N/2)+1) return;
       if(Arr[y][x]!=0) {
       Zero(x, y, min);
       if(x==y) {WriteB(min); return;}
       }
       int size = 0;
       while(((x+size)<(N/2)+1)&&Arr[y][x+size]==0){
           if((N/2)+1-y<size+1) break;
           size++;}
        int last_X = x, last_Y = y;
       for(int k=size;k>=1;k--){
        for(int i=last_Y;i<size+last_Y;i++)
            for(int j=last_X;j<size+last_X;j++)
                  Arr[i][j] = size;
        ++min;
        x = 0; y = 0;
        Zero(x, y, min);
        find(x, y, min);
        cleanSQ(Arr, last_X, last_Y);
        min--;
        size--;
        }
    }

    void print(){
            cout<<"1 "<<"1 "<<(N/2)+1<<endl;
            cout<<1+(N/2)+1<<" 1 "<<N/2<<endl;
            cout<<"1 "<<1+(N/2)+1<<" "<<N/2<<endl;
            cout<<1+(N/2)<<" "<<1+(N/2)+1<<" 1"<<endl;
            for(int i=0;i<best;i++)
                cout<<Best_mas[i][0]+(N/2)+1<<" "<<Best_mas[i][1]+(N/2)+1<<" "<<Best_mas[i][2]<<endl;
        }

    void del(int ** Del_mas, int n){
        for(int i=0;i<n;i++)
            delete [] Del_mas[i];
        delete [] Del_mas;}

    ~simpleNum(){
    del(Arr, (N/2)+1);
    del(Best_mas, best);
    }
    int Best(){return best;}

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
    simpleNum A(N);
    A.find(1, 0, 0);
    cout<<A.Best()+4<<endl;
    A.print();}
    }else cout<<"Wrong N!"<<endl;
    return 0;
}

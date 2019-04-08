#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <iterator>
typedef unsigned short int type;
using namespace std;

struct Node{
    type y;
    type x;
    type size;
};

class Mass{
public:
    struct Node* vect;
    type counter;

    Mass() : counter(0){
        vect = new struct Node[80];
    }
    void push_back(struct Node& node){
        vect[counter].size = node.size;
        vect[counter].y = node.y;
        vect[counter++].x = node.x;
    }
    void pop_back(){
        counter--;
    }
    type size(){
        return counter;
    }
    Mass& operator=(Mass& clone){
        counter = clone.size();
        for(type i(0); i < counter; i++){
            vect[i].size = (clone.vect)[i].size;
            vect[i].y = (clone.vect)[i].y;
            vect[i].x = (clone.vect)[i].x;
        }
        return *this;
    }
    bool empty(){
        if(counter)
            return false;
        return true;
    }
    bool Fun(type N){
        if(vect->size < N / 2)
            return false;
        return true;
    }
    struct Node& back(){
        return vect[counter - 1];
    }
    void print(type N){
        cout << counter + 5 << endl;
        cout << "1 1 " << N << endl;
        cout << "1 " << 1+N << " " << N-1 << endl;
        cout << 1+N << " 1 " << N-1 << endl;
        cout << 1+N << " " << N << " 1" << endl;
        cout << N << " " << 1+N << " 2" << endl;
        for(type i(0); i < counter; i++){
            cout << vect[i].y+N << " " << vect[i].x+N << " " << vect[i].size << endl;
        }
    }
};

class SQ{
public:
    class Mass maxsquare;

    SQ(type size) : maxsize(9999), N(size){
        mass = new type*[N];
        for(type i(0); i < N; i++){
            mass[i] = new type[N];
            for(type j(0); j < N; j++)
                mass[i][j] = 0;
        }
        mass[0][0] = 3;
        mass[1][0] = 3;
    }

    void FindMAX(){
        while(1){
            if(NoHoles()){
                maxsquare = square;
                maxsize = maxsquare.size();
            }
            else
                SetSQ();
            if(square.size() >= maxsize){
                if(!RewriteSQ())
                    break;
                //else if(!square.Fun(N))
                   // break;
            }
        }
    }

private:
    type maxsize;
    type** mass;
    type N;
    class Mass square;

    bool NoHoles(){
        type i = 0;
        while(i < N)
            if(mass[N-1][i])
                i += mass[N-1][i];
            else
                return false;
        return true;
    }

    bool RewriteSQ(){
        if(square.empty())
            return false;
        struct Node &node = square.back();

        node.size--;
        mass[node.y + node.size][node.x] = 0;
        if(!node.size){
            square.pop_back();
            return RewriteSQ();
        }
        for(type i(node.y); i < node.y + node.size; i++)
            mass[i][node.x] = node.size;
        return true;
    }

    void SetSQ(){
        struct Node node;
        if(square.empty()){
            node.y = 0;
            node.x = 3;
            node.size = N - 3;
        }
        else{
            auto pointer = square.back();
            type i = pointer.y, j = pointer.x;
            type size;
            while(1)
                if(mass[i][j]){
                    size = mass[i][j];
                    j = (j+size) % N;
                    if(j < size)
                        i++;
                }
                else{
                    node.y = i;
                    node.x = j;
                    break;
                }
            node.size = 0;
            for(type it(node.x); it < N; it++)
                if(!mass[node.y][it])
                    node.size++;
                else
                    break;
            if(node.size > N - node.y)
                node.size = N - node.y;
        }
        for(type i(node.y); i < node.y + node.size; i++)
                mass[i][node.x] = node.size;
        square.push_back(node);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    type N;
    cin >> N;
    if(!(N % 2)){
        N /= 2;
        cout << "4" << endl;
        cout << "1 1 " << N << endl;
        cout << 1+N << " 1 " << N << endl;
        cout << "1 " << 1+N << " " << N << endl;
        cout << 1+N << " " << 1+N << " " << N << endl;
        return 0;
    }
    if(!(N % 3)){
        N /= 3;
        cout << "6" << endl;
        cout << "1 1 " << 2*N << endl;
        cout << 1+2*N << " 1 " << N << endl;
        cout << "1 " << 1+2*N << " " << N << endl;
        cout << 1+2*N << " " << 1+N << " " << N << endl;
        cout << 1+N << " " << 1+2*N << " " << N << endl;
        cout << 1+2*N << " " << 1+2*N << " " << N << endl;
        return 0;
    }
    if(!(N % 5)){
        N /= 5;
        cout << "8" << endl;
        cout << "1 1 " << 3*N << endl;
        cout << 1+3*N << " 1 " << 2*N << endl;
        cout << "1 " << 1+3*N << " " << 2*N << endl;
        cout << 1+3*N << " " << 1+3*N << " " << 2*N << endl;
        cout << 1+2*N << " " << 1+3*N << " " << N << endl;
        cout << 1+2*N << " " << 1+4*N << " " << N << endl;
        cout << 1+3*N << " " << 1+2*N << " " << N << endl;
        cout << 1+4*N << " " << 1+2*N << " " << N << endl;
        return 0;
    }
    N = N / 2 + 1;
    class SQ f(N);
    f.FindMAX();
    f.maxsquare.print(N);
    return a.exec();
}

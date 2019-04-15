#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <map>
using namespace std;



class Greedy{
public:
    void createGraph() {
        ifstream fin;
        fin.open("Fin.txt");
        fin>>from>>to;
        while (true) {
            char v1;
                        char v2;
                        double weight;
            if ((fin >> v1) && (fin >> v2) && (fin >> weight)) {
                Graph[v1].push_back(pair<char, double>(v2, weight));
                Graph[v2];
                continue;
            }
            break;
        }
        //cout<<"End\n";
    }
        string Greedy_alg(){
            stack.push_back(from);
            VisibleVertex[from] = true;
            double min=0;
            char MinVert = ' ';
            int i;
            for(i=0;i<VisibleVertex.size();i++) {
                        if(stack[stack.size()-1]==to) break;
                        min = 0;
                        MinVert = from;
                        for(iter_Vector=Graph[from].begin();iter_Vector<Graph[from].end();iter_Vector++){
                            if(!VisibleVertex[iter_Vector->first]){
                                if(min==0){
                                    VisibleVertex[iter_Vector->first] = true;
                                    min = iter_Vector->second;
                                    MinVert = iter_Vector->first;
                                }else if(iter_Vector->second<min){
                                    VisibleVertex[iter_Vector->first] = true;
                                    min = iter_Vector->second;
                                    MinVert = iter_Vector->first;
                                }
                            }
                        }
                        if(from==MinVert){
                            stack.pop_back();
                            from=stack[stack.size()-1];
                        }else{
                            stack.push_back(MinVert);
                            from = MinVert;
                        }
            }
            string way = "";
            for(int i=0;i<stack.size();i++)
                        way=way+stack[i];
            return way;
        }
    map<char, bool> VisibleVertex;
    vector<char> stack;
    char from, to;
    vector<pair<char,double>>::iterator iter_Vector;
    map<char,vector<pair<char,double>>>::iterator iter_Graph;
    map<char,vector<pair<char,double>>> Graph;
    };


    int main()
    {
        Greedy Graph;
        Graph.createGraph();
        cout<<Graph.Greedy_alg()<<endl;
        return 0;
    }

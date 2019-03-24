#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <map>
using namespace std;
class A_Star{
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
            map<char,vector<pair<char,double>>>::iterator iter_Graph;
            for( iter_Graph=Graph.begin();iter_Graph!=Graph.end();iter_Graph++){
                                    VisibleVertex[iter_Graph->first] = false;}
        }
        string A_Star_Alg(){
            distance[from];
            VisibleVertex[from] = true;
            way[from] += from;
            double min=0;
            char MinVert;
            for(int i=0;i<VisibleVertex.size();i++) {
                        if(from==to) break;
                        min = 0;
                        for(iter_Vector=Graph[from].begin();iter_Vector!=Graph[from].end();iter_Vector++){
                            if(!VisibleVertex[iter_Vector->first]){
                            if(distance[iter_Vector->first]==0){
                                distance[iter_Vector->first] = distance[from]+iter_Vector->second;
                                way[iter_Vector->first] = "";
                                way[iter_Vector->first] = way[from] + iter_Vector->first;
                            }else if(distance[iter_Vector->first]>distance[from]+iter_Vector->second){
                                                        distance[iter_Vector->first] = distance[from]+iter_Vector->second;
                                                        way[iter_Vector->first] = "";
                                                        way[iter_Vector->first] = way[from] + iter_Vector->first;}
                            }
                        }
                        for(distanceToVertex=distance.begin();distanceToVertex!=distance.end();distanceToVertex++){
                            if(!VisibleVertex[distanceToVertex->first]){
                                if(min==0){
                                    min = distanceToVertex->second+abs(to-distanceToVertex->first);
                                    MinVert = distanceToVertex->first;
                                }else if((distanceToVertex->second+abs(to-distanceToVertex->first))<min){
                                   min = distanceToVertex->second+abs(to-distanceToVertex->first);
                                    MinVert = distanceToVertex->first;
                                }
                            }
                        }
                        distance.erase(distance.find(from));
                        from = MinVert;
                        VisibleVertex[from] = true;
            }
            return way[from];
        }
    map<char,string> way;
    map<char,double> distance;
    map<char, bool> VisibleVertex;
    char from, to;
    map<char,double>::iterator distanceToVertex;
    vector<pair<char,double>>::iterator iter_Vector;
    map<char,vector<pair<char,double>>> Graph;
    };

    int main()
    {
        A_Star Graph;
        Graph.createGraph();
        cout<<Graph.A_Star_Alg()<<endl;
        return 0;
    }

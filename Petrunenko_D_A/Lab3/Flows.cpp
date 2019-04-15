#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;
class Flow{
public:
    void createGraph() {
        maxFlow = 0;
            ifstream fin;
            fin.open("Fin.txt");
            int bandwidth=0;
            char v1;
            char v2;
            fin>>size>>source>>stock;
            for(int i=0;i<size;i++){
                fin>>v1>>v2>>bandwidth;
                Graph[v1][v2] = bandwidth;
                Fact_Graph[v1][v2] = bandwidth;
            }
           }
           void max_Flow(){
               int sum;
            while((sum =Flow_Alg())!=0){ maxFlow += sum;}
                cout<<maxFlow<<endl;
                char Ccurrent;
                        for(G_Iter=Fact_Graph.begin();G_Iter!=Fact_Graph.end();G_Iter++){
                            Ccurrent = G_Iter->first;
                            for(Iter=Fact_Graph[Ccurrent].begin();Iter!=Fact_Graph[Ccurrent].end();++Iter){
                                if(Iter->second-Graph[Ccurrent][Iter->first]<0) Iter->second = 0;
                                else Iter->second = Iter->second-Graph[Ccurrent][Iter->first];
                                   cout<<Ccurrent<<" "<<Iter->first<<" "<<Iter->second<<endl;
                            }
                        }
           }
        int Flow_Alg(){
            vector<char> Vis_Ver;
            vector<pair<char, int>> label;
            Vis_Ver.push_back(source);
            char current = source;
            int i;
        for(i=0;i<size;i++){
            if(current==stock) break;
                        int max = 0;
                        char maxVert;
                for(Iter=Graph[current].begin();Iter!=Graph[current].end();++Iter){
                    if(!(std::find(Vis_Ver.begin(),Vis_Ver.end(),Iter->first)!=Vis_Ver.end())&&Iter->second>0){
                        if(max==0){
                            label.push_back(pair<char, int>(current, Iter->second));
                            maxVert = Iter->first;
                            max = Iter->second;
                        }else if(Iter->second>max){
                            label.pop_back();
                            label.push_back(pair<char, int>(current, Iter->second));
                            maxVert = Iter->first;
                            max = Iter->second;
                        }
                    }
                }
                if(max==0){
                    if(label.size()==0)
                        break;
                current = label.at(label.size()-1).first;
                label.pop_back();
                i--;
                }else{Vis_Ver.push_back(maxVert); current = maxVert;}
        }
        if(current==source) return 0;
        int min = label.at(0).second;
        for(int i=1;i<label.size();i++)
            if(label.at(i).second<min) min = label.at(i).second;
        for(int i=label.size()-1;i>=0;i--){
             Graph[label.at(i).first][current] = label.at(i).second - min;
             Graph[current][label.at(i).first] = Graph[current][label.at(i).first] + min;
             current = label.at(i).first;}
        return min;
        }
    int maxFlow, size;
    char source, stock;
    map<char, int>::iterator Iter;
    map<char,map<char,int>>::iterator G_Iter;
    map<char,map<char, int>> Graph;
    map<char,map<char, int>> Fact_Graph;
    };

    int main()
    {
        Flow Graph;
        Graph.createGraph();
        Graph.max_Flow();
        return 0;
    }
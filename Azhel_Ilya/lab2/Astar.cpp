#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

class Graph {
public:
    Graph() {};
    void createGraph() {
        while (true) {
            char v1;
            char v2;
            double weight;
            if ((cin >> v1) && (cin >> v2) && (cin >> weight)) {
                graph[v1].push_back(pair<char, double>(v2, weight));
                graph[v2];
                continue;
            }
            break;
        }
    }

    string search(char fromVertex, char toVertex) {
        map<char,double> distance;
        map<char,bool> visitedVertexs;
        map<char,char> way;
        for(it_for_graph=graph.begin();it_for_graph!=graph.end();it_for_graph++)
            visitedVertexs[it_for_graph->first]=false;
        distance[fromVertex]=0;
        for(int i=0;i<graph.size();i++){
            map<char,double>::iterator current=min_element(distance.begin(),distance.end(),[toVertex](pair<char,double> v1,pair<char,double> v2){
                return (v1.second+abs(v1.first-toVertex))<(v2.second+abs(v2.first-toVertex));
            });
            if(current->first==toVertex)
                break;
            visitedVertexs[current->first]=true;
            for(pair<char,double> neighbor:graph[current->first]){
                if(!visitedVertexs[neighbor.first]){
                    map<char,double>::iterator distanceToVertex=distance.find(neighbor.first);
                    if(distanceToVertex==distance.end()) {
                        distance[neighbor.first]= current->second + neighbor.second;
                        way[neighbor.first]=current->first;
                    }
                    else if(current->second+neighbor.second<distanceToVertex->second) {
                        way[neighbor.first]=current->first;
                        distanceToVertex->second = current->second + neighbor.second;
                    }
                }
            }
            distance.erase(current);
        }
        string path="";
        for(char vertex=toVertex;path[0]!=fromVertex;vertex=way.find(vertex)->second)
            path=vertex+path;
        return path;
    }

private:
    map<char, vector<pair<char, double>>> graph;
    map<char,vector<pair<char,double>>>::iterator it_for_graph;
};

int main() {
    char A;//из точки А
    char B;// в точку B
    cin>>A>>B;
    Graph graph;
    graph.createGraph();
    cout<<graph.search(A,B);
    return 0;
}

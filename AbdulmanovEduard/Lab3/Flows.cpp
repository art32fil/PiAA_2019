#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

typedef char Vertex;

class Graph {
public:
    Graph() {};
    void createGraph(int count) {
        Vertex from;
        Vertex to;
        int bandwidth;
        cin>>from>>to>>bandwidth;
        for(int i=0;i<count;i++,cin>>from>>to>>bandwidth)
            graph[from][to] = bandwidth;
    }

    void maxFlow(Vertex source,Vertex stock){
        map<Vertex,map<Vertex,int>> network=graph;
        map<Vertex,pair<Vertex,int>> way=BFS(network,source,stock);
        while(way.size()!=0){
            reconstructionNetwork(network,way,source,stock);
            way=BFS(network,source,stock);
        }
        int max_flow=0;
        for_each(graph[source].begin(),graph[source].end(),[&max_flow,&network,source](pair<Vertex,int> neighbor){
            max_flow+=neighbor.second-network[source][neighbor.first];
        });
        cout<<max_flow<<endl;
        for_each(graph.begin(),graph.end(),[&network](pair<Vertex,map<Vertex,int>> neighbors){
            for_each(neighbors.second.begin(),neighbors.second.end(),[&network,neighbors](pair<Vertex,int> ver){
                cout<<neighbors.first<<" "<<ver.first<<" ";
                if(ver.second-network[neighbors.first][ver.first]>=0)
                   cout<<ver.second-network[neighbors.first][ver.first]<<endl;
                else
                   cout<<0<<endl;
            });
        });
    }

    int get_min_flow_on_way(map<Vertex,pair<Vertex,int>> way,Vertex source,Vertex stock){
        int min_flow=way[stock].second;
        for(Vertex ver=stock;ver!=source;ver=way[ver].first) {
            if (min_flow > way[ver].second)
                min_flow = way[ver].second;
        }
        return min_flow;
    }

    void reconstructionNetwork(map<Vertex,map<Vertex,int>> &network,map<Vertex,pair<Vertex,int>> way,Vertex source,Vertex stock){
        int min_flow=get_min_flow_on_way(way,source,stock);
        for(Vertex ver=stock;ver!=source;ver=way[ver].first){
            if(way[ver].second-min_flow==0)
                network[way[ver].first].erase(ver);
            else
                network[way[ver].first][ver] -= min_flow;
            network[ver][way[ver].first] += min_flow;
        }

    }

    map<Vertex,pair<Vertex,int>> BFS(map<Vertex,map<Vertex,int>> g,Vertex source,Vertex stock){
        set<Vertex> visibleVertex;//множество посещенных вершин
        queue<Vertex> queueVertex;//очередь
        map<Vertex,pair<Vertex,int>> way;//путь
        map<Vertex,map<Vertex,int>>::iterator current;//Текущий обрабатывваемый элемент
        visibleVertex.insert(source);
        queueVertex.push(source);
        while(queueVertex.front()!=stock&&queueVertex.size()!=0){
            current=g.find(queueVertex.front());
            queueVertex.pop();
            for_each(current->second.begin(),current->second.end(),[&queueVertex,&visibleVertex,&way,current](pair<Vertex,int> ver){
                if(visibleVertex.find(ver.first)==visibleVertex.end()){
                    queueVertex.push(ver.first);
                    visibleVertex.insert(ver.first);
                    way[ver.first]=pair<Vertex,double>(current->first,ver.second);
                }
            });
        }
        if(visibleVertex.find(stock)==visibleVertex.end())
            return map<Vertex,pair<Vertex,int>>();
        return way;
    }

private:
    map<Vertex,map<Vertex,int>> graph;
};

int main() {
    int count;
    Vertex source;
    Vertex stock;
    cin>>count;
    cin>>source;
    cin>>stock;
    Graph graph;
    graph.createGraph(count);
    graph.maxFlow(source,stock);
    return 0;
}
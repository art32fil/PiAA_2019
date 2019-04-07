#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node{
    char tail;
    float price;
};

struct Graph{
    char head;
    vector <struct Node> node;
};

bool Compare(struct Node first, struct Node second){
    //return first.price >= second.price;
    if(first.tail == second.tail) return first.tail > second.tail;
    return first.tail < second.tail;
}

void Fun(vector <struct Graph>& graph, char first, char final, vector <char>& bestway, vector <char>& way, float& bestwaydata, float& waydata){
    //if(!bestway.empty())
    //        return;
    for(auto it = graph.begin(); it != graph.end(); it++){
        if(it->head == first){
            vector <struct Node> node(it->node);
            while(!node.empty()){
                auto pointer = node.end();
                pointer--;
                if(bestwaydata >= waydata + pointer->price){
                    waydata += pointer->price;
                    way.push_back(pointer->tail);
                    if(pointer->tail == final){
                        if((bestwaydata == waydata && way.size() < bestway.size()) || bestwaydata > waydata){
                            bestway = way;
                            bestwaydata = waydata;
                        }
                    }
                    else
                        Fun(graph, pointer->tail, final, bestway, way, bestwaydata, waydata);
                    waydata -= pointer->price;
                    node.pop_back();
                    way.pop_back();
                }
                else
                    node.pop_back();
            }
        }
    }
}

int main()
{
    char first, final;
    cin >> first >> final;
    vector <struct Graph> graph;
    struct Node node;
    struct Graph newnode;
    char head;
    bool flag;
    //int counter = 1;
    while(/*counter-- && */cin >> head >> node.tail >> node.price){
        flag = false;
        for(auto it = graph.begin(); it != graph.end(); it++)
            if(head == it->head){
                (it->node).push_back(node);
                flag = true;
                break;
            }
        if(!flag){
            newnode.head = head;
            newnode.node.push_back(node);
            graph.push_back(newnode);
            newnode.node.pop_back();
        }
    }
    for(auto it = graph.begin(); it != graph.end(); it++)
        sort((it->node).begin(), (it->node).end(), Compare);
    vector <char> way;
    way.push_back(first);
    vector <char> bestway;
    float waydata = 0, bestwaydata = 9999;
    Fun(graph, first, final, bestway, way, bestwaydata, waydata);
    for(auto it = bestway.begin(); it != bestway.end(); it++)
        cout << *it;
    return 0;
}

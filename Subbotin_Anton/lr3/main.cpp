#include <vector>
#include <iostream>
#include <algorithm>

typedef int type;
using namespace std;

typedef struct edge{
    char head, tail;
    type* out, *ent;
    bool checked;
} edge;

bool Sort(edge first, edge second){
    if(first.head == second.head)
        return first.tail < second.tail;
    return first.head < second.head;
}

bool Compare(edge first, edge second)
{
    if(first.head == second.head)
        return *(first.out) > *(second.out);
    return first.head < second.head;
}

class Ford{
public:
    vector<edge> graph, easy;
    char start, finish, now;
    type count, help, min, sum;
    edge* elem;
    vector <type> prices;
    vector <edge*> way;
    bool trouble;

    Ford(){
        type price;
        cin >> count >> start >> finish;
        for(type i(0); i < count; i++){
            edge node;
            cin >> node.head >> node.tail >> price;
            node.out = new type(price);
            node.ent = new type(0);
            node.checked = false;
            graph.push_back(node);
        }
        easy = graph;
        help = count;
        for(type i(0); i < count; i++){
            bool rewerse = true;
            for(type j(0); j < count; j++)
                if(i != j && easy.at(i).head == easy.at(j).tail && easy.at(i).tail == easy.at(j).head)
                      rewerse = false;
            if(rewerse){
                edge node;
                node.head = easy.at(i).tail;
                node.tail = easy.at(i).head;
                node.out = easy.at(i).ent;
                node.ent = easy.at(i).out;
                node.checked = easy.at(i).checked;
                easy.push_back(node);
                help++;
            }
        }
        if(count > 0){
            elem = nullptr;
            sort(easy.begin(), easy.end(), Compare);
            trouble = true;
            for(type i(0); i < count; i++)
                if(graph.at(i).head == start)
                    trouble = false;
            if(!trouble)
                elem = Headseeker(start);
        }
        now = start;
        sum = 0;
    }

    void Process(){
        if(*(elem->out) && !elem->checked){
            elem->checked = true;
            for(type i(0); i < help; i++)
                if(easy.at(i).tail == now)
                    easy.at(i).checked = true;
            prices.push_back(*(elem->out));
            way.push_back(elem);
            if(elem->tail != finish)
                now = elem->tail;
            else{
                min = 9999;
                while(!prices.empty()){
                    if(min > prices.back())
                        min = prices.back();
                    prices.pop_back();
                }
                sum += min;
                Sub();
                Checkfailer();
                sort(easy.begin(), easy.end(), Compare);
                now = start;
            }
            elem = Headseeker(now);
            Process();
        }
        else{
            now = elem->head;
            elem = &elem[1];
            if(elem->head != now){
                if(now == start)
                    return;
                elem = Headseeker(way.back()->head);
                way.pop_back();
                prices.pop_back();
            }
            Process();
        }
    }

    struct edge* Headseeker(char head)
    {
        int i = 0;
        while(head != easy.at(i++).head);
        return &easy.at(i-1);
    }

    void Checkfailer()
    {
        for(type i(0); i < help; i++)
            easy.at(i).checked = false;
    }

    void Sub()
    {
        struct edge* node;
        while(!way.empty()){
            node = way.back();
            *(node->out) -= min;
            *(node->ent) += min;
            way.pop_back();
        }
    }

    void Out()
    {
        cout << sum << endl;
        if(count > 0)
            sort(graph.begin(), graph.end(), Sort);
        for(type i(0); i < count; i++)
            for(type j(i+1); j < count; j++)
                if(graph.at(i).head == graph.at(j).tail && graph.at(i).tail == graph.at(j).head){
                    if(*(graph.at(i).ent) > *(graph.at(j).ent)){
                        *(graph.at(i).ent) -= *(graph.at(j).ent);
                        *(graph.at(j).ent) = 0;
                    }
                    else{
                        *(graph.at(j).ent) -= *(graph.at(i).ent);
                        *(graph.at(i).ent) = 0;
                    }
                }
        for(type i(0); i < count; i++)
            cout << graph.at(i).head << " " << graph.at(i).tail << " " << *(graph.at(i).ent) << endl;
    }
};

int main()
{
    Ford dot;
    if(dot.count > 0 && dot.elem)
        dot.Process();
    dot.Out();
    return 0;
}

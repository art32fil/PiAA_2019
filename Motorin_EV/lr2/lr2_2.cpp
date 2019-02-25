#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct WAY{
    char from;
    char to;
    double cost;
};

bool cmp (WAY* a, WAY* b) {
    int v =  (int)(a->to) - (int)(b->to);
    if (v == 0) return a->cost > b->cost;
    else return v < 0;
}

bool isNewWayBest(vector<WAY*> bestWay, vector<WAY*> newWay) {
    if (!bestWay.size()) return true;
    
    double bestCost = 0.0;
    double newCost = 0.0;
    
    for (int i = 0; i < bestWay.size(); i++)
        bestCost += bestWay[i]->cost;
    
    for (int i = 0; i < newWay.size(); i++)
        newCost += newWay[i]->cost;
    
    if (newCost != bestCost)
        return newCost < bestCost;
    
    for (int i = 0; i < newWay.size(), i < bestWay.size(); i++) {
        int a1 = (int)(newWay[i]->to) - (int)(newWay[i]->from);
        int a2 = (int)(bestWay[i]->to) - (int)(bestWay[i]->from);
        if (a1 > a2) return true;
    }
    
    return newWay.size() < bestWay.size();
}

inline void findWay(vector<WAY*> ways, vector<WAY*> report, WAY* task, vector<WAY*>* bestWay) {
    std::sort(ways.begin(), ways.end(), cmp);
    if (!report.size()) {
        for (int i = 0; i < ways.size(); i++) {
            if (ways[i]->from == task->from) {
                vector<WAY*> rep;
                rep.push_back(ways[i]);
                findWay(ways, rep, task, bestWay);
            }
        }
        return;
    }
    
    if (report[report.size() - 1]->to == task->to) {
        if (isNewWayBest(*bestWay, report))
            *bestWay = report;
        return;
    }
    
    for (int i = 0; i < ways.size(); i++)
        if (report[report.size() - 1]->to == ways[i]->from) {
            vector<WAY*> ptr = report;
            ptr.push_back(ways[i]);
            findWay(ways, ptr, task, bestWay);
        }
}

int main(int argc, const char * argv[]) {
    vector<WAY*> ways;
    WAY* task = new WAY;
    vector<WAY*> report;
    vector<WAY*> best;
    
    scanf("%c %c\n", &(task->from), &(task->to));
    
    while (true) {
        WAY* ptr = new WAY;
        if ((cin >> ptr->from) && (cin >> ptr->to) && (cin >> ptr->cost))
            ways.push_back(ptr);
        else break;
    }
    
    findWay(ways, report, task, &best);
    
    cout << best[0]->from;
    for (int i = 0; i < best.size(); i++) {
        cout << best[i]->to;
    }
    return 0;
}

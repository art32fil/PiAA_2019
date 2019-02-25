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
    return a->cost < b->cost;
}

inline void search(vector<WAY*> ways, vector<WAY*> stack, WAY* task, char current, vector<char>* res) {
    if (task->to == current) {
        return;
    }
    
    vector<WAY*> buf;
    for (int i = 0; i < ways.size(); i++) {
        if (ways[i]->from == current) {
            buf.push_back(ways[i]);
        }
    }
    
    if (buf.size() == 0) {
        char next = stack[stack.size() - 1]->to;
        stack.pop_back();
        res->pop_back();
        res->push_back(next);
        search(ways, stack, task, next, res);
        return;
    }
    
    std::sort(buf.begin(), buf.end(), cmp);
    char next = buf[0]->to;
    
    for (unsigned long i = (buf.size() - 1); i > 0; i--) {
        stack.push_back(buf[i]);
    }
    res->push_back(next);
    search(ways, stack, task, next, res);
}

int main(int argc, const char * argv[]) {
    vector<WAY*> ways;
    vector<WAY*> history;
    WAY* task = new WAY;
    vector<char> res;
    
    scanf("%c %c\n", &(task->from), &(task->to));
    res.push_back(task->from);
    
    while (true) {
        WAY* ptr = new WAY;
        if ((cin >> ptr->from) && (cin >> ptr->to) && (cin >> ptr->cost))
            ways.push_back(ptr);
        else break;
    }
    
    search(ways, history, task, task->from, &res);
    
    for (int i = 0; i < res.size(); i++)
        cout << res[i];
    return 0;
}

#include <algorithm>
#include <vector>
#include <iostream>
#define noPath -1
#define size_MAX 150
using namespace std;

class Graph
{
public:
    Graph():istock(0),
             stock(0),
             value(size_MAX, vector<int>(size_MAX, 0)),
             prevs(size_MAX, 0),
             visited(size_MAX, false),
             flow(size_MAX, vector<int>(size_MAX, 0)){}

    vector<vector<int>> value;
    vector<vector<int>> flow;
    vector<int> prevs;
    vector<bool> visited;
    int istock, stock;

    void initPrevs() {
        for (int i = 0; i<size_MAX; ++i)
            prevs[i] = noPath;
    }

    void isVertex(int v) {
        visited[v] = true;
        for (int i = 0; i<size_MAX; ++i)
            if (!visited[i] && ((value[v][i] - flow[v][i] > 0 && value[v][i] != 0) || (flow[v][i] < 0 && value[i][v] != 0))) {
                prevs[i] = v;
                isVertex(i);
            }
    }

    bool isPath(int v) {
        isVertex(v);
        for (int i = 0; i<size_MAX; ++i)
            visited[i] = false;
        return (prevs[stock] != noPath);
    }

    int ford_fald() {
        int maxFlow = 0;
        while (isPath(istock)) {
            int tmp = 9999999;
            for (int v = stock; 0 <= prevs[v]; v = prevs[v])
                tmp = min(tmp, value[prevs[v]][v] - flow[prevs[v]][v]);
            for (int v = stock; 0 <= prevs[v]; v = prevs[v]) {
                flow[prevs[v]][v] += tmp;
                flow[v][prevs[v]] -= tmp;
            }
            maxFlow += tmp;
            initPrevs();
        }
        return maxFlow;
    }


};

int main() {
    Graph h;

    h.initPrevs();
    int numb_edges = 0, cost = 0;
    char  istok, stok;
    cin >> numb_edges;
    cin >> istok >> stok;
    h.istock = istok - '0';
    h.stock = stok - '0';
int i,j;
    for (int k = 0; k < numb_edges; ++k) {
        cin >> istok >> stok >> cost;
        i = istok - '0';
        j = stok - '0';
        h.value[i][j] = cost;
    }
    cout << h.ford_fald() << char(10);
    for (i = 0; i < size_MAX; ++i)
        for (j = 0; j < size_MAX; ++j) {
            if ( h.flow[i][j] < 0)
                h.flow[i][j] = 0;
            if (h.value[i][j] > 0)
                cout << (char)(i + '0') << " " << (char)(j + '0') << " " << h.flow[i][j] << char(10);
        }
    return 0;
}
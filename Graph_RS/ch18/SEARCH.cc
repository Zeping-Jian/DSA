#ifndef SEARCH_CC_
#define SEARCH_CC_

#include <vector>
#include "Edge.cc"

using namespace std;

// Программа 18.2. Поиск на графе
template <class Graph>
class SEARCH {
protected:
    const Graph &G;
    int cnt;
    vector<int> ord;

    virtual void searchC(Edge) = 0;

    void search() {
        for (int v = 0; v < G.V(); v++) {
            if (ord[v] == -1) searchC(Edge(v, v));
        }
    }

public:
    explicit SEARCH(const Graph &G) : G(G), cnt(0), ord(G.V(), -1) {}

    int operator [] (int v) const { return ord[v]; }

    void printOrd(){
        // cout.width(2);
        for (int i = 0; i < G.V(); ++i) {
            // cout << i << " ";
            printf("%2d ",i);
        }
        cout << endl;
        // cout.width(2); // 输出endl 后自动恢复
        for (int i = 0; i < G.V(); ++i) {
            // cout << ord[i] << " ";
            printf("%2d ",ord[i]);
        }
        cout << endl;
    }
};

#endif

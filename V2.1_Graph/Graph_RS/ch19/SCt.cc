#ifndef SCT_CC_
#define SCT_CC_

#include <stack>
#include <vector>
using namespace std;

//Program 19.11 SCC  Tanjan 实现
template <class Graph>
class SCt {
    const Graph &G;
    stack<int> Stk;
    int cnt, scnt; // scnt联通分量个数
    vector<int> pre, low, id;

    void scR(int w) {
        int min = pre[w] = low[w] = cnt++;
        Stk.push(w);
        
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (pre[t] == -1) scR(t);
            if (low[t] < min) min = low[t];
        }

        if (min < low[w]) {
            low[w] = min;
            return;
        }

        int t;
        do {
            t = Stk.top(); Stk.pop();
            id[t] = scnt;
            low[t] = G.V();
        } while (t != w);
        scnt++;
    }

public:
    SCt(const Graph &G) : G(G), cnt(0), scnt(0), pre(G.V(), -1), low(G.V(), -1), id(G.V()) {
        for (int v = 0; v < G.V(); v++) {
            if (pre[v] == -1) scR(v);
        }
    }

    int count() const { return scnt; }
    bool stronglyreachable(int v, int w) const { return id[v] == id[w]; }
    int ID(int v) const { return id[v]; }
};

#endif

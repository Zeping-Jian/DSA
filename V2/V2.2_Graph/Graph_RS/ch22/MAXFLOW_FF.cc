//
// Created by 菅泽平 on 2025/6/2.
//

#ifndef MAXFLOW_FF_CC__
#define MAXFLOW_FF_CC__

#include <vector>
// #include <queue>
#include "PQI.cc"

using namespace std;

// program22.3 Ford-Fulkerson算法，增广路径最大流算法
template<class Graph, class Edge>
class MAXFLOW_FF {
    const Graph &G;
    int s, t;
    vector<int> wt;
    vector<Edge *> st;

    int ST(int v) const { return st[v]->other(v); }

    void augment(int s, int t) {
        int d = st[t]->capRto(t);
        for (int v = ST(t); v != s; v = ST(v))
            if (st[v]->capRto(v) < d)
                d = st[v]->capRto(v);
        st[t]->addflowRto(t, d);
        for (int v = ST(t); v != s; v = ST(v))
            st[v]->addflowRto(v, d);
    }

    bool pfs();

public:
    MAXFLOW_FF(const Graph &G, int s, int t) :
            G(G), s(s), t(t), st(G.V()), wt(G.V()) {
        while (pfs()) augment(s, t);
    }
};

#define M 10

//
template<class Graph, class Edge>
bool MAXFLOW_FF<Graph, Edge>::pfs() {
    PQi<int> pQ(G.V(), wt);
    // priority_queue<int> pQ(G.V(), wt);
    for (int v = 0; v < G.V(); v++) {
        wt[v] = 0;
        st[v] = 0;
        pQ.insert(v); // 等效如下
        // pQ.push(v);
    }
    wt[s] = -M;
    pQ.lower(s); // 这个是什么能力？  //如何等效？
    while (!pQ.empty()) {
        int v = pQ.getmin();
        wt[v] = -M;
        if (v == t || (v != s && st[v] == 0)) break;
        typename Graph::adjIterator A(G, v);
        for (Edge *e = A.beg(); !A.end(); e = A.nxt()) {
            int w = e->other(v);
            int cap = e->capRto(w);
            int P = cap < -wt[v] ? cap : -wt[v];
            if (cap > 0 && -P < wt[w]) {
                wt[w] = -P;
                pQ.lower(w);
                st[w] = e;
            }
        }
    }
    return st[t] != 0;
}


#endif
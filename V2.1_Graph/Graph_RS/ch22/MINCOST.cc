//
// Created by 菅泽平 on 2025/6/2.
//

#ifndef MINCOST_CC__
#define MINCOST_CC__

#include "DenseGRAPH.cc"
#include <vector>

using namespace std;

// 定义容量？
#define  C 10

// program 22.9 环消除算法
template<class Graph>
static int cost(Graph &G) {
    int x = 0;
    for (int v = 0; v < G.V(); v++) {
        typename Graph::adjIterator A(G, v);
        for (Edge *e = A.beg(); !A.end(); e = A.nxt())
            if (e->from(v) && e->costRto(e->w) < C)
                x += e->flow() * e->costRto(e->w);
    }
    return x;
}

template<class Graph, class Edge>
class MINCOST {
    const Graph &G;
    int s, t;
    vector<int> wt;
    vector<Edge *> st;

    int ST(int v) const;

    void augment(int, int);

    int negcyc(int);    //要求自己实现 ，根据Bellman-Ford

    int negcyc();

public:
    MINCOST(const Graph &G, int s, int t) : G(G),
                                            s(s), t(t), st(G.V()), wt(G.V()) {
        MAXFLOW<Graph, Edge>(G, s, t);
        for (int x = negcyc(); x != -1; x = negcyc()) { augment(x, x); }
    }
};

#endif
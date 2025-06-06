//
// Created by 菅泽平 on 2025/6/2.
//
#ifndef MAXFLOW_CC__
#define MAXFLOW_CC__

#include <vector>
#include <queue>
#include "GQ.cc"
#include "PQI.cc"

using namespace std;

#define M 10 // 假定的最大值

// Program 22.5 Preflow-push max-flow implementation
template<class Graph, class Edge>
class MAXFLOW {
    const Graph &G;
    int s, t;
    vector<int> h; // 高度函数
    vector<int> wt; // 超额量

    //要求自己实现，
    void initheights(); //需要先反转图，然后通过BFS方法实现

public:
    MAXFLOW(const Graph &G, int s, int t) : G(G),
                                            s(s), t(t), h(G.V()), wt(G.V(), 0) {
        initheights();
        GQ<int> gQ(G.V());
        gQ.put(s);
        wt[t] = -(wt[s] = M * G.V());
        while (!gQ.empty()) {
            int v = gQ.get();
            typename Graph::adjIterator A(G, v);
            for (Edge *e = A.beg(); !A.end(); e = A.nxt()) {
                int w = e->other(v);
                int cap = e->capRto(w);
                int P = cap < wt[v] ? cap : wt[v]; // 这里的P代表什么
                if (P > 0 && v == s || h[v] == h[w] + 1) {
                    e->addflowRto(w, P);
                    wt[v] -= P;
                    wt[w] += P;
                    if ((w != s) && (w != t)) gQ.put(w);
                }
            }
            if (v != s && v != t && wt[v] > 0) {
                h[v]++;
                gQ.put(v);
            }
        }
    }
};


#endif
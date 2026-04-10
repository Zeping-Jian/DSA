#ifndef TCSC_CC_
#define TCSC_CC_

#include "DenseGRAPH.cc"
#include "dagTC.cc"
#include "SCg.cc"

// Program 19.13 基于强分量的传递闭包 Strong-Connect-Component
// Solve Transitive-closure by Strong-Connect-Component 强连通分量
// BaseOn Property 19.2 Kernal-DAG
template <class Graph>
class TCsc {
    const Graph &G;
    DenseGRAPH *G_K;    // kernalDAG
    dagTC<DenseGRAPH, Graph> *Ktc;
    SCg<Graph> *Gsc;    // Strong-CC计算类

public:
    TCsc(const Graph &G) : G(G) {
        Gsc = new SCg<Graph>(G);
        G_K = new DenseGRAPH(Gsc->count, true);
        for (int v = 0; v < G.V(); v++) {
            typename Graph::adjIterator A(G, v);
            for (int t = A.beg(); !A.end(); t = A.nxt()) {
                G_K->insert(Edge(Gsc->ID(v), Gsc->ID(t)));
            }
        }
        // 新建TC类，计算新的传递闭包，以KernalDAG进行建立
        Ktc = new dagTC<DenseGRAPH, Graph>(*G_K);
    }

    ~TCsc() {
        delete G_K;
        delete Ktc;
        delete Gsc;
    }

    bool reachable(int v, int w) const {
        return Ktc->reachable(Gsc->ID(v), Gsc->ID(w));
    }
};

#endif

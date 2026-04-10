#ifndef TC_DFS_CC_
#define TC_DFS_CC_

#include "Edge.cc"

// program 19.4 dfs实现 传递闭包 Transitive Closure
// 邻接矩阵表示
template<class Graph>
class tcDFS {
    Graph T;
    const Graph &G;

    void tcR(int v, int w) {
        T.insert(Edge(v, w));
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt())
            if (!T.edge(v, t)) tcR(v, t);
    }

public:
    tcDFS(const Graph &G) : G(G), T(G.V(), true) {
        for (int v = 0; v < G.V(); v++) tcR(v, v);
    }

    bool reachable(int v, int w) { return T.edge(v, w); }
};

#endif // TC_DFS_CC_
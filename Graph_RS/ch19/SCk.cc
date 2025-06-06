#ifndef SCK_CC_
#define SCK_CC_

#include <vector>
#include "clients.cc"
using namespace std;

// 19.10 Kosaraju 强分量计算法方法
template <class Graph>
class SCk {
    const Graph &G;
    int cnt;  // 访问次序记录器
    int scnt; // 联通分量记录器
    vector<int> postI, postR, id;

    void dfsR(const Graph &G, int w) {
        id[w] = scnt;
        typename Graph::adjIterator A(G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (id[t] == -1) dfsR(G, t);
        }
        postI[cnt++] = w;
    }

public:
    SCk(const Graph &G) : G(G), cnt(0), scnt(0), postI(G.V()), postR(G.V()), id(G.V(), -1) {
        Graph R(G.V(), true);
        reverse<Graph, Graph>(G, R);
        for (int v = 0; v < R.V(); v++) {
            if (id[v] == -1) dfsR(R, v);
        }

        postR = postI;
        cnt = scnt = 0;
        id.assign(G.V(), -1);

        for (int v = G.V() - 1; v >= 0; v--) {
            if (id[postR[v]] == -1) {
                dfsR(G, postR[v]);
                scnt++;
            }
        }
    }

    int count() const { return scnt; }
    bool stronglyreachable(int v, int w) const { return id[v] == id[w]; }
    int ID(int v) const { return id[v]; }
};

#endif // SCK_CC_

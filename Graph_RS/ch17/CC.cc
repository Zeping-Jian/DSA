#ifndef CC_CC_
#define CC_CC_

#include <vector>

using namespace std;

// Программа 17.5, 18.4. Интерфейс связности, Связность графа
template <class Graph>
class CC {
    const Graph &G;
    int ccnt;
    vector<int> id;

    void ccR(int w) {
        id[w] = ccnt;
        typename Graph::adjIterator A(G, w);
        cout << "ccR w=" << w << ", ccnt=" << ccnt <<endl;
        for (int v = A.beg(); !A.end(); v = A.nxt()) {
            cout << "ccR v=" << v << ", id[v]" << id[v] <<endl;
            if (id[v] == -1) ccR(v);
        }
    }

public:
    CC(const Graph &G) : G(G), ccnt(0), id(G.V(), -1) {
        for (int v = 0; v < G.V(); v++) {
            cout << "CC in v=" << v << ", id[v]=" << id[v] << endl;
            if (id[v] == -1) {
                ccR(v);
                cout << "CC in v=" << v << ", id[v]=" << id[v] << ",ccnt=" << ccnt << endl;
                ccnt++;
            }
        }
    }

    int count() const { return ccnt; }
    bool connect(int s, int t) { return id[s] == id[t]; }
};

#endif

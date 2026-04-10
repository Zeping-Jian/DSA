#ifndef EC_CC_
#define EC_CC_

#include "SEARCH.cc"

// Программа 18.7. Ребёрная связность
// Edge Connected 边连通性 Program 18.7 Edge connectivity
template <class Graph>
class EC : public SEARCH<Graph> {
    int bcnt;
    vector<int> low;


    void searchC(Edge e) {
        int w = e.w;
        this->ord[w] = this->cnt++;
        low[w] = this->ord[w];

        typename Graph::adjIterator A(this->G, w);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (this->ord[t] == -1) {
                searchC(Edge(w, t));
                if (low[w] > low[t]){
                    // printf("1 w-t low[%d]=%d, low[%d]=%d\n", w, low[w], t, low[t]);
                    low[w] = low[t];
                }
                if (low[t] == this->ord[t]) bcnt++; // 产生桥
            } else if (t != e.v) {
                if (low[w] > this->ord[t]) {
                    // cout << "low[w]:" << low[w] << ",ord[t]:" << this->ord[t] << ",<< endl;
                    // printf("2 w-t low[%d]=%d, ord[%d]=%d\n", w, low[w], t, this->ord[t]);
                    low[w] = this->ord[t];
                }
            }
        }
    }


public:
    EC(const Graph &G) : SEARCH<Graph>(G), bcnt(0), low(G.V(), -1) {
        this->search();
    }

    int count() const {
        // return bcnt + 1; // 这里分析+1 会多出一个bridge来
        return bcnt;
    }

    void printLow(){
        // cout.width(2);
        for (int i = 0; i < this->G.V(); ++i) {
            printf("%2d ",low[i]);
        }
        cout << endl;
    }
};

#endif

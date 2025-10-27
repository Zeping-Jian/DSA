#ifndef BC_CC_
#define BC_CC_

#include "SEARCH.cc"

#include <unordered_set>

// Программа 18.7. Ребёрная связность
// Program 18.7 Edge connectivity, Edge Connected 边连通性
template <class Graph>
class BC : public SEARCH<Graph> {
    int bcnt;
    vector<int> low;

    unordered_set<int> bc;
    int root;


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
                if (low[t] >= this->ord[w] && w != root) {
                    // w是关节点，检查条件是怎么定出来的？
                    bc.insert(w);
                    cout << "Processing edge: " << e.v << "-" << e.w << ",t:" << t
                         << " ord[" << t << "]=" << this->ord[t]
                         << " low[" << w << "]=" << low[w] << endl;
                }
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
    BC(const Graph &G, int root) : SEARCH<Graph>(G), root(root), bcnt(0), low(G.V(), -1) {
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
        std::cout << std::endl;
    }

    void printBC(){
        // cout.width(2);
        for (auto b: bc) {
            printf("%2d ",b);
        }
        std::cout << std::endl;
    }
};

#endif

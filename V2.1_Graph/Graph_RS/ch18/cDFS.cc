#ifndef CDFS_CC_
#define CDFS_CC_

#include <vector>

using namespace std;

// Программа 18.1. Поиск в глубину связной компоненты
template<class Graph>
class cDFS {
    const Graph &G;
    int cnt;
    vector<int> ord;    // 节点访问顺序，同时标记是否被访问过

    void searchC(int v) {
        ord[v] = cnt++;
        // cout << "cDFS=" << ord[v] << " " << v << ", cnt=" <<  cnt << endl;
        typename Graph::adjIterator A(G, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (ord[t] == -1) searchC(t);
        }
    }

public:
    /**
     * cDFS遍历
     * @param G 图
     * @param v search起点
     */
    cDFS(const Graph &G, int v = 0) : G(G), cnt(0), ord(G.V(), -1) {
        // ord(G.V(), -1) // 代表的含义是初始化n个顶点，初始值是-1
        searchC(v);
    }

    int count() const { return cnt; }

    int operator[](int v) const { return ord[v]; }

    void printVistOrd() {
        for (int i = 0; i < G.V(); i++) {
            cout << ord[i] << " ";
        }
        cout << endl;
    }
};


#endif

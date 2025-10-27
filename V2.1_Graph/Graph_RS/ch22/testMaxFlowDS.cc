
#include <iostream>
// #include "MAXFLOW.cc"
// #include "DenseGRAPH.cc"
// #include "DenseGRAPH.cc"

using namespace std;

// typedef WeightedEdge Edge;
// typedef DenseGRAPH Graph;

// 简单的有向图实现
class Graph {
    int VN;
    bool directed;
    vector<vector<int>> adj;
public:
    vector<vector<int>> capacity;

public:
    Graph(int VN, bool directed) : VN(VN), directed(directed),
                                  adj(VN), capacity(VN, vector<int>(VN, 0)) {}

    int V() const { return VN; }
    int getV() const {return  VN;}

    void addEdge(int v, int w, int cap) {
        adj[v].push_back(w);
        capacity[v][w] = cap;
        if (!directed) {
            adj[w].push_back(v);
            capacity[w][v] = cap;
        }
    }

public:
    // 添加这个非 const 方法
    vector<vector<int>>& getCapacity() { return capacity; }
    const vector<vector<int>>& getCapacity() const { return capacity; } // const 版本

    class adjIterator {
        const Graph &G;
        int v;
        size_t i;
    public:
        adjIterator(const Graph &G, int v) : G(G), v(v), i(0) {}
        int beg() { i = 0; return (i < G.adj[v].size()) ? G.adj[v][i] : -1; }
        int nxt() { i++; return (i < G.adj[v].size()) ? G.adj[v][i] : -1; }
        bool end() { return i >= G.adj[v].size(); }
    };

};

// 边类实现
class Edge {
    int v, w, flow, cap;
public:
    Edge(int v, int w, int cap) : v(v), w(w), flow(0), cap(cap) {}
    int from() const { return v; }
    int to() const { return w; }
    int other(int vertex) const { return vertex == v ? w : v; }
    int capRto(int vertex) const { return vertex == w ? cap - flow : flow; }
    void addflowRto(int vertex, int d) {
        if (vertex == w) flow += d;
        else flow -= d;
    }
};


template<class Graph, class Edge>
class MAXFLOW {
    const Graph &G;
    int s, t;
    vector<int> h;
    vector<int> wt;

    void initheights() {
        Graph R(G.getV(), true);

        for (int v = 0; v < G.getV(); v++) {
            typename Graph::adjIterator A(G, v);
            for (int w = A.beg(); !A.end(); w = A.nxt()) {
                R.addEdge(w, v, G.capacity[v][w]);
            }
        }

        h.assign(G.getV(), INT_MAX);
        queue<int> q;

        h[t] = 0;
        q.push(t);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            typename Graph::adjIterator A(R, v);
            for (int w = A.beg(); !A.end(); w = A.nxt()) {
                if (h[w] == INT_MAX) {
                    h[w] = h[v] + 1;
                    q.push(w);
                }
            }
        }

        h[s] = G.getV();
    }

public:
    MAXFLOW(const Graph &G, int s, int t) : G(G), s(s), t(t), h(G.getV()), wt(G.getV(), 0) {
        initheights();

        // 计算 M = 所有边容量的总和
        int M = 0;
        for (int v = 0; v < G.getV(); v++) {
            typename Graph::adjIterator A(G, v);
            for (int w = A.beg(); !A.end(); w = A.nxt()) {
                M += G.capacity[v][w];
            }
        }

        queue<int> gQ;
        gQ.push(s);
        wt[t] = -(wt[s] = M);

        while (!gQ.empty()) {
            int v = gQ.front();
            gQ.pop();

            typename Graph::adjIterator A(G, v);
            for (int w = A.beg(); !A.end(); w = A.nxt()) {
                int cap = G.capacity[v][w];
                int P = cap < wt[v] ? cap : wt[v];

                if (P > 0 && (v == s || h[v] == h[w] + 1)) {
                    // 这里需要解决 ， 泛型后类型转化的问题
                    G.getCapacity()[v][w] -= P;
                    G.getCapacity()[w][v] += P;
                    wt[v] -= P;
                    wt[w] += P;

                    if (w != s && w != t) {
                        gQ.push(w);
                    }
                }
            }

            if (v != s && v != t && wt[v] > 0) {
                h[v]++;
                gQ.push(v);
            }
        }
    }

    int getMaxFlow() const { return wt[t] + (wt[s] == 0 ? 0 : -wt[s]); }
};


void testMaxFlow() {
    // 测试用例1: 简单图
    {
        Graph G(4, true);
        G.addEdge(0, 1, 3);
        G.addEdge(0, 2, 2);
        G.addEdge(1, 2, 1);
        G.addEdge(1, 3, 3);
        G.addEdge(2, 3, 2);

        MAXFLOW<Graph, Edge> maxflow(G, 0, 3);
        cout << "Test Case 1 - Max Flow: " << maxflow.getMaxFlow() << " (Expected: 4)" << endl;
    }

    // 测试用例2: 更复杂的图
    {
        Graph G(6, true);
        G.addEdge(0, 1, 16);
        G.addEdge(0, 2, 13);
        G.addEdge(1, 2, 10);
        G.addEdge(1, 3, 12);
        G.addEdge(2, 1, 4);
        G.addEdge(2, 4, 14);
        G.addEdge(3, 2, 9);
        G.addEdge(3, 5, 20);
        G.addEdge(4, 3, 7);
        G.addEdge(4, 5, 4);

        MAXFLOW<Graph, Edge> maxflow(G, 0, 5);
        cout << "Test Case 2 - Max Flow: " << maxflow.getMaxFlow() << " (Expected: 23)" << endl;
    }

    // 测试用例3: 单边图
    {
        Graph G(2, true);
        G.addEdge(0, 1, 5);

        MAXFLOW<Graph, Edge> maxflow(G, 0, 1);
        cout << "Test Case 3 - Max Flow: " << maxflow.getMaxFlow() << " (Expected: 5)" << endl;
    }
}

int main(){
    // std::string line;
    // while (std::getline(std::cin, line)) {
    //     std::cout << "Read: " << line << std::endl;
    // }

    int token, t2;
    while (std::cin >> token >> t2) {  // 自动按空白分隔
        std::cout << "Processing token: " << token << "," << t2 << std::endl;
        // 处理每个独立token
    }

    testMaxFlow();

    return 0;
}
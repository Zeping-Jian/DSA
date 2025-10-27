//
// Created by 菅泽平 on 2025/5/24.
//

#ifndef DSA_GRAPHADJLIST_H
#define DSA_GRAPHADJLIST_H

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
private:
    int V; // 顶点数
    vector<list<pair<int, int>>> adjList; // 邻接表，pair表示(顶点, 权重)

public:
    // 构造函数
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    // 添加边（无向图）
    void addEdge(int u, int v) {
        adjList[u].push_back(make_pair(v, 1));
        adjList[v].push_back(make_pair(u, 1)); // 对于有向图，去掉这行
    }

    // 添加加权边
    void addWeightedEdge(int u, int v, int weight) {
        adjList[u].push_back(make_pair(v, weight));
        adjList[v].push_back(make_pair(u, weight)); // 对于有向图，去掉这行
    }

    // 打印图
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "顶点 " << i << " 的邻居: ";
            for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                cout << it->first << "(" << it->second << ") ";
            }
            cout << endl;
        }
    }
};

int test() {
    Graph g(5); // 创建有5个顶点的图

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printGraph();

    // 加权图示例
    Graph weightedG(4);
    weightedG.addWeightedEdge(0, 1, 5);
    weightedG.addWeightedEdge(0, 2, 3);
    weightedG.addWeightedEdge(1, 3, 2);
    weightedG.addWeightedEdge(2, 3, 7);

    cout << "\n加权图:" << endl;
    weightedG.printGraph();

    return 0;
}

#endif //DSA_GRAPHADJLIST_H

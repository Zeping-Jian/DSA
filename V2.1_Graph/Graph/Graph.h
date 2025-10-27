//
// Created by 菅泽平 on 2025/5/24.
//

#ifndef DSA_GRAPH_H
#define DSA_GRAPH_H

#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V; // 顶点数
    vector<vector<int>> adjMatrix; // 邻接矩阵

public:
    // 构造函数
    Graph(int vertices) : V(vertices) {
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void validateVertex(int v) {
        if (v < 0 || v >= V){
            // throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V-1));
            throw "非法的顶点:" + std::to_string(v);
        }
    }

    // 添加边（无向图）
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // 对于有向图，去掉这行
    }

    // 添加加权边
    void addWeightedEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; // 对于有向图，去掉这行
    }

    int degree(int v) {
        validateVertex(v);
        return adjMatrix[v].size();
    }

    // 打印图
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "顶点 " << i << " 的邻居: ";
            for (int j = 0; j < V; ++j) {
                if (adjMatrix[i][j] != 0) {
                    cout << j << "(" << adjMatrix[i][j] << ") ";
                }
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

    return 0;
}

#endif //DSA_GRAPH_H

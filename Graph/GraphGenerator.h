//
// Created by 菅泽平 on 2025/5/24.
//

#ifndef DSA_GraphGenerator_H
#define DSA_GraphGenerator_H

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

class RandomGraphGenerator {
private:
    mt19937 gen; // 随机数生成器
    uniform_real_distribution<double> dis; // [0,1)均匀分布

public:
    RandomGraphGenerator() : gen(time(nullptr)), dis(0.0, 1.0) {}

    // 生成无向图 (邻接矩阵表示)
    vector<vector<int>> generateErdosRenyi(int n, double p) {
        vector<vector<int>> graph(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (dis(gen) < p) {
                    graph[i][j] = 1;
                    graph[j][i] = 1;
                }
            }
        }
        return graph;
    }

    // 生成有向图 (邻接矩阵表示)
    vector<vector<int>> generateDirectedErdosRenyi(int n, double p) {
        vector<vector<int>> graph(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && dis(gen) < p) {
                    graph[i][j] = 1;
                }
            }
        }
        return graph;
    }

    // 打印图
    void printGraph(const vector<vector<int>>& graph) {
        int n = graph.size();
        for (int i = 0; i < n; ++i) {
            cout << "顶点 " << i << " 的邻居: ";
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] != 0) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
};

int testRandom() {
    RandomGraphGenerator generator;

    // 生成10个顶点，边存在概率0.3的无向图
    auto graph = generator.generateErdosRenyi(10, 0.3);
    cout << "无向随机图:" << endl;
    generator.printGraph(graph);

    // 生成8个顶点，边存在概率0.2的有向图
    auto directedGraph = generator.generateDirectedErdosRenyi(8, 0.2);
    cout << "\n有向随机图:" << endl;
    generator.printGraph(directedGraph);

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <random>
// #include <ctime>
//
// using namespace std;

// 随机加权图生成器
class WeightedGraphGenerator {
private:
    mt19937 gen;    // 随机生成器
    uniform_real_distribution<double> probDis;
    uniform_int_distribution<int> weightDis;

public:
    WeightedGraphGenerator(int minWeight = 1, int maxWeight = 10)
            : gen(time(nullptr)), probDis(0.0, 1.0), weightDis(minWeight, maxWeight) {}

    // 生成无向加权图
    vector<vector<int>> generateWeightedGraph(int n, double p) {
        vector<vector<int>> graph(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (probDis(gen) < p) {
                    int weight = weightDis(gen);
                    graph[i][j] = weight;
                    graph[j][i] = weight;
                }
            }
        }
        return graph;
    }

    // 打印加权图
    void printWeightedGraph(const vector<vector<int>>& graph) {
        int n = graph.size();
        for (int i = 0; i < n; ++i) {
            cout << "顶点 " << i << " 的邻居: ";
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] != 0) {
                    cout << j << "(" << graph[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }
};

int test2() {
    WeightedGraphGenerator generator(1, 20); // 权重范围1-20

    // 生成6个顶点，边存在概率0.4的加权图
    auto weightedGraph = generator.generateWeightedGraph(6, 0.4);
    cout << "加权随机图:" << endl;
    generator.printWeightedGraph(weightedGraph);

    return 0;
}


#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

class ConnectedGraphGenerator {
private:
    mt19937 gen;
    uniform_int_distribution<int> vertexDis;
    uniform_real_distribution<double> probDis;

    // 检查图是否连通 (使用DFS)
    bool isConnected(const vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> visited(n, false);
        int count = 0;
        dfs(0, graph, visited, count);
        return count == n;
    }

    void dfs(int v, const vector<vector<int>>& graph, vector<bool>& visited, int& count) {
        visited[v] = true;
        count++;
        for (int i = 0; i < graph.size(); ++i) {
            if (graph[v][i] && !visited[i]) {
                dfs(i, graph, visited, count);
            }
        }
    }

public:
    ConnectedGraphGenerator() : gen(time(nullptr)), vertexDis(0, 1), probDis(0.0, 1.0) {}

    // 生成连通无向图
    vector<vector<int>> generateConnectedGraph(int n, double p) {
        vector<vector<int>> graph(n, vector<int>(n, 0));

        // 先生成一个生成树保证连通性
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i;
        shuffle(vertices.begin(), vertices.end(), gen);

        for (int i = 1; i < n; ++i) {
            int j = uniform_int_distribution<int>(0, i-1)(gen);
            graph[vertices[i]][vertices[j]] = 1;
            graph[vertices[j]][vertices[i]] = 1;
        }

        // 然后按照概率p添加其他边
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (graph[i][j] == 0 && probDis(gen) < p) {
                    graph[i][j] = 1;
                    graph[j][i] = 1;
                }
            }
        }

        return graph;
    }

    void printGraph(const vector<vector<int>>& graph) {
        int n = graph.size();
        for (int i = 0; i < n; ++i) {
            cout << "顶点 " << i << " 的邻居: ";
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] != 0) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
};

int test3() {
    ConnectedGraphGenerator generator;

    // 生成8个顶点的连通图，额外边概率0.2
    auto connectedGraph = generator.generateConnectedGraph(8, 0.2);
    cout << "连通随机图:" << endl;
    generator.printGraph(connectedGraph);

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <random>
// #include <ctime>
// #include <algorithm>
//
// using namespace std;

//
class DAGGenerator {
private:
    mt19937 gen;
    uniform_real_distribution<double> probDis;

    // 检查是否有环 (使用DFS)
    bool hasCycle(const vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> visited(n, false), recursionStack(n, false);

        for (int i = 0; i < n; ++i) {
            if (!visited[i] && hasCycleUtil(i, graph, visited, recursionStack)) {
                return true;
            }
        }
        return false;
    }

    bool hasCycleUtil(int v, const vector<vector<int>>& graph,
                      vector<bool>& visited, vector<bool>& recursionStack) {
        visited[v] = true;
        recursionStack[v] = true;

        for (int i = 0; i < graph.size(); ++i) {
            if (graph[v][i]) {
                if (!visited[i] && hasCycleUtil(i, graph, visited, recursionStack)) {
                    return true;
                } else if (recursionStack[i]) {
                    return true;
                }
            }
        }

        recursionStack[v] = false;
        return false;
    }

public:
    DAGGenerator() : gen(time(nullptr)), probDis(0.0, 1.0) {}

    // 生成有向无环图
    vector<vector<int>> generateDAG(int n, double p) {
        vector<vector<int>> graph(n, vector<int>(n, 0));

        // 先生成一个拓扑排序
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i;
        shuffle(vertices.begin(), vertices.end(), gen);

        // 只允许从排序靠前的顶点指向排序靠后的顶点
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (probDis(gen) < p) {
                    graph[vertices[i]][vertices[j]] = 1;
                }
            }
        }

        // 确保无环
        if (hasCycle(graph)) {
            // 如果意外产生了环(由于浮点误差等)，重新生成
            return generateDAG(n, p);
        }

        return graph;
    }

    void printGraph(const vector<vector<int>>& graph) {
        int n = graph.size();
        for (int i = 0; i < n; ++i) {
            cout << "顶点 " << i << " 指向: ";
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] != 0) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
};

int test4() {
    DAGGenerator generator;

    // 生成7个顶点的DAG，边存在概率0.3
    auto dag = generator.generateDAG(7, 0.3);
    cout << "随机DAG:" << endl;
    generator.printGraph(dag);

    return 0;
}

// 4.1 生成特定度数的随机图

class DegreeSpecificGraphGenerator {
private:
    mt19937 gen;

    // 检查图是否有效
    bool isValidGraph(const vector<int>& degrees) {
        int sum = 0;
        for (int d : degrees) {
            if (d < 0) return false;
            sum += d;
        }
        return sum % 2 == 0; // 握手定理
    }

public:
    DegreeSpecificGraphGenerator() : gen(time(nullptr)) {}

    // 使用Havel-Hakimi算法生成图
    vector<vector<int>> generateGraph(vector<int> degrees) {
        if (!isValidGraph(degrees)) {
            throw invalid_argument("度数序列不合法");
        }

        int n = degrees.size();
        vector<vector<int>> graph(n, vector<int>(n, 0));
        vector<pair<int, int>> nodes;

        for (int i = 0; i < n; ++i) {
            nodes.emplace_back(degrees[i], i);
        }

        while (true) {
            sort(nodes.begin(), nodes.end(), greater<pair<int, int>>());

            // 检查是否所有度数都为0
            if (nodes[0].first == 0) break;

            int d = nodes[0].first;
            int v = nodes[0].second;

            // 连接v与后面d个度数最大的节点
            for (int i = 1; i <= d; ++i) {
                if (i >= n || nodes[i].first == 0) {
                    throw runtime_error("无法构造满足条件的图");
                }
                int u = nodes[i].second;
                graph[v][u] = 1;
                graph[u][v] = 1;
                nodes[i].first--;
            }

            nodes[0].first = 0;
        }

        return graph;
    }

    // 生成随机度数序列的图
    vector<vector<int>> generateRandomDegreeGraph(int n, int maxDegree) {
        uniform_int_distribution<int> dis(1, maxDegree);
        vector<int> degrees(n);

        do {
            for (int i = 0; i < n; ++i) {
                degrees[i] = dis(gen);
            }
        } while (!isValidGraph(degrees));

        return generateGraph(degrees);
    }

    void printGraph(const vector<vector<int>>& graph) {
        int n = graph.size();
        for (int i = 0; i < n; ++i) {
            cout << "顶点 " << i << " 的邻居: ";
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] != 0) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
};

int test5() {
    DegreeSpecificGraphGenerator generator;

    // 生成5个顶点的图，每个顶点度数不超过3
    auto graph = generator.generateRandomDegreeGraph(5, 3);
    cout << "特定度数的随机图:" << endl;
    generator.printGraph(graph);

    return 0;
}

#endif //DSA_GraphGenerator_H

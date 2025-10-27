#ifndef GRAPH_CC_
#define GRAPH_CC_

#include "Edge.cc"

// Program 17.1 Graph ADT
class GRAPH {
private:
public:
    GRAPH(int, bool);
    ~GRAPH();
    
    int V() const;
    int E() const;
    bool directed() const;
    
    void insert(Edge);
    void remove(Edge);
    bool edge(int, int) const;

    // Упражнение 17.20
    void insert(); // Добавления новой вершины
    void remove(int); // Удаление вершины

    // Упражнение 17.34
    void removeLoopsAndParallels();

    class adjIterator {
    public:
        adjIterator(const GRAPH &, int);
        int beg();
        int nxt();
        bool end();
    };
};

#endif

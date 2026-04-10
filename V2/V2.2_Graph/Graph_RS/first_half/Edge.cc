#ifndef EDGE_CC_
#define EDGE_CC_

// Программа 17.1. Интерфейс ребра графа
// Program 17.1 基础边定义
// class Edge {
// private:
//     int pcost;
//     int pflow; // 边流量？
//
// public:
//     int v, w;
//
//     Edge(int v = -1, int w = -1) : v(v), w(w), pcost(0), pflow(0) {}
//
//
//     // int v() const { return v; };
//     // int w() const {return w;};
//     // double wt() const;
//
//     int cost() const { return pcost; }
//
//     bool from(int in) const { // 如果是原点指向终点，则认为代价是正
//         return v == in;
//     };
//
//     int flow() const{
//         return pflow;
//     }
//     int other(int) const { return false; };
//
//     int costRto(int v) { return from(v) ? -pcost : pcost; }
// };

class Edge {

    int pcap, pflow;
    int pcost;
public:
    int v, w;

    Edge(int v = -1, int w = -1) : v(v), w(w){}

    Edge(int v, int w, int cap) :
            v(v), w(w), pcap(cap), pflow(0) {}

    // int v() const { return pv; }
    // int w() const { return pw; }

    int cap() const { return pcap; }

    int flow() const { return pflow; }

    bool from(int v_in) const { return v == v_in; }

    int other(int v) const { return from(v) ? w : v; }

    int capRto(int v) const { return from(v) ? pflow : pcap - pflow; }

    int costRto(int v) { return from(v) ? -pcost : pcost; }

    // 什么作用？
    void addflowRto(int v, int d) { pflow += from(v) ? -d : d; }
};

#endif
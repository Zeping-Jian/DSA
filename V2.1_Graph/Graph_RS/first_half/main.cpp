#include <cstdlib>
#include <sys/time.h>
#include "process_mem_usage.h"

#include "DenseGRAPH.cc"
#include "UndirDenseGRAPH.cc"
#include "UndirBitDenseGRAPH.cc"
#include "DenseMultiGRAPH.cc"
#include "SparseGRAPH.cc"
#include "EdgeOptimalSparseGRAPH.cc"
#include "SparseMultiGRAPH.cc"
#include "STLSparseMultiGRAPH.cc"
#include "StaticMultiGRAPH.cc"

#include "IO.cc"

#include "sPATH.cc"
#include "gPATH.cc"
#include "ePATH.cc"

#include "cDFS.cc"
#include "diDFS.cpp"
#include "DFS.cc"
#include "EC.cc"
#include "BC.cc"
#include "InfoDFS.cc"
#include "CC.cc"
#include "EULER.cc"
#include "BI.cc"
#include "BFS.cc"
#include "PFS.cc"

#include "TC.cc"
// #include "tc.cc"
#include "TCsc.cc"


#include "SCk.cc"
#include "SCt.cc"
#include "SCg.cc"

// typedef DenseGRAPH Graph;
// typedef UndirDenseGRAPH Graph;
// typedef UndirBitDenseGRAPH Graph;
// typedef DenseMultiGRAPH Graph;
// typedef SparseGRAPH Graph;
// typedef EdgeOptimalSparseGRAPH Graph;
typedef SparseMultiGRAPH Graph;
// typedef STLSparseMultiGRAPH Graph;
// typedef StaticMultiGRAPH Graph;

// typedef DFS<Graph> DFST;
typedef InfoDFS<Graph> DFST;
// typedef EULER<Graph> DFST;
// typedef BI<Graph> DFST;

// typedef SCg<Graph> SC;

void graphInfo(const Graph &G) {
    IO<Graph>::show(G);
    IO<Graph>::showEdges(G);
    IO<Graph>::showAdj(G);
}

void removeAllEdges(Graph &G) {
    vector<Edge> vec = edges(G);
    for (vector<Edge>::iterator p = vec.begin(); p != vec.end(); ++p) {
        G.remove(*p);
    }
}

// Упражнение 17.65, 17.66
void measure(char *argv[]) {
    Graph G(atoi(argv[1]), true);
    IO<Graph>::scanEZ(G);

    timeval tBegin, tEnd;
    gettimeofday(&tBegin, NULL);

// BODY -->

    // IO<Graph>::randG(G, 2 * G.V());
    DFST s(G);
    // cout << "OK = " << s.bipartite() << endl;

// <-- BODY

    gettimeofday(&tEnd, NULL);
    double elapsedTime = (tEnd.tv_sec - tBegin.tv_sec) * 1000.0;  // sec to ms
    elapsedTime += (tEnd.tv_usec - tBegin.tv_usec) / 1000.0;      // us to ms
    cout << elapsedTime << " ms.\n";

    double vm, rss;
    process_mem_usage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;
}

void test(char *argv[]) {
    // Graph G(atoi(argv[1]), true);
    // IO<Graph>::scanEZ(G);
    // // IO<Graph>::scan(G);
    // // removeAllEdges(G);
    // graphInfo(G);

    // // Graph O = G;
    // Graph O = removeZerosLoopsParallels(G);
    // graphInfo(O);

    // G.insert();
    // G.insert();
    // graphInfo(G);
    // cout << "zeros: " << G.zeros() << " | " << zeros(G) << endl;
    // for (int v = 0; v < G.V(); ++v) {
    //     cout << v << ": " << G.degree(v) << endl;
    // }

    // G.remove(0);
    // graphInfo(G);

    // findMaxSeqClique(G);

    // cout << "sPATH = " << sPATH<Graph>(G, 1, 2).exist() << endl;

    // Hamilton Path
    // cout << "gPATH = " << gPATH<Graph>(G, 1, 2).exist() << endl;

    // 欧拉路径
    // ePATH<Graph> ep(G, 1, 2);
    // cout << "ePATH = " << ep.exist() << endl;
    // ep.show();

    // cDFS cdfs(G);
    // cdfs.printVistOrd();

    // 18. 桥搜索
    // EC<Graph> mEc(G);
    // cout << "Bridge count=" << mEc.count() << endl;
    // mEc.printOrd();
    // mEc.printLow();

    // 18.x 关节点
    // BC<Graph> mBc(G, 0);
    // cout << "Bridge count=" << mBc.count() << endl;
    // mBc.printOrd();
    // mBc.printLow();
    // mBc.printBC();


}

void test19_2(char *argv[]){
    // 19.12 Gabow 算法
    // 必须是有向图
    Graph G(atoi(argv[1]), true);
    IO<Graph>::scanEZ(G);
    graphInfo(G);

    // 有向图的DFS算法,并标记 pre post
    diDFS<Graph> mDiDFS(G);

}

// 测试联通分量
void test19(char *argv[]){
    // 19.12 Gabow 算法
    // 必须是有向图
    Graph G(atoi(argv[1]), true);
    IO<Graph>::scanEZ(G);
    // IO<Graph>::scan(G);
    // removeAllEdges(G);
    graphInfo(G);
    SCg<Graph> mSCg(G);
    for (int i = 0; i < G.V(); ++i) {
        cout << " " << mSCg.ID(i);
    }
    cout << endl;
}

#include "dagTSs.cc"
#include "dagTSq.cc"

void test19_6(char *argv[]){
    // 输入必须是Dag 图
    Graph G(atoi(argv[1]), true);
    IO<Graph>::scanEZ(G);
    // IO<Graph>::scan(G);
    // removeAllEdges(G);
    graphInfo(G);


    dagTSs<Graph> mDagTSs(G);
    mDagTSs.printPre();
    cout.width(2);
    for(int i = 0; i < G.V(); i++){
        cout.width(2);
        cout << mDagTSs[i] << " ";
    }
    cout << endl;
    cout.width(2);
    for(int i = 0; i < G.V(); i++){
        cout.width(2);
        cout << mDagTSs.relabel(i) << " ";
    }
    cout << endl;

    // cout << "========" << endl;
    // 使用方法2 进行拓扑排序看看 同一张图是什么结果 ，，
    dagTSq<Graph> mDagTSq(G);
    mDagTSq.printPre();
    cout.width(2);
    for(int i = 0; i < G.V(); i++){
        cout.width(2);
        cout << mDagTSs[i] << " ";
    }
    cout << endl;
    cout.width(2);
    for(int i = 0; i < G.V(); i++){
        cout.width(2);
        cout << mDagTSs.relabel(i) << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    // measure(argv);
    // test(argv);

    // test19_2(argv);
    // test19(argv);

    test19_6(argv);

    return 0;
}

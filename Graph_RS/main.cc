#include "second_half/WeightedEdge.cc"
#include "second_half/DenseGRAPH.cc"
#include "second_half/SparseMultiGRAPH.cc"
#include "second_half/IO.cc"

#include "second_half/MSTpr.cc"
#include "second_half/MSTcr.cc"
#include "second_half/MSTbr.cc"

typedef WeightedEdge Edge;
typedef DenseGRAPH<Edge> Graph;

void graphInfo(const Graph &G) {
    // IO<Graph, Edge>::show(G);
    // IO<Graph, Edge>::showEdges(G);
    IO<Graph, Edge>::showAdj(G);
}

int testBaseGraph() {
    int V;
    cin >> V;
    Graph G(V);

    IO<Graph, Edge>::scanEZ(G);
    MSTbr<Graph, Edge>(G).show();

    // graphInfo(G);

    return 0;
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

    return 0;
}
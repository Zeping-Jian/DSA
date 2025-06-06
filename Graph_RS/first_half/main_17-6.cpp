#include <iostream>
#include <cstdlib>
// #include "GRAPH.cc"
#include "DenseGRAPH.cc"
#include "IO.cc"
#include "CC.cc"

using namespace std;

typedef DenseGRAPH GRAPH;
// Программа 17.6. Пример клиентской программы обработки графов
int main(int argc, char *argv[]) {
    int V = atoi(argv[1]);
    GRAPH G(V);
    IO<GRAPH>::scanStr(G);
    if (V < 20) IO<GRAPH>::show(G);
    cout << G.E() << " edges, V=" << G.V() << endl;

    CC<DenseGRAPH> Gcc(G);
    cout << Gcc.count() << " components" << endl;
    return 0;
}
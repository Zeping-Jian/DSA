#ifndef DAGTSS_CC_
#define DAGTSS_CC_

#include <vector>

using namespace std;

// Программа 19.6. Обратная топологическая сортировка
template<class Dag> // Dag 是指DAG的图，并没有一个新类
class dagTSs {
    const Dag &D;
    int cnt, tcnt;
    vector<int> pre, post; // 前序序列， 后续序列
    vector<int> postI; // 逆序后的 后续序列

    void tsR(int v) {
        pre[v] = cnt++;
        // cout << "pre cnt=" <<cnt << ",v=" << v << endl;
        typename Dag::adjIterator A(D, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (pre[t] == -1) {
                // cout << "re " << ",t=" << t << endl;
                tsR(t);
            }
        }
        post[v] = tcnt;
        postI[tcnt++] = v;
        // cout << "post tcnt=" << tcnt << ",v=" << v << endl;
    }

public:
    dagTSs(const Dag &D) : D(D), cnt(0), tcnt(0),
                           pre(D.V(), -1), post(D.V(), -1), postI(D.V(), -1) {
        for (int v = 0; v < D.V(); v++) {
            if (pre[v] == -1) tsR(v);
        }
    }

    int operator[](int v) const { return postI[v]; }

    int relabel(int v) const { return post[v]; }

    void printPre(){
        // 打印标准序列
        for(int i = 0; i < D.V(); i++){
            cout.width(2);
            cout << i << " ";
        }
        cout << endl;

        // 打印前序序列
        for(int i = 0; i < D.V(); i++){
            cout.width(2);
            cout << pre[i] << " ";
        }
        cout << endl;
    }
};

#endif
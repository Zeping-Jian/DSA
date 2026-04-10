//
// Created by 菅泽平 on 2025/5/23.
//

#ifndef DSA_EVBTREE_H
#define DSA_EVBTREE_H

#include <iostream>
#include <cmath>
#include <memory>
#include <climits>
#include <vector>

class VEBTree {
private:
    int u;  // 全域大小
    int min, max;
    std::unique_ptr<VEBTree> summary;
    std::vector<std::unique_ptr<VEBTree>> clusters;

    // 计算高位和低位
    int high(int x) const { return x / (int)std::sqrt(u); }
    int low(int x) const { return x % (int)std::sqrt(u); }
    int index(int x, int y) const { return x * (int)std::sqrt(u) + y; }

public:
    explicit VEBTree(int universe) : u(universe), min(-1), max(-1) {
        if (u <= 2) {
            summary = nullptr;
            clusters = std::vector<std::unique_ptr<VEBTree>>(0);
        } else {
            int upper = (int)std::ceil(std::sqrt(u));
            int lower = (int)std::floor(std::sqrt(u));
            std::cout << "upper=" << upper << ",lower=" << lower << std::endl;

            summary = std::make_unique<VEBTree>(upper);
            clusters.resize(upper);

            for (int i = 0; i < upper; ++i) {
                clusters[i] = std::make_unique<VEBTree>(lower);
            }
        }
    }

    // 判断树是否为空
    bool isEmpty() const { return min == -1; }

    // 判断元素是否存在
    bool contains(int x) const {
        if (x == min || x == max) return true;
        if (u == 2) return false;
        return clusters[high(x)]->contains(low(x));
    }

    // 插入元素
    void insert(int x) {
        if (isEmpty()) {
            min = max = x;
            return;
        }

        if (x < min) std::swap(x, min);

        if (u > 2) {
            int h = high(x);
            int l = low(x);

            if (clusters[h]->isEmpty()) {
                summary->insert(h);
                clusters[h]->min = l;
                clusters[h]->max = l;
            } else {
                clusters[h]->insert(l);
            }
        }

        if (x > max) max = x;
    }

    // 删除元素
    void remove(int x) {
        if (min == max) {
            min = max = -1;
            return;
        }

        if (u == 2) {
            if (x == 0) {
                min = (max == 0) ? -1 : 1;
            } else {
                max = (min == 1) ? -1 : 0;
            }
            return;
        }

        if (x == min) {
            int firstCluster = summary->min;
            x = index(firstCluster, clusters[firstCluster]->min);
            min = x;
        }

        int h = high(x);
        int l = low(x);
        clusters[h]->remove(l);

        if (clusters[h]->isEmpty()) {
            summary->remove(h);
            if (x == max) {
                int summaryMax = summary->max;
                if (summaryMax == -1) {
                    max = min;
                } else {
                    max = index(summaryMax, clusters[summaryMax]->max);
                }
            }
        } else if (x == max) {
            max = index(h, clusters[h]->max);
        }
    }

    // 查找后继
    int successor(int x) const {
        if (u == 2) {
            if (x == 0 && max == 1) return 1;
            return -1;
        }

        if (!isEmpty() && x < min) return min;

        int h = high(x);
        int l = low(x);
        int maxLow = clusters[h]->max;

        if (maxLow != -1 && l < maxLow) {
            int offset = clusters[h]->successor(l);
            return index(h, offset);
        }

        int succCluster = summary->successor(h);
        if (succCluster == -1) return -1;

        int offset = clusters[succCluster]->min;
        return index(succCluster, offset);
    }

    // 查找前驱
    int predecessor(int x) const {
        if (u == 2) {
            if (x == 1 && min == 0) return 0;
            return -1;
        }

        if (!isEmpty() && x > max) return max;

        int h = high(x);
        int l = low(x);
        int minLow = clusters[h]->min;

        if (minLow != -1 && l > minLow) {
            int offset = clusters[h]->predecessor(l);
            return index(h, offset);
        }

        int predCluster = summary->predecessor(h);
        if (predCluster == -1) {
            if (!isEmpty() && x > min) return min;
            return -1;
        }

        int offset = clusters[predCluster]->max;
        return index(predCluster, offset);
    }

    // 获取最小值
    int getMin() const { return min; }

    // 获取最大值
    int getMax() const { return max; }
};

#endif //DSA_EVBTREE_H

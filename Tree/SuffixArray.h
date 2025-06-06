//
// Created by 菅泽平 on 2025/5/23.
//

#ifndef DSA_SUFFIXARRAY_H
#define DSA_SUFFIXARRAY_H

// 完整 C++ 实现（基于Kasai算法构建LCP数组）

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

class SuffixArray {
private:
    std::string text;
    std::vector<int> sa;   // 后缀数组
    std::vector<int> lcp;  // 最长公共前缀数组
    std::vector<int> rank; // 排名数组

    // 构建后缀数组（使用排序方法）
    void buildSuffixArray() {
        int n = text.size();
        sa.resize(n);
        rank.resize(n);

        // 初始排序（单个字符）
        for (int i = 0; i < n; ++i) {
            sa[i] = i;
            rank[i] = text[i];
        }

        // 比较函数
        auto cmp = [this](int a, int b, int k) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int ra = (a + k < text.size()) ? rank[a + k] : -1;
            int rb = (b + k < text.size()) ? rank[b + k] : -1;
            return ra < rb;
        };

        // 倍增算法
        for (int k = 1; k < n; k *= 2) {
            // 排序
            std::sort(sa.begin(), sa.end(), [&](int a, int b) {
                return cmp(a, b, k);
            });

            // 重新计算rank
            std::vector<int> newRank(n);
            newRank[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                newRank[sa[i]] = newRank[sa[i - 1]] + (cmp(sa[i - 1], sa[i], k) ? 1 : 0);
            }
            rank = std::move(newRank);

            // 如果所有后缀已经唯一，提前结束
            if (rank[sa.back()] == n - 1) break;
        }
    }

    // 构建LCP数组（Kasai算法）
    void buildLCPArray() {
        int n = text.size();
        lcp.resize(n);
        std::vector<int> invSa(n);

        for (int i = 0; i < n; ++i) {
            invSa[sa[i]] = i;
        }

        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (invSa[i] == n - 1) {
                k = 0;
                continue;
            }

            int j = sa[invSa[i] + 1];
            while (i + k < n && j + k < n && text[i + k] == text[j + k]) {
                k++;
            }

            lcp[invSa[i]] = k;
            if (k > 0) k--;
        }
    }

public:
    explicit SuffixArray(const std::string& input) : text(input) {
        buildSuffixArray();
        buildLCPArray();
    }

    // 获取后缀数组
    const std::vector<int>& getSuffixArray() const {
        return sa;
    }

    // 获取LCP数组
    const std::vector<int>& getLCPArray() const {
        return lcp;
    }

    // 检查是否包含子串（二分查找）
    bool contains(const std::string& pattern) const {
        int left = 0;
        int right = text.size() - 1;
        int m = pattern.size();

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cmp = text.compare(sa[mid], m, pattern);

            if (cmp == 0) {
                return true;
            } else if (cmp < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;
    }

    // 查找所有出现位置
    std::vector<int> getAllOccurrences(const std::string& pattern) const {
        std::vector<int> occurrences;
        int n = text.size();
        int m = pattern.size();

        // 查找第一个出现位置
        int first = -1;
        int left = 0;
        int right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cmp = text.compare(sa[mid], m, pattern);

            if (cmp == 0) {
                first = mid;
                right = mid - 1;
            } else if (cmp < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (first == -1) return occurrences;

        // 查找最后一个出现位置
        int last = first;
        left = first;
        right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cmp = text.compare(sa[mid], m, pattern);

            if (cmp == 0) {
                last = mid;
                left = mid + 1;
            } else if (cmp < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // 收集所有出现位置
        for (int i = first; i <= last; ++i) {
            occurrences.push_back(sa[i]);
        }

        std::sort(occurrences.begin(), occurrences.end());
        return occurrences;
    }

    // 查找最长重复子串
    std::string getLongestRepeatedSubstring() const {
        int maxLen = 0;
        int startPos = 0;

        for (int i = 1; i < text.size(); ++i) {
            if (lcp[i] > maxLen) {
                maxLen = lcp[i];
                startPos = sa[i];
            }
        }

        return text.substr(startPos, maxLen);
    }

    // 打印后缀数组（调试用）
    void printSuffixArray() const {
        std::cout << "Suffix Array:\n";
        for (int i = 0; i < sa.size(); ++i) {
            std::cout << i << ": " << sa[i] << " -> " << text.substr(sa[i]) << "\n";
        }
    }

    // 打印LCP数组（调试用）
    void printLCPArray() const {
        std::cout << "LCP Array:\n";
        for (int i = 0; i < lcp.size(); ++i) {
            std::cout << i << ": " << lcp[i] << "\n";
        }
    }
};

#endif //DSA_SUFFIXARRAY_H

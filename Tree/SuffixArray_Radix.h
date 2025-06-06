//
// Created by 菅泽平 on 2025/5/23.
//

#ifndef DSA_SUFFIXARRAY_RADIX_H
#define DSA_SUFFIXARRAY_RADIX_H

// 完整 C++ 实现（基于Kasai算法构建LCP数组）
// 后缀数组的c++实现，通过基数排序

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>

class SuffixArray_Radix {
private:
    std::string text;
    std::vector<int> sa;   // 后缀数组
    std::vector<int> rank; // 排名数组
    std::vector<int> lcp;  // 最长公共前缀数组

    // 基数排序辅助函数
    void countingSort(int k) {
        int n = text.size();
        std::vector<int> count(std::max(256, n)), output(n);

        // 统计频率
        for (int i = 0; i < n; ++i) {
            int idx = (i + k < n) ? rank[i + k] : 0;
            count[idx]++;
        }

        // 计算前缀和
        for (int i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }

        // 构建排序结果
        for (int i = n - 1; i >= 0; --i) {
            int idx = (sa[i] + k < n) ? rank[sa[i] + k] : 0;
            output[--count[idx]] = sa[i];
        }

        sa = output;
    }

    // 构建后缀数组（使用基数排序）
    void buildSuffixArray() {
        int n = text.size();
        sa.resize(n);
        rank.resize(n);

        // 初始排序（单个字符）
        for (int i = 0; i < n; ++i) {
            sa[i] = i;
            rank[i] = text[i];
        }

        // 倍增算法
        for (int k = 1; k < n; k *= 2) {
            // 对第二关键字排序
            countingSort(k);
            // 对第一关键字排序
            countingSort(0);

            // 重新计算rank
            std::vector<int> newRank(n);
            newRank[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                // 比较当前和上一个后缀的两个关键字
                bool equal = true;
                if (rank[sa[i]] != rank[sa[i - 1]]) {
                    equal = false;
                } else {
                    int a = (sa[i] + k < n) ? rank[sa[i] + k] : -1;
                    int b = (sa[i - 1] + k < n) ? rank[sa[i - 1] + k] : -1;
                    if (a != b) equal = false;
                }

                newRank[sa[i]] = newRank[sa[i - 1]] + (equal ? 0 : 1);
            }
            rank = newRank;

            // 如果所有排名已经唯一，提前结束
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
    explicit SuffixArray_Radix(const std::string& input) : text(input) {
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
};

int testSuffixArray_Radix() {
    std::string text = "banana";
    SuffixArray_Radix sa(text);

    // 打印后缀数组
    sa.printSuffixArray();

    // 测试子串查找
    std::cout << "Contains 'ana': " << sa.contains("ana") << std::endl;
    std::cout << "Contains 'nan': " << sa.contains("nan") << std::endl;
    std::cout << "Contains 'ban': " << sa.contains("ban") << std::endl;
    std::cout << "Contains 'aba': " << sa.contains("aba") << std::endl;

    // 测试所有出现位置
    std::vector<int> occurrences = sa.getAllOccurrences("ana");
    std::cout << "Occurrences of 'ana': ";
    for (int pos : occurrences) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    // 测试最长重复子串
    std::cout << "Longest repeated substring: "
              << sa.getLongestRepeatedSubstring() << std::endl;

    return 0;
}
#endif //DSA_SUFFIXARRAY_RADIX_H

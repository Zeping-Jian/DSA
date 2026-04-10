

//
// Created by 菅泽平 on 2025/10/27.
//

#include <vector>
using namespace std;

// 组合 回溯简单实现
// LeetCode 77. 组合
// 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    
    void backtracking(int n, int k, int startIndex) {
        // 终止条件：当path的大小等于k时，找到一个组合
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        
        // 遍历范围：从startIndex开始，到n结束
        // 剪枝优化：如果剩余元素不足以构成一个组合，则提前结束
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) {
            path.push_back(i);           // 处理节点
            backtracking(n, k, i + 1);   // 递归
            path.pop_back();             // 回溯，撤销处理的节点
        }
    }
    
public:
    vector<vector<int>> combine(int n, int k) {
        result.clear();
        path.clear();
        backtracking(n, k, 1);
        return result;
    }
};

// 示例用法和测试
/*
示例 1:
输入: n = 4, k = 2
输出: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]

示例 2:
输入: n = 1, k = 1
输出: [[1]]

回溯算法三部曲：
1. 递归函数的参数和返回值
2. 递归终止条件
3. 单层搜索的过程

时间复杂度：O(C(n,k) * k) = O(n! / ((n-k)! * k!) * k)
空间复杂度：O(k) - 递归深度和path数组的空间
*/
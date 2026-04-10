
#include "BinTree.hpp"
#include <iostream>
using namespace std;

// 二叉树的 路径综合
class Solution {
public:
    int targetSum;          // 目标路径和
    bool traversal(TreeNode* cur, int count)   // 注意函数的返回类型
    {
        if (cur == NULL) return false;          // 空节点，返回false
        count += cur->val;                      // 中，累加节点值到count
        if (cur->left == NULL && cur->right == NULL) { // 叶子节点
            return count == targetSum;          // 判断路径和是否等于目标值
        }
        // 左右递归遍历，任一子树返回true则返回true
        return traversal(cur->left, count) || traversal(cur->right, count);
    }
    
    bool hasPathSum(TreeNode* root, int targetSum) {
        this->targetSum = targetSum;            // 设置目标路径和
        return traversal(root, 0);              // 从根节点开始遍历，初始路径和为0
    }
};
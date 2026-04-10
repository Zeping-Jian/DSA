
#include "BinTree.hpp"
#include <iostream>

#include <iostream>
#include <algorithm> // 用于std::abs和std::max

using namespace std;

// https://github.com/youngyangyang04/leetcode-master/blob/master/problems/0110.%E5%B9%B3%E8%A1%A1%E4%BA%8C%E5%8F%89%E6%A0%91.md
// 本题中，一棵高度平衡二叉树定义为：一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。

// 后序遍历思路
class Solution {
public:
    // 返回以该节点为根节点的二叉树的高度，如果不是平衡二叉树了则返回-1
    int getHeight(TreeNode* node) {
        if (node == NULL) {
            return 0;
        }
        int leftHeight = getHeight(node->left);
        if (leftHeight == -1) return -1;
        int rightHeight = getHeight(node->right);
        if (rightHeight == -1) return -1;
        return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);
    }
    bool isBalanced(TreeNode* root) {
        return getHeight(root) == -1 ? false : true;
    }
};


class Solution {
public:
    // 判断二叉树是否平衡
    bool isBalanced(TreeNode* root) {
        // 若辅助函数返回值≠-1，则平衡
        return getHeightAndCheck(root) != -1;
    }

private:
    // 辅助函数：返回当前子树的高度，若不平衡则返回-1
    int getHeightAndCheck(TreeNode* node) {
        // 空节点高度为0（平衡）
        if (node == nullptr) {
            return 0;
        }
        
        // 计算左子树高度，若左子树不平衡，直接返回-1
        int leftHeight = getHeightAndCheck(node->left);
        if (leftHeight == -1) {
            return -1;
        }
        
        // 计算右子树高度，若右子树不平衡，直接返回-1
        int rightHeight = getHeightAndCheck(node->right);
        if (rightHeight == -1) {
            return -1;
        }
        
        // 检查当前节点的左右子树高度差，若超过1则不平衡
        if (std::abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        
        // 若平衡，返回当前子树的高度（左右子树最大高度+1）
        return std::max(leftHeight, rightHeight) + 1;
    }
};

// 测试示例
int main() {
    // 示例1：平衡树
    //       3
    //      / \
    //     9  20
    //       /  \
    //      15   7
    TreeNode* balancedTree = new TreeNode(3);
    balancedTree->left = new TreeNode(9);
    balancedTree->right = new TreeNode(20);
    balancedTree->right->left = new TreeNode(15);
    balancedTree->right->right = new TreeNode(7);
    
    // 示例2：不平衡树（根节点左子树高度为2，右子树高度为0，差2）
    //       1
    //        \
    //         2
    //          \
    //           3
    TreeNode* unbalancedTree = new TreeNode(1);
    unbalancedTree->right = new TreeNode(2);
    unbalancedTree->right->right = new TreeNode(3);
    
    Solution solution;
    std::cout << "平衡树测试：" << (solution.isBalanced(balancedTree) ? "是" : "否") << std::endl; // 输出：是
    std::cout << "不平衡树测试：" << (solution.isBalanced(unbalancedTree) ? "是" : "否") << std::endl; // 输出：否
    
    // 释放内存（实际工程中需递归释放，此处简化）
    delete balancedTree->left;
    delete balancedTree->right->left;
    delete balancedTree->right->right;
    delete balancedTree->right;
    delete balancedTree;
    
    delete unbalancedTree->right->right;
    delete unbalancedTree->right;
    delete unbalancedTree;
    
    return 0;
}


#include "BinTree.hpp"
#include <iostream>
using namespace std;

// 二叉树的最小深度

class Solution {
public:
    int getdepth(TreeNode* node) {
        if (node == NULL) return 0;
        int leftdepth = getdepth(node->left);       // 左
        int rightdepth = getdepth(node->right);     // 右
        
        // 如果左子树为空，则最小深度取右子树的深度 + 1
        if (node->left == NULL) {
            return 1 + rightdepth;
        }
        // 如果右子树为空，则最小深度取左子树的深度 + 1
        if (node->right == NULL) {
            return 1 + leftdepth;
        }
        // 如果左右子树都不为空，取较小的深度 + 1
        return 1 + min(leftdepth, rightdepth);
    }
    int minDepth(TreeNode* root) {
        return getdepth(root);
    }
};

class Solution_2 {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        int leftdepth = minDepth(root->left);
        int rightdepth = minDepth(root->right);
        if (root->left == NULL) {
            return 1 + rightdepth;
        }
        if (root->right == NULL) {
            return 1 + leftdepth;
        }
        return 1 + min(leftdepth, rightdepth);
    }
};

// 迭代法实现，最小深度
class Solution_Iterative {
public:
    int minDepth(TreeNode* root) {
        if (root == NULL) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            depth++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                // 如果是叶子节点，直接返回当前深度
                if (node->left == NULL && node->right == NULL) {
                    return depth;
                }
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return depth;
    }
};

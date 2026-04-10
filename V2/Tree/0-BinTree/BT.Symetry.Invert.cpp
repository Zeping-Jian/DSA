
//
// Created by 菅泽平 on 2025/10/25.
//
#include <vector>
#include <queue>
using namespace std;

/**
 * 二叉树节点定义
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


// reverse or invert binary tree
// 反转二叉树 - 递归法
class Solution_recursive {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        // root->left = right;
        // root->right = left;
        swap(root->left, root->right);
        // 自底向上 的执行交换 反转
        return root;
    }

     TreeNode* invertTree2(TreeNode* root) {
        if (root == nullptr) return nullptr;
        // 自顶向上实现交换 反转
        swap(root->left, root->right);
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        return root;
    }
};

// 反转二叉树 - 迭代法
class Solution_iterative {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            swap(current->left, current->right);
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return root;
    }
};

// 写一个测试点
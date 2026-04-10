#include <iostream>
#include <vector>
#include <queue>
#include <deque>

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

/**
 * 关键算法思想
数据结构：使用队列（Queue）实现BFS
核心原理：队列的FIFO特性保证层序访问
时间复杂度：O(n) - 每个节点访问一次
空间复杂度：O(w) - w是树的最大宽度
 */

class BinaryTreeLevelOrder {
public:
    /**
     * 方法1：基本层序遍历 - 使用队列
     * 时间复杂度：O(n)
     * 空间复杂度：O(w) 其中w是树的最大宽度
     */
    static vector<int> levelOrder(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            
            // 访问当前节点
            result.push_back(current->val);
            
            // 将子节点加入队列
            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        
        return result;
    }
    
    /**
     * 方法2：分层级的层序遍历 - 每一层单独输出
     * 返回二维数组，每个子数组代表一层
     */
    static vector<vector<int>> levelOrderByLevels(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size(); // 当前层的节点数量
            vector<int> currentLevel;
            
            // 处理当前层的所有节点
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = q.front();
                q.pop();
                
                currentLevel.push_back(current->val);
                
                // 将下一层的节点加入队列
                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
            
            result.push_back(currentLevel);
        }
        
        return result;
    }
    
    /**
     * 方法3：从右到左的层序遍历
     */
    static vector<vector<int>> levelOrderRightToLeft(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = q.front();
                q.pop();
                
                currentLevel.push_back(current->val);
                
                // 注意：先右后左，这样输出时就是从右到左
                if (current->right) {
                    q.push(current->right);
                }
                if (current->left) {
                    q.push(current->left);
                }
            }
            
            result.push_back(currentLevel);
        }
        
        return result;
    }
    
    /**
     * 方法4：自底向上的层序遍历
     */
    static vector<vector<int>> levelOrderBottomUp(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = q.front();
                q.pop();
                
                currentLevel.push_back(current->val);
                
                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
            
            result.push_back(currentLevel);
        }
        
        // 反转结果，实现自底向上
        reverse(result.begin(), result.end());
        return result;
    }
    
    /**
     * 方法5：之字形（锯齿状）层序遍历
     * 奇数层从左到右，偶数层从右到左
     */
    static vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true; // 标记当前层的遍历方向
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel(levelSize);
            
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = q.front();
                q.pop();
                
                // 根据方向决定放置位置
                int index = leftToRight ? i : (levelSize - 1 - i);
                currentLevel[index] = current->val;
                
                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
            
            leftToRight = !leftToRight; // 切换方向
            result.push_back(currentLevel);
        }
        
        return result;
    }
    
    /**
     * 方法6：使用双端队列实现之字形遍历（另一种实现）
     */
    static vector<vector<int>> zigzagLevelOrderDeque(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        deque<TreeNode*> dq;
        dq.push_back(root);
        bool leftToRight = true;
        
        while (!dq.empty()) {
            int levelSize = dq.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; ++i) {
                if (leftToRight) {
                    TreeNode* current = dq.front();
                    dq.pop_front();
                    currentLevel.push_back(current->val);
                    
                    if (current->left) dq.push_back(current->left);
                    if (current->right) dq.push_back(current->right);
                } else {
                    TreeNode* current = dq.back();
                    dq.pop_back();
                    currentLevel.push_back(current->val);
                    
                    if (current->right) dq.push_front(current->right);
                    if (current->left) dq.push_front(current->left);
                }
            }
            
            leftToRight = !leftToRight;
            result.push_back(currentLevel);
        }
        
        return result;
    }
};

// 辅助函数：创建测试用的二叉树
TreeNode* createSampleTree() {
    /*
     * 创建如下二叉树：
     *       3
     *      / \
     *     9   20
     *        /  \
     *       15   7
     */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    return root;
}

// 创建更复杂的测试树
TreeNode* createComplexTree() {
    /*
     * 创建如下二叉树：
     *         1
     *       /   \
     *      2     3
     *     / \   / \
     *    4   5 6   7
     *   /
     *  8
     */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->left->left->left = new TreeNode(8);
    
    return root;
}

// 打印一维结果
void printResult(const vector<int>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// 打印二维结果
void printResult2D(const vector<vector<int>>& result) {
    cout << "[" << endl;
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "  [";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
        cout << endl;
    }
    cout << "]" << endl;
}

// 清理内存
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void runTests() {
    cout << "=== 二叉树层序遍历测试 ===" << endl << endl;
    
    // 测试简单树
    TreeNode* tree1 = createSampleTree();
    cout << "测试树1结构:" << endl;
    cout << "    3" << endl;
    cout << "   / \\" << endl;
    cout << "  9   20" << endl;
    cout << "     /  \\" << endl;
    cout << "    15   7" << endl << endl;
    
    cout << "1. 基本层序遍历: ";
    auto result1 = BinaryTreeLevelOrder::levelOrder(tree1);
    printResult(result1);
    
    cout << "2. 分层级层序遍历:" << endl;
    auto result2 = BinaryTreeLevelOrder::levelOrderByLevels(tree1);
    printResult2D(result2);
    
    cout << "3. 自底向上层序遍历:" << endl;
    auto result3 = BinaryTreeLevelOrder::levelOrderBottomUp(tree1);
    printResult2D(result3);
    
    cout << "4. 之字形层序遍历:" << endl;
    auto result4 = BinaryTreeLevelOrder::zigzagLevelOrder(tree1);
    printResult2D(result4);
    
    deleteTree(tree1);
    
    cout << "\n" << string(50, '=') << endl;
    
    // 测试复杂树
    TreeNode* tree2 = createComplexTree();
    cout << "测试树2结构:" << endl;
    cout << "      1" << endl;
    cout << "    /   \\" << endl;
    cout << "   2     3" << endl;
    cout << "  / \\   / \\" << endl;
    cout << " 4   5 6   7" << endl;
    cout << "/" << endl;
    cout << "8" << endl << endl;
    
    cout << "1. 基本层序遍历: ";
    auto complex1 = BinaryTreeLevelOrder::levelOrder(tree2);
    printResult(complex1);
    
    cout << "2. 分层级层序遍历:" << endl;
    auto complex2 = BinaryTreeLevelOrder::levelOrderByLevels(tree2);
    printResult2D(complex2);
    
    cout << "3. 之字形层序遍历:" << endl;
    auto complex3 = BinaryTreeLevelOrder::zigzagLevelOrder(tree2);
    printResult2D(complex3);
    
    cout << "4. 使用双端队列的之字形遍历:" << endl;
    auto complex4 = BinaryTreeLevelOrder::zigzagLevelOrderDeque(tree2);
    printResult2D(complex4);
    
    deleteTree(tree2);
}

void algorithmAnalysis() {
    cout << "\n=== 算法分析 ===" << endl;
    
    cout << "核心思想:" << endl;
    cout << "- 使用队列(Queue)数据结构实现广度优先搜索(BFS)" << endl;
    cout << "- 队列的FIFO特性保证了层序访问顺序" << endl << endl;
    
    cout << "基本步骤:" << endl;
    cout << "1. 将根节点加入队列" << endl;
    cout << "2. 循环直到队列为空:" << endl;
    cout << "   a) 取出队列头部节点并访问" << endl;
    cout << "   b) 将该节点的左右子节点加入队列尾部" << endl << endl;
    
    cout << "复杂度分析:" << endl;
    cout << "- 时间复杂度: O(n) - 每个节点访问一次" << endl;
    cout << "- 空间复杂度: O(w) - w是树的最大宽度" << endl;
    cout << "  * 完全二叉树的最大宽度约为 n/2" << endl;
    cout << "  * 最坏情况下空间复杂度为 O(n)" << endl << endl;
    
    cout << "变种算法特点:" << endl;
    cout << "1. 分层遍历: 记录每层节点数量，分别处理每层" << endl;
    cout << "2. 之字形遍历: 交替改变每层的输出顺序" << endl;
    cout << "3. 自底向上: 先正常遍历，最后反转结果" << endl;
    cout << "4. 从右到左: 改变子节点加入队列的顺序" << endl;
}

int main() {
    cout << "二叉树层序遍历实现与分析" << endl;
    cout << string(50, '=') << endl;
    
    runTests();
    algorithmAnalysis();
    
    cout << "\n总结:" << endl;
    cout << "层序遍历是二叉树的基本遍历方式之一，" << endl;
    cout << "通过队列数据结构可以优雅地实现BFS算法。" << endl;
    cout << "在实际应用中常用于:" << endl;
    cout << "- 寻找二叉树的最小深度" << endl;
    cout << "- 判断是否为完全二叉树" << endl;
    cout << "- 二叉树的序列化和反序列化" << endl;
    cout << "- 求二叉树每层的平均值等问题" << endl;
    
    return 0;
}

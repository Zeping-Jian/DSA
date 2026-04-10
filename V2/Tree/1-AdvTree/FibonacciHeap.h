//
// Created by 菅泽平 on 2025/5/23.
//

#ifndef DSA_FIBONACCIHEAP_H
#define DSA_FIBONACCIHEAP_H

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

template <typename T>
class FibonacciHeap {
private:
    struct Node {
        T key;
        int degree = 0;
        bool marked = false;
        Node* parent = nullptr;
        Node* child = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        explicit Node(T k) : key(k) {
            left = this;
            right = this;
        }
    };

    Node* minNode = nullptr;
    int size = 0;
    std::unordered_map<T, Node*> nodeMap;  // 用于快速查找节点

    // 合并两个循环双向链表
    void mergeLists(Node* a, Node* b) {
        if (!a || !b) return;

        Node* aRight = a->right;
        Node* bLeft = b->left;

        a->right = b;
        b->left = a;
        aRight->left = bLeft;
        bLeft->right = aRight;
    }

    // 链接两个堆：使较大根成为较小根的子节点
    void link(Node* child, Node* parent) {
        // 从根列表中移除child
        child->left->right = child->right;
        child->right->left = child->left;

        // 使child成为parent的子节点
        child->parent = parent;
        parent->degree++;

        if (!parent->child) {
            parent->child = child;
            child->left = child;
            child->right = child;
        } else {
            mergeLists(parent->child, child);
        }

        child->marked = false;
    }

    // 合并相同度数的树
    void consolidate() {
        int maxDegree = static_cast<int>(log2(size)) + 1;
        std::vector<Node*> degreeTable(maxDegree, nullptr);

        Node* current = minNode;
        std::vector<Node*> nodesToProcess;

        // 收集所有根节点
        do {
            nodesToProcess.push_back(current);
            current = current->right;
        } while (current != minNode);

        for (Node* node : nodesToProcess) {
            int degree = node->degree;

            while (degreeTable[degree] != nullptr) {
                Node* other = degreeTable[degree];

                if (node->key > other->key) {
                    std::swap(node, other);
                }

                link(other, node);
                degreeTable[degree] = nullptr;
                degree++;

                if (degree >= degreeTable.size()) {
                    degreeTable.push_back(nullptr);
                }
            }

            degreeTable[degree] = node;
        }

        // 重建根列表并找到新的minNode
        minNode = nullptr;
        for (Node* node : degreeTable) {
            if (node != nullptr) {
                if (!minNode) {
                    minNode = node;
                    minNode->left = minNode;
                    minNode->right = minNode;
                } else {
                    mergeLists(minNode, node);
                    if (node->key < minNode->key) {
                        minNode = node;
                    }
                }
            }
        }
    }

    // 切断节点与父节点的连接，并将其加入根列表
    void cut(Node* child, Node* parent) {
        // 从父节点的子列表中移除child
        if (child->right == child) {
            parent->child = nullptr;
        } else {
            child->right->left = child->left;
            child->left->right = child->right;
            if (parent->child == child) {
                parent->child = child->right;
            }
        }

        parent->degree--;

        // 将child加入根列表
        child->parent = nullptr;
        child->marked = false;
        mergeLists(minNode, child);
    }

    // 级联切断：递归检查父节点是否需要被切断
    void cascadingCut(Node* node) {
        Node* parent = node->parent;
        if (parent) {
            if (!node->marked) {
                node->marked = true;
            } else {
                cut(node, parent);
                cascadingCut(parent);
            }
        }
    }

public:
    ~FibonacciHeap() {
        if (minNode) {
            std::vector<Node*> nodesToDelete;
            Node* current = minNode;

            do {
                nodesToDelete.push_back(current);
                current = current->right;
            } while (current != minNode);

            for (Node* node : nodesToDelete) {
                deleteSubtree(node);
            }
        }
    }

    void deleteSubtree(Node* node) {
        if (!node) return;

        Node* child = node->child;
        if (child) {
            Node* current = child;
            do {
                Node* next = current->right;
                deleteSubtree(current);
                current = next;
            } while (current != child);
        }

        delete node;
    }

    // 插入新元素
    void insert(T key) {
        Node* newNode = new Node(key);
        nodeMap[key] = newNode;

        if (!minNode) {
            minNode = newNode;
        } else {
            mergeLists(minNode, newNode);
            if (key < minNode->key) {
                minNode = newNode;
            }
        }
        size++;
    }

    // 查看最小元素
    T findMin() const {
        if (!minNode) {
            throw std::runtime_error("Heap is empty");
        }
        return minNode->key;
    }

    // 合并两个斐波那契堆
    void merge(FibonacciHeap& other) {
        if (!other.minNode) return;

        if (!minNode) {
            minNode = other.minNode;
        } else {
            mergeLists(minNode, other.minNode);
            if (other.minNode->key < minNode->key) {
                minNode = other.minNode;
            }
        }

        size += other.size;
        other.minNode = nullptr;
        other.size = 0;
    }

    // 提取最小元素
    T extractMin() {
        if (!minNode) {
            throw std::runtime_error("Heap is empty");
        }

        Node* extractedMin = minNode;
        T minKey = extractedMin->key;
        nodeMap.erase(minKey);

        // 将最小节点的所有子节点加入根列表
        if (extractedMin->child) {
            Node* child = extractedMin->child;
            do {
                Node* nextChild = child->right;
                child->parent = nullptr;
                mergeLists(minNode, child);
                child = nextChild;
            } while (child != extractedMin->child);
        }

        // 从根列表中移除最小节点
        if (extractedMin->right == extractedMin) {
            minNode = nullptr;
        } else {
            minNode = extractedMin->right;
            extractedMin->left->right = extractedMin->right;
            extractedMin->right->left = extractedMin->left;
            consolidate();
        }

        delete extractedMin;
        size--;
        return minKey;
    }

    // 降低键值
    void decreaseKey(T oldKey, T newKey) {
        if (newKey > oldKey) {
            throw std::runtime_error("New key is greater than current key");
        }

        auto it = nodeMap.find(oldKey);
        if (it == nodeMap.end()) {
            throw std::runtime_error("Key not found");
        }

        Node* node = it->second;
        node->key = newKey;
        nodeMap.erase(oldKey);
        nodeMap[newKey] = node;

        Node* parent = node->parent;

        if (parent && node->key < parent->key) {
            cut(node, parent);
            cascadingCut(parent);
        }

        if (node->key < minNode->key) {
            minNode = node;
        }
    }

    // 删除元素
    void remove(T key) {
        decreaseKey(key, std::numeric_limits<T>::min());
        extractMin();
    }

    // 检查堆是否为空
    bool isEmpty() const {
        return size == 0;
    }

    // 获取堆的大小
    int getSize() const {
        return size;
    }
};

#endif //DSA_FIBONACCIHEAP_H

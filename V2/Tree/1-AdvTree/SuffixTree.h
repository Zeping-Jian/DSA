//
// Created by 菅泽平 on 2025/5/23.
//

#ifndef DSA_SUFFIXTREE_H
#define DSA_SUFFIXTREE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

class SuffixTree {
private:
    struct Node {
        int start; // 边起始索引
        int* end;  // 边结束索引指针（便于全局更新）
        Node* suffixLink; // 后缀链接
        std::unordered_map<char, Node*> children; // 子节点

        Node(int start, int* end) : start(start), end(end), suffixLink(nullptr) {}

        int edgeLength(int currentPos) {
            return std::min(*end, currentPos + 1) - start;
        }
    };

    Node* root;
    Node* activeNode;
    int activeEdge;
    int activeLength;
    int remainingSuffixCount;
    int leafEnd;
    std::string text;
    std::vector<int> suffixArray;

    Node* lastNewNode;
    int* rootEnd;
    int* splitEnd;

    // 创建新节点
    Node* newNode(int start, int* end) {
        Node* node = new Node(start, end);
        return node;
    }

    // 获取活动边的字符
    char activeEdgeChar() {
        return text[activeEdge];
    }

    // 向下走一步
    bool walkDown(Node* currNode) {
        if (activeLength >= currNode->edgeLength(leafEnd)) {
            activeEdge += currNode->edgeLength(leafEnd);
            activeLength -= currNode->edgeLength(leafEnd);
            activeNode = currNode;
            return true;
        }
        return false;
    }

    // 扩展规则3：当前字符已存在
    void extendSuffixTree(int pos) {
        leafEnd = pos;
        remainingSuffixCount++;
        lastNewNode = nullptr;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0) {
                activeEdge = pos;
            }

            auto it = activeNode->children.find(activeEdgeChar());
            Node* next = (it == activeNode->children.end()) ? nullptr : it->second;

            if (!next) { // 规则2：创建新叶节点
                activeNode->children[activeEdgeChar()] = newNode(pos, &leafEnd);

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
            } else { // 规则3处理
                if (walkDown(next)) continue;

                if (text[next->start + activeLength] == text[pos]) { // 规则3
                    if (lastNewNode != nullptr && activeNode != root) {
                        lastNewNode->suffixLink = activeNode;
                        lastNewNode = nullptr;
                    }
                    activeLength++;
                    break;
                }

                // 规则2：分裂节点
                splitEnd = new int;
                *splitEnd = next->start + activeLength - 1;

                Node* split = newNode(next->start, splitEnd);
                activeNode->children[activeEdgeChar()] = split;

                split->children[text[pos]] = newNode(pos, &leafEnd);
                next->start += activeLength;
                split->children[text[next->start]] = next;

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = split;
                }

                lastNewNode = split;
            }

            remainingSuffixCount--;

            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            } else if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }

    // 递归释放内存
    void freeSuffixTree(Node* node) {
        if (!node) return;

        for (auto& child : node->children) {
            freeSuffixTree(child.second);
        }

        if (node->end != &leafEnd) {
            delete node->end;
        }
        delete node;
    }

    // 构建后缀数组
    void buildSuffixArray(Node* node, int pathLen) {
        if (!node) return;

        bool isLeaf = true;
        for (auto& child : node->children) {
            isLeaf = false;
            int edgeLen = child.second->edgeLength(leafEnd);
            buildSuffixArray(child.second, pathLen + edgeLen);
        }

        if (isLeaf) {
            suffixArray.push_back(text.size() - pathLen);
        }
    }

public:
    SuffixTree(const std::string& input) : text(input) {
        rootEnd = new int(-1);
        root = newNode(-1, rootEnd);
        activeNode = root;
        activeEdge = -1;
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = -1;

        // 构建后缀树
        for (int i = 0; i < text.size(); i++) {
            extendSuffixTree(i);
        }

        // 构建后缀数组
        buildSuffixArray(root, 0);
        std::sort(suffixArray.begin(), suffixArray.end());
    }

    ~SuffixTree() {
        freeSuffixTree(root);
        delete rootEnd;
    }

    // 检查是否包含子串
    bool contains(const std::string& pattern) {
        Node* curr = root;
        int patternPos = 0;

        while (patternPos < pattern.size()) {
            auto it = curr->children.find(pattern[patternPos]);
            if (it == curr->children.end()) return false;

            Node* child = it->second;
            int edgeLen = child->edgeLength(leafEnd);

            for (int i = 0; i < edgeLen && patternPos < pattern.size(); i++) {
                if (text[child->start + i] != pattern[patternPos++]) {
                    return false;
                }
            }

            if (patternPos == pattern.size()) return true;
            curr = child;
        }

        return false;
    }

    // 获取所有出现位置
    std::vector<int> getAllOccurrences(const std::string& pattern) {
        std::vector<int> occurrences;
        Node* curr = root;
        int patternPos = 0;
        int matchLen = 0;

        // 查找模式对应的节点
        while (patternPos < pattern.size()) {
            auto it = curr->children.find(pattern[patternPos]);
            if (it == curr->children.end()) return occurrences;

            Node* child = it->second;
            int edgeLen = child->edgeLength(leafEnd);
            matchLen += edgeLen;

            for (int i = 0; i < edgeLen && patternPos < pattern.size(); i++) {
                if (text[child->start + i] != pattern[patternPos++]) {
                    return occurrences;
                }
            }

            curr = child;
        }

        // 收集所有叶节点位置
        std::vector<Node*> stack = {curr};
        while (!stack.empty()) {
            Node* node = stack.back();
            stack.pop_back();

            if (node->children.empty()) { // 叶节点
                occurrences.push_back(text.size() - (matchLen - node->edgeLength(leafEnd)));
            } else {
                for (auto& child : node->children) {
                    stack.push_back(child.second);
                }
            }
        }

        std::sort(occurrences.begin(), occurrences.end());
        return occurrences;
    }

    // 获取后缀数组
    const std::vector<int>& getSuffixArray() const {
        return suffixArray;
    }

    // 打印树结构（调试用）
    void printTree(Node* node = nullptr, int depth = 0) {
        if (!node) node = root;

        for (auto& child : node->children) {
            std::cout << std::string(depth * 2, ' ') << "["
                      << child.second->start << ", "
                      << *child.second->end << "] "
                      << text.substr(child.second->start,
                                     child.second->edgeLength(leafEnd))
                      << std::endl;
            printTree(child.second, depth + 1);
        }
    }
};

#endif //DSA_SUFFIXTREE_H

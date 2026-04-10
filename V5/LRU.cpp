

//
// Created by 菅泽平 on 2025/10/27.
//

#include <unordered_map>
using namespace std;

//  LRU 的简单实现
struct LinkedNode {
    int key;
    int value;
    LinkedNode* prev;
    LinkedNode* next;
    
    LinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    LinkedNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    LinkedNode* head;  // 虚拟头节点
    LinkedNode* tail;  // 虚拟尾节点
    unordered_map<int, LinkedNode*> map;  // 哈希表存储 key 到节点的映射
    
    // 辅助函数：在head后添加节点
    void addToHead(LinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    // 辅助函数：删除节点
    void removeNode(LinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    // 辅助函数：移动节点到头部
    void moveToHead(LinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }
    
    // 辅助函数：删除尾部节点
    LinkedNode* removeTail() {
        LinkedNode* lastNode = tail->prev;
        removeNode(lastNode);
        return lastNode;
    }
    
public:
    LRUCache(int capacity) : capacity(capacity) {
        // 创建虚拟头尾节点
        head = new LinkedNode();
        tail = new LinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) {
            return -1;  // 不存在
        }
        
        // 移动到链表头部（最近使用）
        LinkedNode* node = it->second;
        moveToHead(node);
        
        return node->value;
    }
    
    void put(int key, int value) {
        auto it = map.find(key);
        
        if (it != map.end()) {
            // 已存在，更新值并移到头部
            LinkedNode* node = it->second;
            node->value = value;
            moveToHead(node);
        } else {
            LinkedNode* newNode = new LinkedNode(key, value);
            
            if (map.size() >= capacity) {
                // 缓存满了，删除最久未使用的（链表尾部）
                LinkedNode* tail = removeTail();
                map.erase(tail->key);
                delete tail;
            }
            
            // 插入到头部
            addToHead(newNode);
            map[key] = newNode;
        }
    }
};
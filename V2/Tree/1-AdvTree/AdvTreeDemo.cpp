//
// Created by 菅泽平 on 2025/5/23.
//

#include "EVBTree.h"
#include "FibonacciHeap.h"

int testEVBTree() {
    VEBTree veb(16);  // 创建全域大小为16的vEB树

    // 插入元素
    veb.insert(2);
    veb.insert(3);
    veb.insert(4);
    veb.insert(5);
    veb.insert(7);
    veb.insert(14);
    veb.insert(15);

    // 测试查找
    std::cout << "Contains 5: " << veb.contains(5) << std::endl;  // 输出1 (true)
    std::cout << "Contains 6: " << veb.contains(6) << std::endl;  // 输出0 (false)

    // 测试前驱后继
    std::cout << "Successor of 5: " << veb.successor(5) << std::endl;  // 输出7
    std::cout << "Predecessor of 5: " << veb.predecessor(5) << std::endl;  // 输出4
    std::cout << "Successor of 7: " << veb.successor(7) << std::endl;  // 输出14
    std::cout << "Predecessor of 14: " << veb.predecessor(14) << std::endl;  // 输出7

    // 测试删除
    veb.remove(5);
    std::cout << "Contains 5 after deletion: " << veb.contains(5) << std::endl;  // 输出0 (false)
    std::cout << "Successor of 4 after deletion: " << veb.successor(4) << std::endl;  // 输出7

    // 测试最小最大值
    std::cout << "Min: " << veb.getMin() << std::endl;  // 输出2
    std::cout << "Max: " << veb.getMax() << std::endl;  // 输出15

    return 0;
}

int testFibHeap() {
    FibonacciHeap<int> fibHeap;

    // 插入元素
    fibHeap.insert(7);
    fibHeap.insert(3);
    fibHeap.insert(17);
    fibHeap.insert(24);

    std::cout << "Min: " << fibHeap.findMin() << std::endl;  // 输出 3

    // 提取最小值
    std::cout << "Extracted: " << fibHeap.extractMin() << std::endl;  // 输出 3
    std::cout << "New Min: " << fibHeap.findMin() << std::endl;  // 输出 7

    // 降低键值
    fibHeap.decreaseKey(24, 2);
    std::cout << "New Min after decreaseKey: " << fibHeap.findMin() << std::endl;  // 输出 2

    // 删除元素
    fibHeap.remove(17);
    std::cout << "Min after remove: " << fibHeap.findMin() << std::endl;  // 输出 2

    return 0;
}

#include "SuffixArray_Radix.h"

int main() {

    // testFibHeap();

    testSuffixArray_Radix();

    return 0;
}
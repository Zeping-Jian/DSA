//
// Created by 菅泽平 on 2025/6/7.
//



#include <iostream>
#include <set>
#include <vector>

int main() {
    // 示例1: 直接使用std::set存储数据
    std::set<int> uniqueSortSet;

    // 插入一些数据(包含重复项)
    uniqueSortSet.insert(5);
    uniqueSortSet.insert(2);
    uniqueSortSet.insert(8);
    uniqueSortSet.insert(2);  // 重复项不会被插入
    uniqueSortSet.insert(5);  // 重复项不会被插入
    uniqueSortSet.insert(1);

    // 输出结果(自动排序且去重)
    std::cout << "直接使用set存储的结果:\n";
    for (int num : uniqueSortSet) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";




    // 示例2: 将现有vector转换为set来去重排序
    std::vector<int> numbers = {7, 3, 5, 3, 9, 1, 7, 5, 2};

    std::set<int> uniqueSortSet2(numbers.begin(), numbers.end());

    std::cout << "vector转换为set后的结果:\n";
    for (int num : uniqueSortSet2) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // 示例3: 降序排列
    std::set<int, std::greater<int>> descending_set;
    descending_set.insert(numbers.begin(), numbers.end());

    std::cout << "降序排列的结果:\n";
    for (int num : descending_set) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}

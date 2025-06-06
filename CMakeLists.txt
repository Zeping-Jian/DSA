cmake_minimum_required(VERSION 3.31)
project(DSA)

set(CMAKE_CXX_STANDARD 20)

add_executable(DSA main.cpp)

# 添加子模块-子目录
add_subdirectory(Tree)
add_subdirectory(Graph_RS)
add_subdirectory(Graph)

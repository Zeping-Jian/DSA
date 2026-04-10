

include_directories(. ch17 ch18 ch19 first_half)


add_executable(GraphRSDemo main.cc)

add_executable(GraphRSDemo_1 first_half/main.cpp first_half/process_mem_usage.cc)

add_executable(GraphRSDemo_17_6 first_half/main_17-6.cpp )

#add_executable(TreeDemo TreeDemo.cpp)
message("Module Graph RS")
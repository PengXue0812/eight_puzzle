cmake_minimum_required(VERSION 3.23)
project(eight_puzzle)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp)
# 从dll中导入库psapi.lib
target_link_libraries(main psapi)

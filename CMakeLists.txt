cmake_minimum_required(VERSION 3.14)
project(algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(algorithms main.cpp graph.cpp test_runner.cpp two_three_tree.cpp node.cpp tests.cpp)
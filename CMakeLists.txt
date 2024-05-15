cmake_minimum_required(VERSION 3.27)
project(cpp_Ex2)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_Ex2 main.cpp
        Algorithms.cpp
        DetectCycle.cpp
        DetectNegativeCycle.cpp
        doctest.h
        Graph.cpp
        IsBipartite.cpp
        IsConnected.cpp
        ShortestPath.cpp
        Test.cpp
        TestCounter.cpp)

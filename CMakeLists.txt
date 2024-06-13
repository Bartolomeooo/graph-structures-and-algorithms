cmake_minimum_required(VERSION 3.26)
project(graph-structures-and-algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(aizo_graphs main.cpp
        Array/array.h
        Array/array.cpp
        IncidenceMatrixGraph/GraphIM.cpp
        AdjacencyListGraph/GraphAL.cpp
        MST/MST.h
        MST/MST.cpp
        ShortestPath/SP.h
        ShortestPath/SP.cpp
        UnionFind/unionFind.h
        UnionFind/unionFind.cpp
        PriorityQueue/queue.h
        PriorityQueue/queue.cpp
)

target_include_directories(aizo_graphs PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Array
        ${CMAKE_CURRENT_SOURCE_DIR}/AdjacencyListGraph
        ${CMAKE_CURRENT_SOURCE_DIR}/Dijkstra
        ${CMAKE_CURRENT_SOURCE_DIR}/IncidenceMatrixGraph
        ${CMAKE_CURRENT_SOURCE_DIR}/Menu
        ${CMAKE_CURRENT_SOURCE_DIR}/PriorityQueue
        ${CMAKE_CURRENT_SOURCE_DIR}/ShortestPath
        ${CMAKE_CURRENT_SOURCE_DIR}/Timer
        ${CMAKE_CURRENT_SOURCE_DIR}/MST
        ${CMAKE_CURRENT_SOURCE_DIR}/UnionFind
)

set(CMAKE_EXE_LINKER_FLAGS "-static")
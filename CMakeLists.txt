cmake_minimum_required(VERSION 3.27)
project(graphAlgorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(graphAlgorithms main.cpp
        Sources/Menu.cpp
        Sources/Graph.cpp
        Sources/Utilities.cpp
)

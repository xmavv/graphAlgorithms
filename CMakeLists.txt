cmake_minimum_required(VERSION 3.27)
project(graphAlgorithms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(graphAlgorithms main.cpp
        Sources/Menu.cpp
        Sources/Graph.cpp
        Sources/Utilities.cpp
)

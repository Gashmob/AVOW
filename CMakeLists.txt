cmake_minimum_required(VERSION 3.23)
project(AVOW)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        src
        src/utils
        src/algorithms
)

add_executable(AVOW
        src/main.cpp
        src/algorithms/Algorithm.hpp
        src/utils/cxxopts.hpp)

cmake_minimum_required(VERSION 3.10)
project(AVOW)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)

add_executable(avow
        src/main.cpp
        src/VERSION.h
        src/algorithm/Algorithm.hpp
        src/algorithm/algorithms.hpp
        src/utils/cxxopts.hpp
        src/utils/stb_image.h src/utils/stb_image_write.h
        src/utils/Image.hpp
        src/utils/tools.hpp
        src/utils/enquirer.hpp
        src/algorithm/algos/Blank.hpp)

target_include_directories(avow PUBLIC
        src
        src/utils
        src/algorithm
        src/algorithm/algos
        )

target_link_libraries(avow jsoncpp_lib)
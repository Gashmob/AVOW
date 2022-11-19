cmake_minimum_required(VERSION 3.23)
project(AVOW)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)

add_executable(avow
        src/main.cpp
        src/VERSION.h
        src/algorithms/Algorithm.hpp
        src/algorithms/algorithms.hpp
        src/utils/cxxopts.hpp
        src/utils/stb_image.h src/utils/stb_image_write.h
        src/utils/Image.hpp
        src/utils/tools.hpp
        src/utils/enquirer.hpp
        )

target_include_directories(avow PUBLIC
        src
        src/utils
        src/algorithms
        )

target_link_libraries(avow jsoncpp_lib)
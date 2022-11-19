cmake_minimum_required(VERSION 3.23)
project(AVOW)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)

include_directories(
        src
        src/utils
        src/algorithms
)

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

target_link_libraries(avow jsoncpp_lib)
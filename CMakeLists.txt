cmake_minimum_required(VERSION 3.10)
project(AVOW)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)

add_executable(avow
        src/main.cpp
        src/VERSION.h
        src/algorithm/Algorithm.hpp
        src/algorithm/algorithms.hpp
        src/include/cxxopts.hpp
        src/include/stb_image.h src/include/stb_image_write.h
        src/include/enquirer.hpp
        src/utils/Image.hpp
        src/utils/tools.hpp src/utils/data.hpp

        src/algorithm/algos/Blank.hpp
        src/algorithm/algos/Color.hpp
        src/algorithm/algos/Noise.hpp src/algorithm/algos/Noise/Perlin.hpp
        src/algorithm/algos/Random.hpp)

target_include_directories(avow PUBLIC
        src
        src/include
        src/utils
        src/algorithm
        src/algorithm/algos
        )

target_link_libraries(avow jsoncpp_lib)

install(TARGETS avow DESTINATION bin)
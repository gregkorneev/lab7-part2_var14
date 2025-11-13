cmake_minimum_required(VERSION 3.16)
project(lab7_part2_var14 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(app
    src/main.cpp
    src/lis_dp.cpp
    src/lis_bruteforce.cpp
    src/utils.cpp
)

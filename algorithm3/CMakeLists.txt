cmake_minimum_required(VERSION 3.5)
project(algorithm3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp)

add_executable(algorithm3 ${SOURCE_FILES})
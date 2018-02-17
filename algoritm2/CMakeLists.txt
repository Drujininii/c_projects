cmake_minimum_required(VERSION 3.5)
project(algoritm2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    CMakeLists.txt
    main.cpp)

add_executable(algoritm2 ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.5)
project(C__3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(C__3 ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(C__3 ${OpenCV_LIBS})
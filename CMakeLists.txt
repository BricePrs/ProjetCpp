cmake_minimum_required(VERSION 3.24)
project(TP_PERESB_HASSANH)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(test)
file(GLOB SRC "src/*cpp")


add_executable(lab2 ${SRC} test/test_lab2.cpp)

cmake_minimum_required(VERSION 3.17)
project(interpreter-pattern-test)

set(CMAKE_CXX_STANDARD 17)

add_executable(test catch.hpp catchMain.cpp tests.cpp Expression.cpp Expression.hpp)
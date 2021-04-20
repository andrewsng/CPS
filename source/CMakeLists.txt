
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project ("cps")

add_executable (cps-output main.cpp Shape.hpp Shape.cpp CompoundShape.hpp CompoundShape.cpp CPS.hpp CPS.cpp)
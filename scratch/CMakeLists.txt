
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project ("cps-scratch")

add_executable (cps-scratch  main.cpp Point.hpp BoundingBox.hpp  Shape.hpp Shape.cpp  )
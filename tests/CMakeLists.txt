
cmake_minimum_required (VERSION 3.8)

project ("cps-tests")

add_executable (unit-tests  main.cpp catch.hpp postscript_output.cpp Shape.hpp Shape.cpp)
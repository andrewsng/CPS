
cmake_minimum_required (VERSION 3.8)

project ("cps-tests")

include_directories("../source")
file(GLOB SOURCES "../source/Shape.*")

add_executable (unit-tests catch_main.cpp catch.hpp postscript_output.cpp ${SOURCES})
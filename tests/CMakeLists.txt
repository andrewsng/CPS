
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project ("cps-tests")

include_directories("../source")
file(GLOB SOURCES ../source/Shape.* ../source/CPS.*)

add_executable (unit-tests unit_tests_main.cpp catch.hpp unit_tests_ctors.cpp unit_tests_output.cpp ${SOURCES})

add_executable (visual-tests visual_output_main.cpp ${SOURCES})
# CPS
A C++ to Postscript conversion project.

# Shape Classes

Shape.hpp contains
	A virtual class base which contains a height weight and toPostScript functions 
	Multiple shape classes with constructors and toPostScript functions based off of the main virtual shape class
	Multiple compound shape classes that reference the shape classes using pointers 
	Shared pointers to each of the classes

Shape.cpp contains
	toPostScript functions and constructor functions for the different shape and compound shapes

# Tests

unit_tests_ctors.cpp
	Tests inputs for each constructor class to account for each of the classes to check for impossible input parameters
	such as negative numbers and impossible shapes

unit_tests_output.cpp
	Tests for the amount of certain functions are called into the .ps code such (eg triangles only having 2 "rline") 

# Visual Output

visual_output_main.cpp
	creates .ps code outputs or each of the classes 
# CPS
A C++ to Postscript conversion project.

Development tasks and progress can be seen on the [Project Tasks](https://github.com/uaf372/CPS/projects/1) Kanban board.

# Shape Classes

Shape.hpp contains
	A virtual class base which contains a height weight and toPostScript funtions 
	Multiple shape classes with constructors and toPostScript funtions based off of the main vitual shape class
	Multiple compound shape classes that reference the shape classes using pointers 
	Shareed pointers to each of the classes

Shape.cpp contains
	toPostScript funtions and constructor funcitons for the different shape and compound shapes

# Tests

unit_tests_ctors.cpp
	Tests inputs for each constructor class to account for each of the classes to check for impossible input parameters
	such as negative numbers and impossible shapes

unit_tests_output.cpp
	Tests for the amount of certain functions are called into the .ps code such (eg triangles only having 2 "rline") 

# Visual Output

visual_output_main.cpp
	creates .ps code outputs or each of the classes 
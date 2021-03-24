# CPS
A C++ to Postscript conversion project.

## Source Directory

Shape.hpp / Shape.cpp

  * A virtual base class which contains the height, width and ToPostScript function declarations
  * Multiple derived basic shape classes
  * Multiple compound shape classes
  * Helper functions for generating smart pointers to shape objects
  * Detailed implementation of constructors and ToPostScript functions

CPS.hpp / CPS.cpp contains

  * Definition of function for writing PostScript files

main.cpp

  * Demonstration of generation of several output files using the shape language

Visuals Directory

  * Generated PostScript and converted PDF files of shape output from main.cpp


## Tests Directory

Unit Tests

  * Testing of constructors and properties using Catch2
  * Primitive testing of ToPostScript() output strings (see testing README for details)

Visual Tests

  * Regularly regenerated and tested .ps output form visual_output_main.cpp (see testing README for details)

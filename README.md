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
  * Primitive testing of ToPostScript() output strings (see testing [README](https://github.com/uaf372/CPS/tree/main/tests) for details)

Visual Tests

  * Regularly regenerated and tested .ps output form visual_output_main.cpp (see testing [README](https://github.com/uaf372/CPS/tree/main/tests) for details)


## Critique

Translation

  * Currently, positioning shapes to be drawn in specific places is a difficult task to get right, requiring use of Horizontal, Vertical, and Spacer shapes.
  * An actual TranslatedShape derived class might be a solution, and would go nicely with the ScaledShape and RotatedShape. However, there are potential issues
    with maintaining their bounding boxes, as well as determining how they interact when placed in compound shapes. Maybe a good practice would be to Translate 
    only as the last step before drawing.

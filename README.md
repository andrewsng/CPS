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

Abstractions

  * The guidelines provided for the shape abstractions do seem to be well-designed. Writing new shapes requires minimal effort, and the common base makes working with collections of shapes fairly intuitive.
  * CPS as specified conforms to the Open / Closed principle. Extending the project to include customization to the shapes such as colors, fills, and linewidths would require minimal modification to the Shape classes as written. Extending the project to include further shapes or functionality also requires little or no modification of existing code.
  * CPS as specified conforms to the Interface Segregation principle. At present, there is a single function for writing one page of PostScript based on "one shape", which may be a full drawing built from compound shapes. Additional client interfaces could be developed that output collections of pages, or other types of PostScript files, without needing to rely on one another *or* make changes to the Shape Language.

Expressiveness

  * While on their own, the basic shapes are rudimentary, the inclusion of the required compounds does make CPS quite expressive with little additional work. Combining shapes through horizontal and vertical stacking, as well as layering, does allow for quick development of interesting drawings.  
  * One limitation that arises is from the center-aligned requirement of the Layered compound. Some drawings could be accomplished through allowing a relative origin of layers when constructed, or through another compound type utilizing translations discussed below.

Translation

  * Currently, positioning shapes to be drawn in specific places is a difficult task to get right, requiring use of Horizontal, Vertical, and Spacer shapes.
  * An actual TranslatedShape derived class might be a solution, and would go nicely with the ScaledShape and RotatedShape. However, there are potential issues
    with maintaining their bounding boxes, as well as determining how they interact when placed in compound shapes. Maybe a good practice would be to Translate 
    only as the last step before drawing.
  * As an example, consider the following drawing. Presently, achieving this relative placement of *two basic shapes* would require using a layered shape that contains two vertical shapes, each containing horizontal shapes built from a basic shape along with properly dimensioned spacers. Whew.

<p align="center"><img src="https://github.com/uaf372/CPS/blob/main/limitation-example.png"></p>
    
 Tessellation
 
 * While the shape definitions, including compound shapes, do allow for creating drawings easily piece by piece, generating repetitive patterns can be cumbersome. (see the hexagonal lattice example in main.cpp)
 * One way to avoid writing such messy code for a repetitive pattern would be to develop a Tessellation compound shape that takes as input bounding dimensions, a base shape, and a tiling origin. This new compound shape would then build as many vertical and horizontal shapes are required to fill the specified bounds with a tiling of the base shape.

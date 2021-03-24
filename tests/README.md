## CPS Tests

Testing for this project was done in three stages:

* Unit Testing of Basic Shapes (using Catch2)

  * Verify exceptions thrown for invalid inputs to constructors of basic shapes
  * Verify bounding dimensions for basic and compound shapes
  * Verify PostScript output strings contain correct number of specific commands for basic shapes

* Batch Conversion of PostScript Output Files to PDF to Verify Correct Syntax

* Manual Inspection of Conversion Outputs to Verify Correct Appearance

![Example Batch Conversion](https://github.com/uaf372/CPS/blob/main/tests/batch-conv.png?raw=true)


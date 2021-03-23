## CPS Tests

Testing for this project was done in three stages:

* Unit Testing of Basic Shapes (using Catch2)

  * Verify exceptions thrown for invalid inputs to constructors
  * Verify PostScript output strings contain correct number of specific commands

* Batch Conversion of PostScript Output Files to PDF to Verify Correct Syntax

![Example Batch Conversion](https://github.com/uaf372/CPS/tests/batch-conv.png)

* Manual Inspection of Conversion Outputs to Verify Correct Appearance

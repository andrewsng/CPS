#ifndef UAF372_CPS_CPS_H
#define UAF372_CPS_CPS_H

#include "Shape.hpp"

#include <iostream>
#include <fstream>
#include <memory>

void Write_Postscript_File(const std::string& filename, const std::shared_ptr<Shape>& s_ptr,
                           double originX = 0.0, double originY = 0.0);

#endif

#include "Shape.hpp"

std::string Rectangle::ToPostScript() const {

	// when writing output to PostScript we start at the
	// center of the shape's bounding box, so begin the
	// drwaing by moving from the center to the first vertex
	// then proceed to draw lines "relative to that position"
	// connecting to the remaining vertices

	double x = -bounding.Width() / 2;
	double y = -bounding.Height() / 2;

	std::string output = "newpath\n";
	output += std::to_string(x) + " " + std::to_string(y) + " moveto\n";
	output += std::to_string(bounding.Width()) + " 0 rlineto\n";
	output += " 0 " + std::to_string(bounding.Height()) + " rlineto\n";
	output += "-" + std::to_string(bounding.Width()) + " 0 rlineto\n";
	output += "closepath\nstroke";

	return output;
}
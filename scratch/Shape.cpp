#include <cmath>
#include <algorithm>
#include "Shape.hpp"

std::string Rectangle::ToPostScript() const {

	// when writing output to PostScript we start at the
	// center of the shape's bounding box, so begin the
	// drwaing by moving from the center to the first vertex (bottom left)
	// then proceed to draw lines "relative to that position"
	// connecting to the remaining vertices
	
	std::string output{ "newpath\n" };

	output += std::to_string(-bounding.Width() / 2) + " ";
	output += std::to_string(-bounding.Height() / 2) + " moveto\n";
	output += std::to_string(bounding.Width()) + " 0 rlineto\n";
	output += " 0 " + std::to_string(bounding.Height()) + " rlineto\n";
	output += "-" + std::to_string(bounding.Width()) + " 0 rlineto\n";
	output += "closepath\nstroke\n";

	return output;
}

Polygon::Polygon(int numSides, double sideLength) : bounding(BoundingBox::FromPolygon(numSides, sideLength))
{
	num_sides = numSides;
	side_length = sideLength;
	exterior_angle_radians = 2 * PI / numSides;
}

std::string Polygon::ToPostScript() const {
	std::string output{ "newpath\n" };

	// start by moving to bottom left vertex of polygon (first side drawn is always horizontal at bottom)
	output += std::to_string(-side_length / 2) + " ";
	output += std::to_string(-bounding.Height() / 2);
	output += " moveto\n";

	for (int i = 0; i < num_sides - 1; i++) {

		double current_direction = i * exterior_angle_radians;
		double next_x = side_length * cos(current_direction);
		double next_y = side_length * sin(current_direction);
		output += std::to_string(next_x) + " " + std::to_string(next_y) + " rlineto\n";
	}
	output += "closepath\nstroke\n";

	return output;
}

std::string Circle::ToPostScript() const {
	std::string output{ "newpath\n" };

	output += "0 0 " + std::to_string(_radius) + " 0 360 arc\n";
	output += "closepath\nstroke\n";

	return output;
}

std::string Square::ToPostScript() const
{
	std::string output{ "newpath\n" };

	output += std::to_string(-bounding.Width() / 2) + " ";
	output += std::to_string(-bounding.Height() / 2) + " moveto\n";
	output += std::to_string(bounding.Width()) + " 0 rlineto\n";
	output += " 0 " + std::to_string(bounding.Height()) + " rlineto\n";
	output += std::to_string(-bounding.Width()) + " 0 rlineto\n";
	output += "closepath\nstroke\n";

	return output;
}

std::string Triangle::ToPostScript() const
{
	std::string output{ "newpath\n" };

	output += std::to_string(-bounding.Width() / 2) + " ";
	output += std::to_string(-bounding.Height() / 2) + " moveto\n";
	output += std::to_string(bounding.Width() / 2) + " ";
	output += std::to_string(bounding.Height()) + " rlineto\n";
	output += std::to_string(bounding.Width() / 2) + " ";
	output += std::to_string(-bounding.Height()) + " rlineto\n";
	output += "closepath\nstroke\n";

	return output;
}

Layered::Layered(std::initializer_list<std::shared_ptr<Shape>> list)
	: bounding(BoundingBox::FromRectangle(
		std::max(list, [](auto &a, auto &b) { 
			return a->Extent().Width() < b->Extent().Width();
			})->Extent().Width(),
	    std::max(list, [](auto &a, auto &b) {
			return a->Extent().Height() < b->Extent().Height();
			})->Extent().Height())),
	  _shapeList(list)
{}

std::string Layered::ToPostScript() const {
	std::string output{};
	for (const auto &shape : _shapeList)
	{
		output += shape->ToPostScript();
		output += "\n";
	}
	
	return output;
}

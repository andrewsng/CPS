#include <algorithm>
#include <stdexcept>
#include "Shape.hpp"

Rectangle::Rectangle(double width, double height)
{
	if (width < 0 || height < 0) throw std::invalid_argument("Shape dimensions must be positive");
	_width = width;
	_height = height;
}

std::string Rectangle::ToPostScript() const {

	// when writing output to PostScript we start at the
	// center of the shape's bounding box, so begin the
	// drwaing by moving from the center to the first vertex (bottom left)
	// then proceed to draw lines "relative to that position"
	// connecting to the remaining vertices
	
	std::string output{ "newpath\n" };

	output += std::to_string(-Width() / 2) + " ";
	output += std::to_string(-Height() / 2) + " moveto\n";
	output += std::to_string(Width()) + " 0 rlineto\n";
	output += " 0 " + std::to_string(Height()) + " rlineto\n";
	output += "-" + std::to_string(Width()) + " 0 rlineto\n";
	output += "closepath\nstroke\n";

	return output;
}

Polygon::Polygon(int numSides, double sideLength)
{
	num_sides = numSides;
	side_length = sideLength;
	exterior_angle_radians = 2 * PI / numSides;

	if (numSides % 2 != 0) {
		_width = sideLength * sin(PI * (numSides - 1) / (2 * numSides)) / sin(PI / numSides);
		_height = sideLength * (1 + cos(PI / numSides)) / (2 * sin(PI / numSides));
	}
	else
	{
		if (numSides % 4 == 0) {
			_width = sideLength * cos(PI / numSides) / sin(PI / numSides);
			_height = _width;
		}
		else {
			_width = sideLength / sin(PI / numSides);
			_height = _width * cos(PI / numSides);
		}
	}
}

std::string Polygon::ToPostScript() const {
	std::string output{ "newpath\n" };

	// start by moving to bottom left vertex of polygon (first side drawn is always horizontal at bottom)
	output += std::to_string(-side_length / 2) + " ";
	output += std::to_string(-Height() / 2);
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

std::string Square::ToPostScript() const
{
	std::string output{ "newpath\n" };

	output += std::to_string(-Width() / 2) + " ";
	output += std::to_string(-Height() / 2) + " moveto\n";
	output += std::to_string(Width()) + " 0 rlineto\n";
	output += " 0 " + std::to_string(Height()) + " rlineto\n";
	output += std::to_string(-Width()) + " 0 rlineto\n";
	output += "closepath\nstroke\n";

	return output;
}

std::string Triangle::ToPostScript() const
{
	std::string output{ "newpath\n" };

	output += std::to_string(-Width() / 2) + " ";
	output += std::to_string(-Height() / 2) + " moveto\n";
	output += std::to_string(Width() / 2) + " ";
	output += std::to_string(Height()) + " rlineto\n";
	output += std::to_string(Width() / 2) + " ";
	output += std::to_string(Height()) + " rlineto\n";
	output += "closepath\nstroke\n";

	return output;
}

std::string Circle::ToPostScript() const {
	std::string output{ "newpath\n" };

	output += "0 0 " + std::to_string(_radius) + " 0 360 arc\n";
	output += "closepath\nstroke\n";

	return output;
}

Layered::Layered(std::initializer_list<std::shared_ptr<Shape>> list) : _shapeList(list) 
{
	_width = std::max(list, [](auto& a, auto& b) {	return a->Width() < b->Width();	})->Width();
	_height = std::max(list, [](auto& a, auto& b) {	return a->Height() < b->Height(); })->Height();
}

std::string Layered::ToPostScript() const {
	std::string output{};
	for (const auto &shape : _shapeList)
	{
		output += shape->ToPostScript();
		output += "\n";
	}
	
	return output;
}
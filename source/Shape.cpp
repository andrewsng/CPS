#include <algorithm>
#include <stdexcept>
#include "Shape.hpp"

Rectangle::Rectangle(double width, double height)
{
	if (width <= 0 || height <= 0) throw std::invalid_argument("Shape dimensions must be positive");
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

Polygon::Polygon(int num_sides, double side_length)
{
	if (num_sides <= 3) throw std::invalid_argument("Regular polygon cannot have fewer than 3 sides");
	if (side_length <= 0) throw std::invalid_argument("Shape dimensions must be positive");

	_num_sides = num_sides;
	_side_length = side_length;
	exterior_angle_radians = 2 * PI / num_sides;

	if (num_sides % 2 != 0) {
		_width = side_length * sin(PI * (num_sides - 1) / (2 * num_sides)) / sin(PI / num_sides);
		_height = side_length * (1 + cos(PI / num_sides)) / (2 * sin(PI / num_sides));
	}
	else
	{
		if (num_sides % 4 == 0) {
			_width = side_length * cos(PI / num_sides) / sin(PI / num_sides);
			_height = _width;
		}
		else {
			_width = side_length / sin(PI / num_sides);
			_height = _width * cos(PI / num_sides);
		}
	}
}

std::string Polygon::ToPostScript() const {
	std::string output{ "newpath\n" };

	// start by moving to bottom left vertex of polygon (first side drawn is always horizontal at bottom)
	output += std::to_string(-_side_length / 2) + " ";
	output += std::to_string(-Height() / 2);
	output += " moveto\n";

	for (int i = 0; i < _num_sides - 1; i++) {

		double current_direction = i * exterior_angle_radians;
		double next_x = _side_length * cos(current_direction);
		double next_y = _side_length * sin(current_direction);
		output += std::to_string(next_x) + " " + std::to_string(next_y) + " rlineto\n";
	}
	output += "closepath\nstroke\n";

	return output;
}

Square::Square(double side_length)
{
	if (side_length <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_side_length = side_length;
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

Triangle::Triangle(double side_length)
{
	if (side_length <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_side_length = side_length;
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

Circle::Circle(double radius)
{
	if (radius <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_radius = radius;
	_width = 2 * radius;
	_height = 2 * radius;
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

Spacer::Spacer(double width, double height)
{
	if (width <= 0 || height <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_width = width;
	_height = height;
}
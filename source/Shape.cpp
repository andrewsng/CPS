#include <algorithm>
#include <numeric>
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
	
	//std::string output{ "newpath\n" };
	std::string output{};

	output += std::to_string(-Width() / 2) + " ";
	output += std::to_string(-Height() / 2) + " rmoveto\n";
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
	
	std::string output{};

	output += "currentpoint /y exch def /x exch def\nnewpath\n";
	output += "x y " + std::to_string(_radius) + " 0 360 arc\n";
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


VerticalShapes::VerticalShapes(std::initializer_list<std::shared_ptr<Shape>> list) : _shapeList(list)
{
	_width = std::max(list, [](auto& a, auto& b) {	return a->Width() < b->Width();	})->Width();
	_height = std::accumulate(list.begin(), list.end(), 0.0, [](double sum, const auto& s) {return sum + s->Height(); });
}

std::string VerticalShapes::ToPostScript() const
{
	// assume the "current point" in postscript file is the center
	// of the first shape; after calling its ToPostScript, need
	// to move up to center of next shape

	std::string output{};

	// move to bottom-center of first shape
	output += "0 " + std::to_string(-_shapeList.front()->Height() / 2) + " rmoveto\n";

	for (const auto& shape : _shapeList)
	{
		// move from top-center of previous shape to center of current shape
		output += "0 " + std::to_string(shape->Height() / 2) + " rmoveto\n";

		output += shape->ToPostScript();
		
		// move from center of current shape to top-center of current shape
		output += "0 " + std::to_string(shape->Height() / 2) + " rmoveto\n";
		output += "\n";
	}

	return output;
}

HorizontalShapes::HorizontalShapes(std::initializer_list<std::shared_ptr<Shape>> list) : _shapeList(list)
{
	_width = std::accumulate(list.begin(), list.end(), 0.0, [](double sum, const auto& s) {return sum + s->Width(); });
	_height = std::max(list, [](auto& a, auto& b) {	return a->Height() < b->Height(); })->Height();
}


std::string HorizontalShapes::ToPostScript() const
{
	// assume the "current point" in postscript file is the center
	// of the first shape; after calling its ToPostScript, need
	// to move right to center of next shape

	std::string output{};

	// move to left-center of first shape
	output += std::to_string(-_shapeList.front()->Width() / 2) + " 0 rmoveto\n";

	for (const auto& shape : _shapeList)
	{
		// move from left-center of previous shape to center of current shape
		output += std::to_string(shape->Width() / 2) + " 0 rmoveto\n";

		output += shape->ToPostScript();

		// move from center of current shape to right-center of current shape
		output += std::to_string(shape->Width() / 2) + " 0 rmoveto\n";
		output += "\n";
	}

	return output;
}

std::string Scaled::ToPostScript() const
{
	std::string output{};

	output += "gsave\n";
	output += std::to_string(_factorX) + " " + std::to_string(_factorY) + " scale\n";
	output += _shape->ToPostScript();
	output += "grestore\n";

	return output;
}

Scaled::Scaled(std::shared_ptr<Shape> shape, double factorX, double factorY)
	:_width(factorX * shape->Width()),_height(factorY * shape->Height()),
	 _factorX(factorX),_factorY(factorY),_shape(shape)
{}

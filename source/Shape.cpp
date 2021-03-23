#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "Shape.hpp"

RectangleShape::RectangleShape(double width, double height)
{
	if (width <= 0 || height <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_width = width;
	_height = height;
}

std::string RectangleShape::ToPostScript() const {

	// when writing output to PostScript we start at the
	// center of the shape's bounding box, so begin the
	// drwaing by moving from the center to the first vertex (bottom left)
	// then proceed to draw lines "relative to that position"
	// connecting to the remaining vertices
	
	std::string output{"gsave\n"};

	output += std::to_string(-Width() / 2) + " ";
	output += std::to_string(-Height() / 2) + " rmoveto\n";
	output += std::to_string(Width()) + " 0 rlineto\n";
	output += " 0 " + std::to_string(Height()) + " rlineto\n";
	output += "-" + std::to_string(Width()) + " 0 rlineto\n";
	output += "closepath\nstroke\ngrestore\n";

	return output;
}

PolygonShape::PolygonShape(int num_sides, double side_length)
{
	if (num_sides <= 3) throw std::invalid_argument("Regular PolygonShape cannot have fewer than 3 sides");
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

std::string PolygonShape::ToPostScript() const {
	
	std::string output{ "gsave\n" };

	// start by moving to bottom left vertex of PolygonShape (first side drawn is always horizontal at bottom)
	output += std::to_string(-_side_length / 2) + " ";
	output += std::to_string(-Height() / 2);
	output += " rmoveto\n";

	for (int i = 0; i < _num_sides - 1; i++) {

		double current_direction = i * exterior_angle_radians;
		double next_x = _side_length * cos(current_direction);
		double next_y = _side_length * sin(current_direction);
		output += std::to_string(next_x) + " " + std::to_string(next_y) + " rlineto\n";
	}
	output += "closepath\nstroke\ngrestore\n";

	return output;
}

SquareShape::SquareShape(double side_length)
{
	if (side_length <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_side_length = side_length;
}

std::string SquareShape::ToPostScript() const
{
	std::string output{ "gsave\n" };

	output += std::to_string(-Width() / 2) + " ";
	output += std::to_string(-Height() / 2) + " rmoveto\n";
	output += std::to_string(Width()) + " 0 rlineto\n";
	output += " 0 " + std::to_string(Height()) + " rlineto\n";
	output += std::to_string(-Width()) + " 0 rlineto\n";
	output += "closepath\nstroke\ngrestore\n";

	return output;
}

TriangleShape::TriangleShape(double side_length)
{
	if (side_length <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_side_length = side_length;
}

std::string TriangleShape::ToPostScript() const
{
	std::string output{ "gsave\n" };

	output += std::to_string(-Width() / 2) + " ";
	output += std::to_string(-Height() / 2) + " rmoveto\n";
	output += std::to_string(Width()) + " 0 rlineto\n";
	output += std::to_string(-Width() / 2) + " ";
	output += std::to_string(Height()) + " rlineto\n";
	output += "closepath\nstroke\ngrestore\n";

	return output;
}

CircleShape::CircleShape(double radius)
{
	if (radius <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_radius = radius;
	_width = 2 * radius;
	_height = 2 * radius;
}

std::string CircleShape::ToPostScript() const {
	
	std::string output{ "gsave\n" };

	output += "currentpoint /y exch def /x exch def\nnewpath\n";
	output += "x y " + std::to_string(_radius) + " 0 360 arc\n";
	output += "closepath\nstroke\ngrestore\n";

	return output;
}

LayeredShapes::LayeredShapes(std::initializer_list<std::shared_ptr<Shape>> list) : _shapeList(list) 
{
	_width = std::max(list, [](auto& a, auto& b) {	return a->Width() < b->Width();	})->Width();
	_height = std::max(list, [](auto& a, auto& b) {	return a->Height() < b->Height(); })->Height();
}

std::string LayeredShapes::ToPostScript() const {
	std::string output{};
	for (const auto &shape : _shapeList)
	{
		output += shape->ToPostScript();
		output += "\n";
	}
	
	return output;
}

SpacerShape::SpacerShape(double width, double height)
{
	if (width <= 0 || height <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_width = width;
	_height = height;
}

Plus::Plus(double crosslength, double crosswidth)
{
	if (crosslength <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	if (crosswidth <= 0) throw std::invalid_argument("Shape dimensions must be positive");
	_crosslength = crosslength;
	_crosswidth = crosswidth;
}

std::string Plus::ToPostScript() const {
	std::string output{ "gsave\n" };

	output += std::to_string(_crosswidth / 2) + " ";
	output += std::to_string(_crosswidth / 2) + " rmoveto\n";

	for (int i = 0; i < 4; i++)
	{
		output += std::to_string(_crosslength) + " 0 rlineto\n";
		output += " 0 " + std::to_string(-_crosswidth) + " rlineto\n";
		output += std::to_string(_crosslength) + " 0 rlineto\n";
		output += " 0 " + std::to_string(_crosswidth) + " rmoveto\n";
		output += "90 rotate\n";
	}

	output += "grestore\n";

	return output;
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

	std::string output{"gsave\n"};

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
	output += "grestore\n";

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

	std::string output{"gsave\n"};

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
	output += "grestore\n";

	return output;
}

std::string ScaledShape::ToPostScript() const
{
	std::string output{};

	output += "gsave\n";
	output += std::to_string(_factorX) + " " + std::to_string(_factorY) + " scale\n";
	output += _shape->ToPostScript();
	output += "grestore\n";

	return output;
}

ScaledShape::ScaledShape(std::shared_ptr<Shape> shape, double factorX, double factorY)
	:_width(factorX * shape->Width()),_height(factorY * shape->Height()),
	 _factorX(factorX),_factorY(factorY),_shape(shape)
{}

std::string RotatedShape::ToPostScript() const
{
	std::string output{};

	output += "gsave\n";
	output += std::to_string(static_cast<int>(_angle)) + " rotate\n";
	output += _shape->ToPostScript();
	output += "grestore\n";

	return output;
}

RotatedShape::RotatedShape(std::shared_ptr<Shape> shape, Angle angle)
	:_width(angle == Angle::deg180 ? shape->Width() : shape->Height()),
	 _height(angle == Angle::deg180 ? shape->Height() : shape->Width()),
	 _angle(angle),
	 _shape(shape)
{}


std::shared_ptr<RectangleShape> Rectangle(double width, double height)
{
	return std::make_shared<RectangleShape>(width, height);
}

std::shared_ptr<PolygonShape> Polygon(int numSides, double sideLength)
{
	return std::make_shared<PolygonShape>(numSides, sideLength);
}

std::shared_ptr<SpacerShape> Spacer(double width, double height)
{
	return std::make_shared<SpacerShape>(width, height);
}

std::shared_ptr<SquareShape> Square(double sideLength)
{
	return std::make_shared<SquareShape>(sideLength);
}

std::shared_ptr<TriangleShape> Triangle(double sideLength)
{
	return std::make_shared<TriangleShape>(sideLength);
}

std::shared_ptr<CircleShape> Circle(double radius)
{
	return std::make_shared<CircleShape>(radius);
}

std::shared_ptr<ScaledShape> Scaled(std::shared_ptr<Shape> shape, double fx, double fy)
{
	return std::make_shared<ScaledShape>(shape, fx, fy);
}

std::shared_ptr<RotatedShape> Rotated(std::shared_ptr<Shape> shape, Angle rotationAngle)
{
	return std::make_shared<RotatedShape>(shape, rotationAngle);
}

std::shared_ptr<LayeredShapes> Layered(std::initializer_list<std::shared_ptr<Shape>> list)
{
	return std::make_shared<LayeredShapes>(list);
}

std::shared_ptr<VerticalShapes> Vertical(std::initializer_list<std::shared_ptr<Shape>> list)
{
	return std::make_shared<VerticalShapes>(list);
}

std::shared_ptr<HorizontalShapes> Horizontal(std::initializer_list<std::shared_ptr<Shape>> list)
{
	return std::make_shared<HorizontalShapes>(list);
}

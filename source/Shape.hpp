#ifndef UAF372_CPS_SHAPE_H
#define UAF372_CPS_SHAPE_H

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

const double PI = 3.14159265358979323846264;

class Shape {

public:
	
	[[nodiscard]] virtual double Width() const = 0;
	[[nodiscard]] virtual double Height() const = 0;
	[[nodiscard]] virtual std::string ToPostScript() const = 0;
	
	virtual ~Shape() = default;
};

class RectangleShape : public Shape {

private:

	double _width;
	double _height;

public:
	
	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	RectangleShape(double width, double height);
};

class SpacerShape : public Shape {

private:

	double _width;
	double _height;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override { return ""; }
	SpacerShape(double width, double height);
};

class SquareShape : public Shape {

private:

	double _side_length;

public:

	[[nodiscard]] double Width() const override { return _side_length; }
	[[nodiscard]] double Height() const override { return _side_length; }
	[[nodiscard]] std::string ToPostScript() const override;
	SquareShape(double side_length);
};

class TriangleShape : public Shape {
private:

	double _side_length;

public:
	
	[[nodiscard]] double Width() const override { return _side_length; }
	[[nodiscard]] double Height() const override { return _side_length / 2 * sqrt(3); }
	[[nodiscard]] std::string ToPostScript() const override;
	TriangleShape(double side_length);
};

class PolygonShape : public Shape {

private:

	double _width;
	double _height;
	int _num_sides;
	double _side_length;
	double exterior_angle_radians;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	PolygonShape(int numSides, double side_length);
};

class CircleShape : public Shape {

private:

	double _width;
	double _height;
	double _radius;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	CircleShape(double radius);
};

class Plus : public Shape {
private:

	double _crosslength;
	double _crosswidth;

public:

	[[nodiscard]] double Height() const override { return _crosslength * 2 + _crosswidth * 2; }
	[[nodiscard]] double Width() const override { return _crosslength * 2 + _crosswidth * 2; }
	[[nodiscard]] std::string ToPostScript() const override;
	Plus(double crosslength, double crosswidth);
};

class LayeredShapes : public Shape {

private:

	double _width;
	double _height;
	std::vector<std::shared_ptr<Shape>> _shapeList;
	
public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	LayeredShapes(std::initializer_list<std::shared_ptr<Shape>> list);

};


class VerticalShapes : public Shape {

private:

	double _width;
	double _height;
	std::vector<std::shared_ptr<Shape>> _shapeList;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	VerticalShapes(std::initializer_list<std::shared_ptr<Shape>> list);

};


class HorizontalShapes : public Shape {

private:

	double _width;
	double _height;
	std::vector<std::shared_ptr<Shape>> _shapeList;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	HorizontalShapes(std::initializer_list<std::shared_ptr<Shape>> list);

};

class ScaledShape : public Shape {

private:

	double _width;
	double _height;
	double _factorX;
	double _factorY;
	std::shared_ptr<Shape> _shape;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	ScaledShape(std::shared_ptr<Shape> shape, double factorX, double factorY);
	
};

enum class Angle {
	deg90  = 90,
	deg180 = 180,
	deg270 = 270
};

class RotatedShape : public Shape {

private:

	double _width;
	double _height;
	Angle _angle;
	std::shared_ptr<Shape> _shape;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	RotatedShape(std::shared_ptr<Shape> shape, Angle angle);
	
};


std::shared_ptr<RectangleShape> Rectangle(double width, double height);

std::shared_ptr<PolygonShape> Polygon(int numSides, double sideLength);

std::shared_ptr<SpacerShape> Spacer(double width, double height);

std::shared_ptr<SquareShape> Square(double sideLength);

std::shared_ptr<TriangleShape> Triangle(double sideLength);

std::shared_ptr<CircleShape> Circle(double radius);

std::shared_ptr<ScaledShape> Scaled(std::shared_ptr<Shape> shape, double fx, double fy);

std::shared_ptr<RotatedShape> Rotated(std::shared_ptr<Shape> shape, Angle rotationAngle);

std::shared_ptr<LayeredShapes> Layered(std::initializer_list<std::shared_ptr<Shape>> list);

#endif
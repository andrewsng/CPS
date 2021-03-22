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

class Rectangle : public Shape {

private:

	double _width;
	double _height;

public:
	
	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	Rectangle(double width, double height);
};

class Spacer : public Shape {

private:

	double _width;
	double _height;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override { return ""; }
	Spacer(double width, double height);
};

class Square : public Shape {

private:

	double _side_length;

public:

	[[nodiscard]] double Width() const override { return _side_length; }
	[[nodiscard]] double Height() const override { return _side_length; }
	[[nodiscard]] std::string ToPostScript() const override;
	Square(double side_length);
};

class Triangle : public Shape {
private:

	double _side_length;

public:
	
	[[nodiscard]] double Width() const override { return _side_length; }
	[[nodiscard]] double Height() const override { return _side_length / 2 * sqrt(3); }
	[[nodiscard]] std::string ToPostScript() const override;
	Triangle(double side_length);
};

class Polygon : public Shape {

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
	Polygon(int numSides, double side_length);
};

class Circle : public Shape {

private:

	double _width;
	double _height;
	double _radius;

public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	Circle(double radius);
};

class Layered : public Shape {

private:

	double _width;
	double _height;
	std::vector<std::shared_ptr<Shape>> _shapeList;
	
public:

	[[nodiscard]] double Width() const override { return _width; }
	[[nodiscard]] double Height() const override { return _height; }
	[[nodiscard]] std::string ToPostScript() const override;
	Layered(std::initializer_list<std::shared_ptr<Shape>> list);

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

#endif
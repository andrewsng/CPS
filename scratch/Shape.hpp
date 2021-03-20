#ifndef UAF372_CPS_SHAPE_H
#define UAF372_CPS_SHAPE_H

#include <string>
#include "BoundingBox.hpp"

class Shape {

public:
	
	[[nodiscard]] virtual BoundingBox Extent() const = 0;
	[[nodiscard]] virtual std::string ToPostScript() const = 0;
	virtual ~Shape() = default;
	
};

class Rectangle : public Shape {

private:
	BoundingBox bounding;

public:
	[[nodiscard]] BoundingBox Extent() const override { return bounding; }
	[[nodiscard]] std::string ToPostScript() const override;
	Rectangle(double width, double height) : bounding( BoundingBox::FromRectangle(width,height)) {}
};

class Polygon : public Shape {

private:
	BoundingBox bounding;
	int num_sides;
	double side_length;
	double exterior_angle_radians;

public:
	[[nodiscard]] BoundingBox Extent() const override { return bounding; }
	[[nodiscard]] std::string ToPostScript() const override;
	Polygon(int numSides, double sideLength);
};

class Circle : public Shape {

private:
	BoundingBox bounding;
	double _radius;

public:
	[[nodiscard]] BoundingBox Extent() const override { return bounding; }
	[[nodiscard]] std::string ToPostScript() const override;
	Circle(double radius)
		: bounding(BoundingBox::FromRectangle(2*radius, 2*radius)), _radius(radius)
	{}
};

#endif
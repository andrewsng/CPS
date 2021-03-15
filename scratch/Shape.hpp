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

class Rectangle : Shape {

private:
	BoundingBox bounding;

public:
	[[nodiscard]] BoundingBox Extent() const override { return bounding; }
	[[nodiscard]] std::string ToPostScript() const override;
	Rectangle(double width, double height) : bounding{ 0, width, 0, height } {}
};

#endif
#include "BoundingBox.hpp"

BoundingBox BoundingBox::FromRectangle(double width, double height)
{
	return BoundingBox{ 0,width,0,height };
}

BoundingBox BoundingBox::FromPolygon(int numSides, double sideLength)
{
	double width; double height;

	if (numSides % 2 != 0) {
		width = sideLength * sin(PI * (numSides - 1) / (2 * numSides)) / sin(PI / numSides);
		height = sideLength * (1 + cos(PI / numSides)) / (2 * sin(PI / numSides));
	}
	else
	{
		if (numSides % 4 == 0) {
			width = sideLength * cos(PI / numSides) / sin(PI / numSides);
			height = width;
		}
		else {
			width = sideLength / sin(PI / numSides);
			height = width * cos(PI / numSides);
		}
	}

	return BoundingBox{ 0,width,0,height };
}

BoundingBox BoundingBox::FromSquare(double length)
{
	return BoundingBox{ 0,length,0,length };
}

BoundingBox BoundingBox::FromTriangle(double length)
{
	double height = length / 2 * sqrt(3);
	return BoundingBox{ 0,length,0,height };
}
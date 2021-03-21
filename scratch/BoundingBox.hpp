#ifndef UAF372_CPS_BOUNDING_H
#define UAF372_CPS_BOUNDING_H

#include <iostream>
#include "Point.hpp"

const double PI = 3.14159265358979323846264;

class BoundingBox {

private:

	double minx, maxx, miny, maxy;
	BoundingBox(double min_x, double max_x, double min_y, double max_y) :
		minx{ min_x }, maxx{ max_x }, miny{ min_y }, maxy{ max_y }{}

public:

	static BoundingBox FromRectangle(double width, double height);
	static BoundingBox FromPolygon(int numSides, double sideLength);
	static BoundingBox FromSquare(double length);
	static BoundingBox FromTriangle(double length);

	double Width() const { return maxx - minx; }
	double Height() const { return maxy - miny; }

	double Minimum_X() const { return minx; }
	double Maximum_X() const { return maxx; }
	double Minimum_Y() const { return miny; }
	double Maximum_Y() const { return maxy; }

	Point Top_Left() const { return Point{ minx,maxy }; }
	Point Top_Right() const { return Point{ maxx,maxy }; }
	Point Bottom_Right() const { return Point{ maxx,miny }; }
	Point Bottom_Left() const { return Point{ minx,miny }; }
	Point Center() const{ return Point{ minx + (maxx - minx) / 2, miny + (maxy - miny) / 2 }; }

	friend std::ostream& operator<< (std::ostream& out, const BoundingBox& box) {

		out << "Bounding Box Extents:\n  x: " << box.minx << ", " << box.maxx
			<< "\n  y: " << box.miny << ", " << box.maxy << std::endl;
		return out;
	}
};

#endif
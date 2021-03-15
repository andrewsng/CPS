#ifndef UAF372_CPS_POINT_H
#define UAF372_CPS_POINT_H

#include <iostream>

struct Point
{
    double X{};
    double Y{};

	friend std::ostream& operator<< (std::ostream& out, const Point& point) {

		out << point.X << ", " << point.Y;
		return out;
	}
};

#endif
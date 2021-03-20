#include <iostream>
#include "BoundingBox.hpp"
#include "Point.hpp"
#include "Shape.hpp"

int main() {

	Rectangle r(17.5, 32);

	std::cout << "\nRectangle Corners : \n";
	std::cout << "Top Left : " << r.Extent().Top_Left() << "\n";
	std::cout << "Top Right : " << r.Extent().Top_Right() << "\n";
	std::cout << "Bottom Right : " << r.Extent().Bottom_Right() << "\n";
	std::cout << "Bottom Left : " << r.Extent().Bottom_Left() << "\n";

	std::cout << "\nRectangle Center : " << r.Extent().Center() << "\n";

	std::cout << "\n\n" << r.ToPostScript() << "\n\n";

	Polygon p(7, 55);
	std::cout << "\n\n" << p.ToPostScript();
	
	Circle c(72);
	std::cout << "\n\n" << c.ToPostScript();

	std::cin.get();
	return 0;
}

//just testing
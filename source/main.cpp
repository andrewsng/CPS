#include <iostream>
#include <memory>
#include "Shape.hpp"

int main() {

	Rectangle r(17.5, 32);
	std::cout << "\n\nRectangle\n"  << r.ToPostScript();

	Polygon p(7, 55);
	std::cout << "\n\nPolygon\n" << p.ToPostScript();
	
	Circle c(72);
	std::cout << "\n\nCircle\n" << c.ToPostScript();
	
	Square s(15);
	std::cout << "\n\nSquare\n" << s.ToPostScript();

	Triangle t(1.5);
	std::cout << "\n\nTriangle\n" << t.ToPostScript();

	Layered l{ std::make_shared<Rectangle>(54, 80),
			   std::make_shared<Polygon>(5, 72),
			   std::make_shared<Circle>(25) };
	std::cout << "\n\nLayered Shape\n" << l.ToPostScript();

	std::cin.get();
	return 0;
}
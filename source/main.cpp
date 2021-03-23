#include <iostream>
#include <memory>
#include "Shape.hpp"

int main() {

	auto r = Rectangle(17.5, 32);
	std::cout << "\n\n%RectangleShape\n" << r->ToPostScript();

	auto p = Polygon(7, 55);
	std::cout << "\n\n%PolygonShape\n" << p->ToPostScript();
	
	Circle c(72);
	std::cout << "\n\n%Circle\n" << c.ToPostScript();
	
	Square s(15);
	std::cout << "\n\n%Square\n" << s.ToPostScript();

	Triangle t(1.5);
	std::cout << "\n\n%Triangle\n" << t.ToPostScript();

	Plus pl(15, 3);
	std::cout << "\n\n%Plus\n" << pl.ToPostScript();

	Layered l{ std::make_shared<RectangleShape>(54, 80),
			   std::make_shared<PolygonShape>(5, 72),
			   std::make_shared<Circle>(25) };
	std::cout << "\n\n%Layered Shape\n" << l.ToPostScript();

	VerticalShapes v{ std::make_shared<RectangleShape>(54, 80),
			   std::make_shared<PolygonShape>(5, 72),
			   std::make_shared<Circle>(25) };
	std::cout << "\n\n%Vertical Shape\n" << v.ToPostScript();

	auto sp = std::make_shared<Scaled>(std::make_shared<PolygonShape>(5, 72), 2.75, 2);
	std::cout << "\n\n%Scaled Shape\n" << sp->ToPostScript();
	
	auto shape = std::make_shared<HorizontalShapes>(HorizontalShapes{std::make_shared<PolygonShape>(5, 20),
	                                                				std::make_shared<Spacer>(15, 15),
																	std::make_shared<Circle>(30),
	                                                				std::make_shared<Spacer>(15, 15),
																	std::make_shared<RectangleShape>(25, 10)});
	std::cout << "\n\n%Horizontal Shape\n" << shape->ToPostScript();
	
	auto rot = std::make_shared<Layered>(Layered{std::make_shared<Rotated>(shape, Angle::deg90),
	                                           std::make_shared<Rotated>(shape, Angle::deg180),
											   std::make_shared<Rotated>(shape, Angle::deg270)});
	std::cout << "\n\n%Rotated Shapes\n" << rot->ToPostScript();

	std::cin.get();
	return 0;
}
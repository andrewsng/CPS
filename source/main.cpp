#include <iostream>
#include <memory>
#include "CPS.hpp"

int main() {

	auto r = Rectangle(17.5, 32);
	std::cout << "\n\n%RectangleShape\n" << r->ToPostScript();

	auto p = Polygon(7, 55);
	std::cout << "\n\n%PolygonShape\n" << p->ToPostScript();
	
	auto c = Circle(72);
	std::cout << "\n\n%CircleShape\n" << c->ToPostScript();
	
	auto s = Square(15);
	std::cout << "\n\n%SquareShape\n" << s->ToPostScript();

	auto t = Triangle(1.5);
	std::cout << "\n\n%TriangleShape\n" << t->ToPostScript();

	auto pl = Plus(50, 50);
	std::cout << "\n\n%PlusShape\n" << pl->ToPostScript();

	auto l = Layered({ Rectangle(54, 80),
			           Polygon(5, 72),
			           Circle(25) });
	std::cout << "\n\n%LayeredShapes Shape\n" << l->ToPostScript();

	auto v = Vertical({ Rectangle(54, 80),
			            Polygon(5, 72),
			            Circle(25) });
	std::cout << "\n\n%Vertical Shape\n" << v->ToPostScript();

	auto sp = Scaled(Polygon(5, 72), 2.75, 2);
	std::cout << "\n\n%ScaledShape Shape\n" << sp->ToPostScript();
	
	auto shape = Horizontal({Polygon(5, 20),
	                         Spacer(15, 15),
							 Circle(30),
	                         Spacer(15, 15),
							 Rectangle(25, 10)});
	std::cout << "\n\n%Horizontal Shape\n" << shape->ToPostScript();
	
	auto rot = Layered({Rotated(shape, Angle::deg90),
	                    Rotated(shape, Angle::deg180),
						Rotated(shape, Angle::deg270)});
	std::cout << "\n\n%RotatedShape Shapes\n" << rot->ToPostScript();

	std::cin.get();
	return 0;
}
#include "CPS.hpp"

int main() {


	std::string visual_path = "../../../visuals/";

	// create postscript file with three rows illustrating all basic shapes
	// note : middle row consists of polygons only

	auto tri = Triangle(45);
	auto sqr = Square(45);
	auto rct = Rectangle(165, 45);
	auto crc = Circle(27);
	auto spcr = Spacer(45, 45);

	auto row_one = Horizontal({ tri, spcr, sqr, spcr, rct, spcr, crc });

	auto tri_p = Polygon(3, 45);
	auto sqr_p = Polygon(4, 45);
	auto pnt = Polygon(5, 35);
	auto hex_p = Polygon(6, 30);
	auto hept = Polygon(7, 25);

	auto row_two = Horizontal({ tri_p,spcr,sqr_p,spcr,pnt,spcr,hex_p,spcr, hept });

	auto tri_layer = Layered({ tri, Scaled(tri, 0.75, 0.75), Scaled(tri, 0.5, 0.5), Scaled(tri, 0.25, 0.25) });
	auto sqr_layer = Layered({ sqr, Scaled(sqr, 0.75, 0.75), Scaled(sqr, 0.5, 0.5), Scaled(sqr, 0.25, 0.25) });
	auto rct_layer = Layered({ rct, Scaled(rct, 0.75, 0.75), Scaled(rct, 0.5, 0.5), Scaled(rct, 0.25, 0.25) });
	auto crc_layer = Layered({ crc, Scaled(crc, 0.75, 0.75), Scaled(crc, 0.5, 0.5), Scaled(crc, 0.25, 0.25) });

	auto row_three = Horizontal({ tri_layer,spcr,sqr_layer,spcr,rct_layer,spcr,crc_layer });

	auto combined_output = Vertical({ row_one,spcr,row_two,spcr,row_three });
	Write_Postscript_File(visual_path + "basic.ps", combined_output, 300, 500);


	// create postscript file with hexagonal lattice

	auto origHex = Polygon(6, 72);
	const double x = origHex->Height();
	const double y = origHex->Height()*sqrt(3);
	auto hex = Rotated(origHex, Angle::deg90);
	auto hexLine = Horizontal({hex, hex, hex, hex, hex, hex });
	auto twoLines = Layered({ hexLine, Vertical({Spacer(10, 1*y), Horizontal({Spacer(x, 10), hexLine })}),
							  Vertical({Spacer(10, 2*y), hexLine}), Vertical({Spacer(10, 3*y), Horizontal({Spacer(x, 10), hexLine })}),
							  Vertical({Spacer(10, 4*y), hexLine}), Vertical({Spacer(10, 5*y), Horizontal({Spacer(x, 10), hexLine })}),
							  Vertical({Spacer(10, 6*y), hexLine}), Vertical({Spacer(10, 7*y), Horizontal({Spacer(x, 10), hexLine })}),
							  Vertical({Spacer(10, 8*y), hexLine}), Vertical({Spacer(10, 9*y), Horizontal({Spacer(x, 10), hexLine })}) });
	Write_Postscript_File(visual_path + "hex.ps", twoLines, 306, 0);

	// create postscript file with the Sierpinski triangle

	auto frac = Sierpinski(400, 10);
	Write_Postscript_File(visual_path + "fractal.ps", frac, 300, 500);

	auto pls = Plus(50, 50);
	auto mlt = Multiply(150);
	auto div = Divide(150);
	auto sub = Rectangle(150, 37.5);

	// create postscript file with the calculator emoji
	
	auto add_sub = Horizontal({ sub, Spacer(60,60), pls });
	auto mlt_div = Horizontal({ mlt, Spacer(60,60), div });
	auto all_symbols = Vertical({ add_sub, Spacer(60,60), mlt_div });
	auto outer_box = Square(400);
	auto calc_emoji = Layered({ outer_box, all_symbols });
	Write_Postscript_File(visual_path + "calc.ps", calc_emoji, 300, 400);

	return 0;
}

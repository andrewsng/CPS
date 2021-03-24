#include <fstream>
#include <iostream>
#include <memory>
#include "CPS.hpp"

int main() {

	std::string outdir = "../../../visual_test_output/";
	const double x = 200;
	const double y = 450;

	auto rect = Rectangle(55, 85);
	Write_Postscript_File(outdir + "rect.ps", rect, x, y);

	auto circ = Circle(65);
	Write_Postscript_File(outdir + "circ.ps", circ, x, y);

	auto tri = Triangle(107);
	Write_Postscript_File(outdir + "tri.ps", tri, x, y);

	auto sqr = Square(86);
	Write_Postscript_File(outdir + "sqr.ps", sqr, x, y);

	auto poly = Polygon(8, 102);
	Write_Postscript_File(outdir + "poly.ps", poly, x, y);

	auto lay = Layered({ rect, circ, tri, poly, sqr });
	Write_Postscript_File(outdir + "layer.ps", lay, x, y);

	auto spcr = Spacer(35, 35);

	auto vert = Vertical({ circ,spcr,circ });
	Write_Postscript_File(outdir + "vert.ps", vert, x, y);

	auto horiz = Horizontal({ tri,spcr,rect,spcr,tri });
	Write_Postscript_File(outdir + "horiz.ps", horiz, x, y);

	auto scl = Scaled(poly, 1.25, 1.75);
	Write_Postscript_File(outdir + "scale.ps", Layered({ poly, scl }), x, y);

	auto pls = Plus(45, 45);
	Write_Postscript_File(outdir + "plus.ps", pls, x, y);

	auto mlt = Multiply(45);
	Write_Postscript_File(outdir + "mult.ps", mlt, x, y);

	auto div = Divide(45);
	Write_Postscript_File(outdir + "div.ps", div, x, y);

	auto sub = Rectangle(45, 11.25);

	auto add_sub = Horizontal({ sub, Spacer(22.5,45), Scaled(pls,0.333,0.333) });
	auto mlt_div = Horizontal({ mlt, Spacer(22.5,45), div });
	auto all_symbols = Vertical({ add_sub, Spacer(45,22.5), mlt_div });
	auto outer_box = Square(135);
	auto calc_emoji = Layered({ outer_box, all_symbols });
	Write_Postscript_File(outdir + "calc.ps", calc_emoji, x, y);


	auto rot = Horizontal({ tri, Rotated(tri, Angle::deg90), spcr,
		Rotated(tri, Angle::deg180), spcr,
		Rotated(tri, Angle::deg270) });
	Write_Postscript_File(outdir + "rotated.ps", rot, x, y);

	auto frac = Sierpinski(400, 10);
	Write_Postscript_File(outdir + "frac.ps", frac, x, y);
}
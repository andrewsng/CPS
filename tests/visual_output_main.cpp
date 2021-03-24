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
}
#include <fstream>
#include <iostream>
#include <memory>
#include "Shape.hpp"

void Write_Postscript_File(const std::string& filename, const std::shared_ptr<Shape>& s_ptr)
{
	// each shape is written to the postscript file using the 'current point' as
	// its center, so move to an absolute position in the page before output

	std::ofstream out_file;
	out_file.open(filename);

	out_file << "200 450 moveto\n";
	out_file << s_ptr->ToPostScript();
	out_file << "\nshowpage";
	out_file.close();
}

int main() {

	std::string outdir = "../../../visual_test_output/";

	auto rect = Rectangle(55, 85);
	Write_Postscript_File(outdir + "rect.ps", rect);

	auto circ = Circle(65);
	Write_Postscript_File(outdir + "circ.ps", circ);

	auto tri = Triangle(107);
	Write_Postscript_File(outdir + "tri.ps", tri);

	auto sqr = Square(86);
	Write_Postscript_File(outdir + "sqr.ps", sqr);

	auto poly = Polygon(8, 102);
	Write_Postscript_File(outdir + "poly.ps", poly);

	auto lay = Layered({ rect, circ, tri, poly, sqr });
	Write_Postscript_File(outdir + "layer.ps", lay);

	auto spcr = Spacer(35, 35);

	auto vert = Vertical({ circ,spcr,circ });
	Write_Postscript_File(outdir + "vert.ps", vert);

	auto horiz = Horizontal({ tri,spcr,rect,spcr,tri });
	Write_Postscript_File(outdir + "horiz.ps", horiz);

	auto scl = Scaled(poly, 1.25, 1.75);
	Write_Postscript_File(outdir + "scale.ps", Layered({ poly, scl }));
}
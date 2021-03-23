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

	auto rect = std::make_shared<Rectangle>(55, 85);
	Write_Postscript_File(outdir + "rect.ps", rect);

	auto circ = std::make_shared<Circle>(65);
	Write_Postscript_File(outdir + "circ.ps", circ);

	auto tri = std::make_shared<Triangle>(107);
	Write_Postscript_File(outdir + "tri.ps", tri);

	auto sqr = std::make_shared<Square>(86);
	Write_Postscript_File(outdir + "sqr.ps", sqr);

	auto poly = std::make_shared<Polygon>(8, 102);
	Write_Postscript_File(outdir + "poly.ps", poly);

	auto lay = Layered{ rect, circ, tri, poly, sqr };
	auto lay_ptr = std::make_shared<Layered>(lay);
	Write_Postscript_File(outdir + "layer.ps", lay_ptr);

	auto spcr = std::make_shared<Spacer>(35, 35);

	auto vert = VerticalShapes{ circ,spcr,circ };
	auto vert_ptr = std::make_shared<VerticalShapes>(vert);
	Write_Postscript_File(outdir + "vert.ps", vert_ptr);

	auto horiz = HorizontalShapes{ tri,spcr,rect,spcr,tri };
	auto horiz_ptr = std::make_shared<HorizontalShapes>(horiz);
	Write_Postscript_File(outdir + "horiz.ps", horiz_ptr);
}
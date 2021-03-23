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

	out_file << "350 350 moveto\n";
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
}
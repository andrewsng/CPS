#include "CPS.hpp"

int main() {

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
	Write_Postscript_File("../../../visual_test_output/hex.ps", twoLines, 306, 396);

	return 0;
}
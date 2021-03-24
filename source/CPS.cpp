#include "CPS.hpp"

void Write_Postscript_File(const std::string& filename, const std::shared_ptr<Shape>& s_ptr,
                           double originX, double originY)
{
	std::ofstream out_file(filename);
    if (!out_file) {
        std::cerr << "Write_Postscript_File: ERROR, file could not be opened" << std::endl;
    }

	// each shape is written to the postscript file using the 'current point' as
	// its center, so move to an absolute position in the page before output
	out_file << originX << " " << originY << " moveto\n";
	out_file << s_ptr->ToPostScript();
	out_file << "\nshowpage";
	out_file.close();
    if (!out_file) {
        std::cerr << "Write_Postscript_File: ERROR, file could not be written to" << std::endl;
    }
}
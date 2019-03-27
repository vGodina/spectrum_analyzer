#ifndef RFILECHOOSER
#define RFILECHOOSER
#include "IFileChooser.h"
#include "fltk/Fl_Native_File_Chooser.H"

class RFileChooser : public Fl_Native_File_Chooser, public IFileChooser
{
public:
	RFileChooser();
	void filter(const char*) override;
	int show() override;
	const char* filename() override;
};
#endif RFILECHOOSER
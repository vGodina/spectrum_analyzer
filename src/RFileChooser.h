#ifndef RFILECHOOSER_H
#define RFILECHOOSER_H

#include "IFileChooser.h"
#include "fltk/Fl_Native_File_Chooser.H"

class RFileChooser : public IFileChooser
{
public:
	RFileChooser();

	void filter(std::string_view) override;

	int show() override;

	std::string_view filename() override;
private:
	Fl_Native_File_Chooser Chooser;
};

#endif
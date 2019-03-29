#ifndef RFILECHOOSER_H
#define RFILECHOOSER_H
#include "IFileChooser.h"
#include "fltk/Fl_Native_File_Chooser.H"
#include <memory>

class RFileChooser : public IFileChooser
{
public:
	RFileChooser();
	void filter(std::string_view) override;
	int show() override;
	std::string_view filename() override;
	//Fl_Native_File_Chooser* GetImplWidget() override;
private:
	Fl_Native_File_Chooser Chooser;
};
#endif RFILECHOOSER_H
#include "RFileChooser.h"

RFileChooser::RFileChooser() : Fl_Native_File_Chooser() {}

void RFileChooser::filter(const char* Val)
{
	Fl_Native_File_Chooser::filter(Val);
}

int RFileChooser::show()
{
	return Fl_Native_File_Chooser::show();
}

const char* RFileChooser::filename()
{
	return Fl_Native_File_Chooser::filename();
}
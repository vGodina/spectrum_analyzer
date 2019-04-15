#include "RFileChooser.h"

RFileChooser::RFileChooser( ) : Chooser() { }


void RFileChooser::filter(std::string_view Val)
{
	Chooser.filter(std::data(Val));
}


int RFileChooser::show()
{
	return Chooser.show();
}


std::string_view RFileChooser::filename()
{
	return Chooser.filename();
}

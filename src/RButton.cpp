#include "RButton.h"

RButton::RButton(int x, int y, int w, int h, std::string_view L) : Button(x, y, w, h, std::data(L))  { }


void RButton::callback(Fl_Callback* Widg, void* Obj) 
{
	Button.callback(Widg, Obj);
}

/*
Fl_Native_File_Chooser* RFileChooser::GetImplWidget()
{
	return &Chooser;
}
*/

#include "RButton.h"

RButton::RButton() : Button(0, 0, 0, 0)  { }


void RButton::callback(Fl_Callback* Widg, void* Obj) 
{
	Button.callback(Widg, Obj);
}


Fl_Widget* RButton::GetImplWidget()
{
	return &Button;
}

void RButton::SetGeometry(int x, int y, int w, int h)
{
	Button.resize(x, y, w, h);
}

void RButton::SetCaption(std::string_view L)
{
	Button.label(std::data(L));
}
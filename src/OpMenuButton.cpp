#include "OpMenuButton.h"

OpMenuButton::OpMenuButton() : Button(30, 30, 100, 30, "Open .wav file")  { }

void OpMenuButton::callback(Fl_Callback* Widg, void* Obj)
{
	Button.callback(Widg, Obj);
}

Fl_Widget* OpMenuButton::GetImplWidget()
{
	return &Button;
}


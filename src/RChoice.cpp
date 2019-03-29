#include "RChoice.h"

RChoice::RChoice(int x, int y, int w, int h, std::string_view L) : Choice(x, y, w, h, std::data(L))  { }


int RChoice::value() const
{
	return Choice.value();
}


int RChoice::value(int v)
{
	return Choice.value(v);
}


int RChoice::add(std::string_view v)
{
	return Choice.add(std::data(v));
}


void RChoice::callback(Fl_Callback* Widg, void* Obj)
{
	Choice.callback(Widg, Obj);
}


Fl_Widget* RChoice::GetImplWidget()
{
	return &Choice;
}
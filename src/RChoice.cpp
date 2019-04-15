#include "RChoice.h"

RChoice::RChoice() : Choice(0, 0, 0, 0)  { }

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

void RChoice::SetGeometry(int x, int y, int w, int h)
{
	Choice.resize(x, y, w, h);
}

void RChoice::SetCaption(std::string_view L)
{
	Choice.label(std::data(L));
}
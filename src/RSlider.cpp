#include "RSlider.h"

RSlider::RSlider(int x, int y, int w, int h, std::string_view L) : Slider(x, y, w, h, std::data(L))  { }

void RSlider::type(uchar t)
{
	Slider.type(t);
}

float RSlider::slider_size()
{
	return Slider.slider_size();
}

void RSlider::slider_size(double v)
{
	Slider.slider_size(v);
}

double RSlider::value() const
{
	return Slider.value();
}

int RSlider::value(double v)
{
	return Slider.value(v);
}

void RSlider::callback(Fl_Callback* Widg, void* Obj)
{
	Slider.callback(Widg, Obj);
}

Fl_Widget* RSlider::GetImplWidget()
{
	return &Slider;
}
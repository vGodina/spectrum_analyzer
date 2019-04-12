#include "RSlider.h"

RSlider::RSlider() : Slider(0, 0, 0, 0)  { }

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

void RSlider::SetGeometry(int x, int y, int w, int h)
{
	Slider.resize(x, y, w, h);
}
#include "CustomSlider.h"

CustomSlider::CustomSlider(int x, int y, int w, int h) : Fl_Slider{ x, y, w, h }
{
	type(FL_HORIZONTAL);
	Reset();
}

inline void CustomSlider::Reset ()
{
	slider_size(1.0);
	value(0.5);
}

boost::signals2::connection CustomSlider::connect(const signal_t::slot_type &subscriber)
{
	return SliderSignal.connect(subscriber);
}

void CustomSlider::EmitSignal()
{
	CenterValue = value() - slider_size() * (value() - 0.5);
	SliderSignal(CustomSlider::CenterValue);
}

void CustomSlider::Resize (double ZoomFactor)
{
	slider_size(slider_size() / ZoomFactor);
	if (slider_size() == 1.0f)
		value(0.5);
	CenterValue = value() - slider_size() * (value() - 0.5);
}

double CustomSlider::GetStartValue ()
{
	return value() * (1.0 - slider_size());
}
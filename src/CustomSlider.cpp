#include "CustomSlider.h"

CustomSlider::CustomSlider(std::unique_ptr<ISlider> Slidr) : 
	Slider{ std::move(Slidr) }
{
	Slider->type(FL_HORIZONTAL);
	Reset();
}

inline void CustomSlider::Reset ()
{
	Slider->slider_size(1.0);
	Slider->value(0.5);
}

boost::signals2::connection CustomSlider::connect(const signal_t::slot_type &subscriber)
{
	return SliderSignal.connect(subscriber);
}

void CustomSlider::EmitSignal()
{
	CenterValue = Slider->value() - Slider->slider_size() * (Slider->value() - 0.5);
	SliderSignal(CustomSlider::CenterValue);
}

void CustomSlider::Resize (double ZoomFactor)
{
	Slider->slider_size(Slider->slider_size() / ZoomFactor);
	if (Slider->slider_size() == 1.0f)
		Slider->value(0.5);
	CenterValue = Slider->value() - Slider->slider_size() * (Slider->value() - 0.5);
}

double CustomSlider::GetStartValue ()
{
	return Slider->value() * (1.0 - Slider->slider_size());
}

float CustomSlider::slider_size()
{
	return Slider->slider_size();
}

void CustomSlider::callback(Fl_Callback* Widg, void* Obj)
{
	Slider->callback(Widg, Obj);
}

Fl_Widget* CustomSlider::GetImplWidget()
{
	return Slider->GetImplWidget();
}
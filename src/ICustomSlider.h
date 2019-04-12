#ifndef ICUSTOMSLIDER
#define ICUSTOMSLIDER
#include <memory>
#include <string_view>
#include <fltk/Fl_Slider.h>
#include <boost/signals2.hpp>

// Interface of CustomSlider

struct ICustomSlider
{
	virtual ~ICustomSlider() = default;
	
	using signal_t = boost::signals2::signal <void(double)>;

	virtual void Reset() = 0;

	virtual boost::signals2::connection connect(const signal_t::slot_type &subscriber) = 0;

	virtual void Resize(double ZoomFactor) = 0;

	virtual void EmitSignal() = 0;

	virtual float slider_size() = 0;

	virtual double GetStartValue() = 0;

	virtual void callback(Fl_Callback*, void*) = 0;

	virtual Fl_Widget* GetImplWidget() = 0;

	virtual void SetGeometry(int x, int y, int w, int h) = 0;
};
#endif ICUSTOMSLIDER
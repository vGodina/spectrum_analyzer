#ifndef ISLIDER
#define ISLIDER

#include <fltk/Fl_Slider.H>

// Interface of Slider

struct ISlider
{
	virtual ~ISlider() = default;

	virtual void type(uchar t) = 0;

	virtual float slider_size() = 0;
	virtual void slider_size(double) = 0;
	
	virtual double value() const = 0;
	virtual int value(double v) = 0;

	virtual void callback(Fl_Callback*, void*) = 0;

	virtual Fl_Widget* GetImplWidget() = 0;

	virtual void SetGeometry(int x, int y, int w, int h) = 0;
};
#endif
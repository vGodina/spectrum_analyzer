#ifndef RSLIDER_H
#define RSLIDER_H
#include "ISlider.h"
#include <fltk/Fl_Slider.h>
#include <memory>

class RSlider : public ISlider
{
public:
	RSlider(int x, int y, int w, int h, std::string_view L);

	void type(uchar t) override;

	float slider_size() override;
	void slider_size(double) override;

	double value() const override;
	int value(double v) override;

	void callback(Fl_Callback*, void*) override;
	Fl_Widget* GetImplWidget() override;
private:
	Fl_Slider Slider;
};
#endif RSLIDER_H
#ifndef RSLIDER_H
#define RSLIDER_H

#include "ISlider.h"

class RSlider : public ISlider
{
public:
	RSlider();

	void type(uchar t) override;

	float slider_size() override;
	void slider_size(double) override;

	double value() const override;
	int value(double v) override;

	void callback(Fl_Callback*, void*) override;
	Fl_Widget* GetImplWidget() override;

	void SetGeometry(int x, int y, int w, int h) override;
private:
	Fl_Slider Slider;
};
#endif
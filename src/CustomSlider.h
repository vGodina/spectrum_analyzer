#include <boost/signals2.hpp>
#include "ICustomSlider.h"
#include "ISlider.h"


class CustomSlider : public ICustomSlider
{
public:
	CustomSlider (std::unique_ptr<ISlider> Slidr);
	using signal_t = boost::signals2::signal <void(double)>;
	inline void Reset () override;
	boost::signals2::connection connect (const signal_t::slot_type &subscriber) override;
	void Resize (double ZoomFactor) override;
	// This method fires the signal that passes the Slider's CenterValue
	void EmitSignal () override;
	double GetStartValue () override;
	void callback(Fl_Callback*, void*) override;
	float slider_size() override;
	Fl_Widget* GetImplWidget() override;
	virtual void SetGeometry(int x, int y, int w, int h) override;

private:
	std::unique_ptr<ISlider> Slider;
	signal_t SliderSignal;
	double CenterValue;
	double StartValue;
};


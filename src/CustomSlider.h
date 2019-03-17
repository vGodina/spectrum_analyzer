#include <boost/signals2.hpp>
#include <fltk/Fl_Slider.H>

class CustomSlider : public Fl_Slider
{
public:
	CustomSlider (int x, int y, int w, int h);
	using signal_t = boost::signals2::signal <void(double)>;
	inline void Reset ();
	boost::signals2::connection connect (const signal_t::slot_type &subscriber);
	void Resize (double ZoomFactor);
	// This method fires the signal that passes the Slider's CenterValue
	void EmitSignal ();
	double GetStartValue ();
private:
	signal_t SliderSignal;
	double CenterValue;
	double StartValue;
};


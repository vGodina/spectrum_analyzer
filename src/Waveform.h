#include <boost/signals2.hpp>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Slider.H>
#include "Fl_AudioFile.h"

class Waveform {
public:
	Waveform();
	void Pass(const IAudioFile<float>::AudioBuffer);
	using signal_t = boost::signals2::signal <void (float, double)>;
	boost::signals2::connection connect(const signal_t::slot_type &subscriber);

private:
	Fl_Chart WaveformChart;
	Fl_Slider Slider;
	Fl_Button ZoomInH;
	Fl_Button ZoomOutH;
	Fl_Button ZoomInV;
	Fl_Button ZoomOutV;
	Fl_AudioFile<float>::AudioBuffer AudioTrack;
	signal_t SliderSignal;
	int AudioLength;

	void EmitSignal();
	static void CbSlider(Fl_Widget*, void*);
	static void CbZoomInH(Fl_Widget*, void*);
	static void CbZoomOutH(Fl_Widget*, void*);
	static void CbZoomInV(Fl_Widget*, void*);
	static void CbZoomOutV(Fl_Widget*, void*);
	void Draw(double ZoomFactor);
	void VerticalScale(double VertFactor, bool ClearChart);
};
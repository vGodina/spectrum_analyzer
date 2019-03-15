#include <boost/signals2.hpp>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Slider.H>
#include "Fl_AudioFile.h"

class Waveform {
public:
	Waveform();
	using signal_t = boost::signals2::signal <void(int)>;
	// Passes AudioBuffer into Waveform
	bool GetAudio(const IAudioFile<float>::AudioBuffer*);
	// Method to connect Waveform signal with 
	boost::signals2::connection connect(const signal_t::slot_type &subscriber);

private:
	Fl_Chart WaveformChart;
	Fl_Slider Slider;
	Fl_Button ZoomInH;
	Fl_Button ZoomOutH;
	Fl_Button ZoomInV;
	Fl_Button ZoomOutV;

	static void CbSlider(Fl_Widget*, void*);
	static void CbZoomInH(Fl_Widget*, void*);
	static void CbZoomOutH(Fl_Widget*, void*);
	static void CbZoomInV(Fl_Widget*, void*);
	static void CbZoomOutV(Fl_Widget*, void*);

	signal_t SliderSignal;
	void EmitSignal();

	int CenterSample;
	int AudioLength;
	const Fl_AudioFile<float>::AudioBuffer* AudioTrack;
	bool Draw(double ZoomFactor);
	void VerticalScale(double VertFactor, bool ClearChart);
};
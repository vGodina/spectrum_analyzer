#ifndef WAVEFORM
#define WAVEFORM

#include <fltk/Fl_Button.h>
#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Slider.H>

class Waveform {
public:
	Waveform();
	~Waveform();
	//void Redraw(AudioFile<float>*);
private:
	Fl_Chart WaveformChart;
	Fl_Slider Slider;
	Fl_Button ZoomInH;
	Fl_Button ZoomOutH;
	Fl_Button ZoomInV;
	Fl_Button ZoomOutV;

	static void CbZoomInH(Fl_Widget*, void*);
	static void CbZoomOutH(Fl_Widget*, void*);
	static void CbZoomInV(Fl_Widget*, void*);
	static void CbZoomOutV(Fl_Widget*, void*);
	static void CbSlider(Fl_Widget*, void*);
	//inline static AudioFile<float>* AudioPtr(Fl_Widget*);
	void ChartRedraw(float ZoomFactor);
	void VerticalScale(float VertFactor, bool ClearChart);
};

#endif WAVEFORM
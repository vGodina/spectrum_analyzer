#include <fltk/Fl_Button.h>
#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Slider.H>

class Waveform {
public:
	Waveform();
	~Waveform();
private:
	std::unique_ptr<Fl_Chart>WaveformChart;
	std::unique_ptr<Fl_Slider>Slider;
	std::unique_ptr<Fl_Button>ZoomInH;
	std::unique_ptr<Fl_Button>ZoomOutH;
	std::unique_ptr<Fl_Button>ZoomInV;
	std::unique_ptr<Fl_Button>ZoomOutV;

	static void CbZoomInH(Fl_Widget*, void*);
	static void CbZoomOutH(Fl_Widget*, void*);
	static void CbZoomInV(Fl_Widget*, void*);
	static void CbZoomOutV(Fl_Widget*, void*);
	static void CbSlider(Fl_Widget*, void*);
	inline static AudioFile<float>* AudioPtr(Fl_Widget*);
	void ChartRedraw(AudioFile<float>*, float ZoomFactor);
	void VerticalScale(float VertFactor, bool ClearChart);

};
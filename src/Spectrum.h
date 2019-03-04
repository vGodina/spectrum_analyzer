#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Choice.H>
#include <audiofft/AudioFFT.h>

class Spectrum {
public:
	Spectrum();
	~Spectrum();
private:
	Fl_Chart SpectrumChart;
	Fl_Chart LevelMeter;
	Fl_Choice SizeFFT;
	audiofft::AudioFFT FFT;

	static void CbSizeFFT(Fl_Widget*, void*);
	void DoFFT();
};
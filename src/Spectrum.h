#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Choice.H>
#include <audiofft/AudioFFT.h>

class Spectrum {
public:
	Spectrum();
	~Spectrum();
private:
	std::unique_ptr<Fl_Chart>SpectrumChart;
	std::unique_ptr<Fl_Chart>LevelMeter;
	std::unique_ptr<Fl_Choice>SizeFFT;
	std::unique_ptr<audiofft::AudioFFT>FFT;

	static void CbSizeFFT(Fl_Widget*, void*);
	void DoFFT(Fl_AudioFile*);
};
#include <audiofft/AudioFFT.h>
#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Choice.H>

class Spectrum {
public:
	Spectrum();
	void Show(const AudioFile<float>*);
	void SetSliderSize(double);
	void SetSliderValue(double);
private:
	Fl_Chart SpectrumChart;
	Fl_Chart LevelMeter;
	Fl_Choice FFTChoice;
	audiofft::AudioFFT FFT;
	const AudioFile<float>* AudioTrack;
	int FFTSize;
	double SliderSize;
	double SliderValue;

	static void CbFFTChoice(Fl_Widget*, void*);
	void Draw();
	void InitFFT();
};
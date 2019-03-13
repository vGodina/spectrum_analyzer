#include <audiofft/AudioFFT.h>
#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Choice.H>
#include "Fl_AudioFile.h"

class Spectrum {
public:
	Spectrum();
	void GetAudio(const IAudioFile<float>::AudioBuffer*);
	void SetSlider(float, double);
private:
	Fl_Chart SpectrumChart;
	Fl_Chart LevelMeter;
	Fl_Choice FFTChoice;
	audiofft::AudioFFT FFT;

	const Fl_AudioFile<float>::AudioBuffer* AudioTrack;
	int FFTSize;
	double SliderSize;
	double SliderValue;

	static void CbFFTChoice(Fl_Widget*, void*);
	void Draw();
	void InitFFT();
};
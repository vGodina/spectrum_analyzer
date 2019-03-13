#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Choice.H>
#include "Fl_AudioFile.h"
#include "LevelMeter.h"
#include "FFTHandler.h"

class Spectrum {
public:
	Spectrum();
	int GetAudio(const IAudioFile<float>::AudioBuffer*);
	void GetPosition(int);
private:
	Fl_Chart SpectrumChart;
	Fl_Choice FFTChoice;
	LevelMeter LMeter;
	FFTHandler FFT;
	
	const Fl_AudioFile<float>::AudioBuffer* AudioTrack;
	int FFTSize;
	int CenterSample;
	static void CbFFTChoice(Fl_Widget*, void*);
	void Draw();
	void InitFFT();

};
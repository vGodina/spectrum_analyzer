#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Choice.H>
#include "Fl_AudioFile.h"
#include "LevelMeter.h"
#include "FFTHandler.h"

class Spectrum {
public:
	Spectrum();
	bool GetAudio(const IAudioFile<float>::AudioBuffer&);
	void GetPosition(int);
private:
	Fl_Choice FFTChoice;
	Fl_Chart SpectrumChart;
	LevelMeter LMeter;
	FFTHandler FFT;
	const Fl_AudioFile<float>::AudioBuffer* AudioTrack;
	int FFTSize;

	static void CbFFTChoice(Fl_Widget*, void*);
	void CheckFFTSize();
	void Draw();
};
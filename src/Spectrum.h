#include <fltk/Fl_Chart.H>
#include <fltk/Fl_Choice.H>
#include <fltk/Fl_Group.H>
#include "IAudioFile.h"
#include "ISpectrum.h"
#include "LevelMeter.h"
#include "FFTHandler.h"

class Spectrum : public ISpectrum {
public:
	Spectrum(std::unique_ptr<Fl_Group> FlGroup);
	bool TakeAudioData(const IAudioFile<float>::AudioBuffer&);
	bool SetPosition(int);
	Fl_Group* GetImplWidget() override;
private:
	std::unique_ptr<Fl_Group> Group;
	Fl_Choice FFTChoice;
	Fl_Chart SpectrumChart;
	LevelMeter LMeter;
	FFTHandler FFT;
	const IAudioFile<float>::AudioBuffer* AudioTrack;
	int FFTSize;

	static void CbFFTChoice(Fl_Widget*, void*);
	void CheckFFTSize();
	void Draw();
};
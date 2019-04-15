#include <fltk/Fl_Group.H>
#include "IAudioFile.h"
#include "ISpectrum.h"
#include "IChart.h"
#include "IChoice.h"
#include "ILevelMeter.h"
#include "IFFTHandler.h"

class Spectrum : public ISpectrum {
public:
	Spectrum (
		std::unique_ptr<IChart> Chart,
		std::unique_ptr<IChoice> Choice,
		std::unique_ptr <IFFTHandler> Fft,
		std::unique_ptr<ILevelMeter> Meter);

	bool SetAudioData(const IAudioFile<float>::AudioBuffer&);

	bool SetPosition(int);

	Fl_Group* GetImplWidget() override;

	void SetGeometry(int x, int y, int w, int h) override;
private:
	Fl_Group Group;

	std::unique_ptr <IChart> SpectrumChart;
	std::unique_ptr <IChoice> FFTChoice;
	std::unique_ptr <ILevelMeter> LMeter;
	std::unique_ptr <IFFTHandler> FFT;

	const IAudioFile<float>::AudioBuffer* AudioTrack;

	int FFTSize;

	static void CbFFTChoice(Fl_Widget*, void*);
	void CheckFFTSize();
	void Draw();
};
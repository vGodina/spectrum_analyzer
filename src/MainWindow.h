#include <fltk/Fl.H>
#include <fltk/Fl_Double_Window.H>
#include "IMenu.h"
#include "IAudioFile.h"
#include "IWaveform.h"
#include "ISpectrum.h"

class MainWindow : public Fl_Double_Window {
public:
	MainWindow(int w, int h, const char* title, IMenu* mainMenu, IAudioFile<float>* AudioTrk, IWaveForm* WaveForm, ISpectrum* SpectraForm);
private:
	IAudioFile<float>* AudioTrack;
	IMenu* MainMenu;
	IWaveForm* WaveFrm;
	ISpectrum* SpectraFrm;

	boost::signals2::connection  MenuConnection;
	boost::signals2::connection  SliderInteraction;

	bool AudioFileHandler (std::string FileName);
	void SliderHandler (double CenterSample);
};
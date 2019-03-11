#include <fltk/Fl.H>
#include <fltk/Fl_Double_Window.H>
#include "Menu.h"
#include "Spectrum.h"
#include "Waveform.h"
#include "Fl_AudioFile.h"

class MainWindow : public Fl_Double_Window {
public:
	MainWindow(int w, int h, const char* title);
private:
	Fl_AudioFile<float> AudioTrack;
	Waveform WaveFrm;
	Spectrum SpectraFrm;
	Menu MainMenu;
	boost::signals2::connection  MenuConnection;
	boost::signals2::connection  SliderConnection;

	bool HandleAudioFile (std::string FileName);
	void HandleSlider (float SliderSize, double SliderValue);
};
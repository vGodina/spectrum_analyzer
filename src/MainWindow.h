#include <audiofile/AudioFile.h>
#include <fltk/Fl.H>
#include <fltk/Fl_Double_Window.H>
#include "Menu.h"
#include "Spectrum.h"
#include "Waveform.h"

class MainWindow : public Fl_Double_Window {
public:
	MainWindow(int w, int h, const char* title);
private:
	AudioFile <float> AudioTrack;
	Waveform WaveFrm;
	Spectrum SpectraFrm;
	Menu MainMenu;
	boost::signals2::connection  MenuConnection;
	boost::signals2::connection  SliderConnection;

	void HandleAudioFile (std::string FileName);
	void HandleSlider (float SliderSize, double SliderValue);
};
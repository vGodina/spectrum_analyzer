#include <fltk/Fl.H>
#include <fltk/Fl_Double_Window.H>
#include "Fl_AudioFile.h"
#include "Menu.h"
#include "Spectrum.h"
#include "Waveform.h"

class MainWindow : public Fl_Double_Window {
public:
	MainWindow(int w, int h, const char* title);
	~MainWindow();
	void LoadAudio();
private:
	Fl_AudioFile AudioTrack;
	Waveform WaveFrm;
	Spectrum SpectraFrm;
	Menu MainMenu;
	boost::signals2::connection  MenuConnection;
};
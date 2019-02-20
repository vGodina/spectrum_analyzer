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
private:
	std::unique_ptr<Fl_AudioFile>AudioTrack;
	std::unique_ptr<Waveform>Wave;
	std::unique_ptr<Spectrum>Spectra;
	std::unique_ptr<Menu>MainMenu;
};
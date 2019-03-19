#include <fltk/Fl.H>
#include <fltk/Fl_Double_Window.H>
#include "IMenu.h"
#include "Spectrum.h"
#include "Waveform.h"
#include "Fl_AudioFile.h"

class MainWindow : public Fl_Double_Window {
public:
	MainWindow(int w, int h, const char* title, IMenu* mainMenu);
private:
	Fl_AudioFile <float> AudioTrack;
	Waveform WaveFrm;
	Spectrum SpectraFrm;
	IMenu* MainMenu;

	boost::signals2::connection  MenuConnection;
	boost::signals2::connection  SliderInteraction;

	bool AudioFileHandler (std::string FileName);
	void SliderHandler (double CenterSample);
};
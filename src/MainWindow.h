#include <fltk/Fl.H>
#include <fltk/Fl_Double_Window.H>
#include "IMenu.h"
#include "IAudioFile.h"
#include "IWaveform.h"
#include "ISpectrum.h"

class MainWindow : public Fl_Double_Window {
public:
	MainWindow(int w, int h, const char* title,
		std::unique_ptr<IMenu> &&,
		std::unique_ptr<IWaveForm> &&,
		std::unique_ptr<ISpectrum> &&,
		std::unique_ptr<IAudioFile<float>> && );
private:
	std::unique_ptr <IMenu> MainMenu;
	std::unique_ptr <IWaveForm> WaveFrm;
	std::unique_ptr <ISpectrum> SpectraFrm;
	std::unique_ptr <IAudioFile<float>> AudioTrack;

	boost::signals2::connection  MenuConnection;
	boost::signals2::connection  SliderInteraction;

	bool AudioFileHandler (std::string FileName);
	void SliderHandler (double CenterSample);
};
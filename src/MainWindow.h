#include <fltk/Fl.H>
#include <fltk/Fl_Double_Window.H>
#include "IMenu.h"
#include "IAudioFile.h"
#include "IWaveform.h"
#include "ISpectrum.h"

class MainWindow : public Fl_Double_Window {
public:
	MainWindow(int w, int h, const char* title, IAudioFile<float>* AudioTrk, std::unique_ptr<IMenu>&& mainMenu, std::unique_ptr<IWaveForm>&& WaveForm, std::unique_ptr<ISpectrum>&& SpectrumForm);
private:
	std::unique_ptr<IMenu> MainMenu;
	std::unique_ptr <IWaveForm> WaveFrm;
	std::unique_ptr <ISpectrum> SpectraFrm;
	IAudioFile<float>* AudioTrack;

	boost::signals2::connection  MenuConnection;
	boost::signals2::connection  SliderInteraction;

	bool AudioFileHandler (std::string FileName);
	void SliderHandler (double CenterSample);
};
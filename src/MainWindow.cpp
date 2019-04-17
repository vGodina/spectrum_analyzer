#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow (
	std::unique_ptr<IMenu> Menu,
	std::unique_ptr<IWaveForm> WaveForm,
	std::unique_ptr<ISpectrum> Spectrum,
	std::unique_ptr<IAudioFile<float>> AudioFile) :
		Fl_Double_Window { 0, 0, "Spectrum Analyzer" },
		MainMenu { std::move(Menu) },
		WaveFrm { std::move(WaveForm) },
		SpectraFrm {std::move(Spectrum)},
		AudioTrack {std::move(AudioFile)},
		AudioIsLoaded(false)
{
	add(MainMenu->GetImplWidget());
	add(WaveFrm->GetImplWidget());
	add(SpectraFrm->GetImplWidget());

	// Connecting MainMenu signal with HandleAudio function. _1 allocates placeholder for passing value of file path
	MenuConnection = MainMenu->connect(boost::bind(&MainWindow::AudioFileHandler, this, _1));
	// Connecting Waveform slider's movement with its MainWindow Handler: update Spectrum chart
	SliderInteraction = WaveFrm->connect(boost::bind(&MainWindow::SliderHandler, this, _1));

	resizable(this);
	Fl::visual(FL_DOUBLE | FL_INDEX);
	show();
}

bool MainWindow::AudioFileHandler (std::string FileName)
{
	AudioIsLoaded = AudioTrack->Load(FileName);
	if (AudioIsLoaded) {
		WaveFrm->SetAudioData(AudioTrack->GetData());
		SliderHandler(0.5);
	}
	return AudioIsLoaded;
}
 
bool MainWindow::SliderHandler (double CenterValue)
{
	if (AudioIsLoaded) {
		unsigned int CenterSample = static_cast<unsigned int>(CenterValue * AudioTrack->GetLength());
		SpectraFrm->SetPosition(CenterSample);
		SpectraFrm->SetAudioData(AudioTrack->GetData());
	}
	return AudioIsLoaded;
}

void MainWindow::SetGeometry(int x, int y, int w, int h)
{
	resize(x, y, w, h);

	// Window Layout Calculation
	int MenuX = w / 20;
	int MenuY = h / 20;
	int MenuW = w / 6;
	int MenuH = h / 20;

	int WavX = w / 30;
	int WavY = h / 6;
	int WavW = 527 * w / 600;
	int WavH = 247 * h / 600;

	int SpX = w / 30;
	int SpY = 3 * h / 5;
	int SpW = 5 * w / 6;
	int SpH = 37 * h / 100;

	MainMenu->SetGeometry(MenuX, MenuY, MenuW, MenuH);
	WaveFrm->SetGeometry(WavX, WavY, WavW, WavH);
	SpectraFrm->SetGeometry(SpX, SpY, SpW, SpH);
}
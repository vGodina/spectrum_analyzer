#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow (int w, int h, const char* title,
	std::unique_ptr<IMenu>&& IMenu,
	std::unique_ptr<IWaveForm> && IWaveForm,
	std::unique_ptr<ISpectrum> && ISpectrum,
	std::unique_ptr<IAudioFile<float>> && IAudioFile) :

	Fl_Double_Window (w, h, title),
	MainMenu(std::move(IMenu)),
	WaveFrm(std::move(IWaveForm)),
	SpectraFrm(std::move(ISpectrum)),
	AudioTrack(std::move(IAudioFile))
{
	add(MainMenu->getImplementatioWidget());
	add(WaveFrm->getImplementatioWidget());
	add(SpectraFrm->getImplementatioWidget());
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
	bool Loaded = AudioTrack->Load(FileName);
	WaveFrm->TakeAudioData(AudioTrack->PassData());
	SliderHandler(AudioTrack->GetLength() / 2);
	return Loaded;
}
 
void MainWindow::SliderHandler (double CenterValue)
{
	if (AudioTrack->IsLoaded()) {
		int CenterSample = static_cast<int>(CenterValue * AudioTrack->GetLength());
		SpectraFrm->GetPosition(CenterSample);
		SpectraFrm->TakeAudioData(AudioTrack->PassData());
	}
}
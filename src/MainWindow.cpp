#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow (int w, int h, const char* title,
	std::unique_ptr<IMenu> Menu,
	std::unique_ptr<IWaveForm> WaveForm,
	std::unique_ptr<ISpectrum> Spectrum,
	std::unique_ptr<IAudioFile<float>> AudioFile) :
		Fl_Double_Window { w, h, title },
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
		WaveFrm->TakeAudioData(AudioTrack->PassData());
		SliderHandler(0.5);
	}
	return AudioIsLoaded;
}
 
bool MainWindow::SliderHandler (double CenterValue)
{
	if (AudioIsLoaded) {
		int CenterSample = static_cast<int>(CenterValue * AudioTrack->GetLength());
		SpectraFrm->SetPosition(CenterSample);
		SpectraFrm->TakeAudioData(AudioTrack->PassData());
	}
	return AudioIsLoaded;
}
#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow (int w, int h, const char* title) : Fl_Double_Window (w, h, title),
	AudioTrack(),
	WaveFrm(),
	SpectraFrm(),
	MainMenu()
{
	// Connecting MainMenu signal with HandleAudio function. _1 allocates placeholder for passing value of file path
	MenuConnection = MainMenu.connect(boost::bind(&MainWindow::AudioFileHandler, this, _1));
	// Connecting Waveform slider's movement with its MainWindow Handler: update Spectrum chart
	SliderInteraction = WaveFrm.connect(boost::bind(&MainWindow::SliderHandler, this, _1));

	resizable(this);
	Fl::visual(FL_DOUBLE | FL_INDEX);
	show();
}

bool MainWindow::AudioFileHandler (std::string FileName)
{
	bool Loaded = AudioTrack.Load(FileName);
	WaveFrm.GetAudio(AudioTrack.PassData());
	SliderHandler(AudioTrack.GetLength() / 2);
	return Loaded;
}
 
void MainWindow::SliderHandler (double CenterValue)
{
	if (AudioTrack.IsLoaded()) {
		int CenterSample = static_cast<int>(CenterValue * AudioTrack.GetLength());
		SpectraFrm.GetPosition(CenterSample);
		SpectraFrm.GetAudio(AudioTrack.PassData());
	}
}
#include "MainWindow.h"
#include <iostream>
MainWindow::MainWindow(int w, int h, const char* title) : Fl_Double_Window(w, h, title),
	AudioTrack(),
	WaveFrm(),
	SpectraFrm(),
	MainMenu()
{
	//Connecting MainMenu signal with HandleAudio function. _1 allocates placeholder for passing value
	MenuConnection = MainMenu.connect(boost::bind(&MainWindow::HandleAudioFile, this, _1));
	SliderConnection = WaveFrm.connect(boost::bind(&MainWindow::HandleSlider, this, _1, _2));
	// Interior initialization
	SpectraFrm.SetSlider(1.0, 0.5);
	resizable(this);
	Fl::visual(FL_DOUBLE | FL_INDEX);
	show();
}

bool MainWindow::HandleAudioFile(std::string FileName)
{
	bool Loaded = AudioTrack.load(FileName);
	WaveFrm.Pass(AudioTrack.GetData());
	SpectraFrm.Pass(AudioTrack.GetData());
	return Loaded;
}

void MainWindow::HandleSlider(float SliderSize, double SliderValue)
{
	SpectraFrm.SetSlider(SliderSize, SliderValue);
	SpectraFrm.Pass(AudioTrack.GetData());
}
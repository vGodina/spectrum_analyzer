#include <fltk/names.h>
#include "MainWindow.h"

MainWindow::MainWindow(int w, int h, const char* title) : Fl_Double_Window(w, h, title),
	AudioTrack(), WaveFrm(), SpectraFrm(), MainMenu()
{
	//Connecting MainMenu signal with LoadAudio function
	MenuConnection = MainMenu.connect(boost::bind(&MainWindow::LoadAudio, this));
	SliderConnection = WaveFrm.connect(boost::bind(&MainWindow::SliderHandler, this));
	resizable(this);
	Fl::visual(FL_DOUBLE | FL_INDEX);
	show();
}

void MainWindow::LoadAudio(std::string FileName)
{
	AudioTrack.load(FileName);
	WaveFrm.Show(AudioTrack);
	SpectraFrm.Show(AudioTrack);
}

void MainWindow::SliderHandler()
{
	SpectraFrm.SetSliderSize(WaveFrm.GetSliderSize());
	SpectraFrm.SetSliderValue(WaveFrm.GetSliderValue());
	SpectraFrm.Show(AudioTrack);
}
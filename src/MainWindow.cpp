#include <fltk/names.h>
#include "MainWindow.h"

MainWindow::MainWindow(int w, int h, const char* title) : Fl_Double_Window(w, h, title),
	AudioTrack(), WaveFrm(), SpectraFrm(), MainMenu()
{
	//Connecting MainMenu signal with LoadAudio function
	MenuConnection = MainMenu.connect(boost::bind(&MainWindow::LoadAudio, this, _1));
	SliderConnection = WaveFrm.connect(boost::bind(&MainWindow::SliderHandler, this, _1, _2));
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

void MainWindow::SliderHandler(double SliderSize, double SliderValue)
{
	SpectraFrm.SetSliderSize(SliderSize);
	SpectraFrm.SetSliderValue(SliderValue);
	SpectraFrm.Show(AudioTrack);
}
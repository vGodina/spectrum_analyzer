#include "MainWindow.h"
#include <fltk/names.h>

MainWindow::MainWindow(int w, int h, const char* title) : Fl_Double_Window(w, h, title),
	AudioTrack(), WaveFrm(), SpectraFrm(), MainMenu()
{
	//Connecting MainMenu signal with LoadAudio function
	MenuConnection = MainMenu.connect(boost::bind(&MainWindow::LoadAudio, this));
	resizable(this);
	Fl::visual(FL_DOUBLE | FL_INDEX);
	show();
}

MainWindow::~MainWindow() {}

void MainWindow::LoadAudio()
{
	AudioTrack.AudioTrack.load(MainMenu.GetFilename());
}
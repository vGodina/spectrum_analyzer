#include "MainWindow.h"

MainWindow::MainWindow(int w, int h, const char* title) :
	Fl_Double_Window(w, h, title),
	AudioTrack(std::make_unique<Fl_AudioFile>()),
	Wave(std::make_unique<Waveform>()),
	Spectra(std::make_unique<Spectrum>()),
	MainMenu(std::make_unique<Menu>())
{
	resizable(this);
	Fl::visual(FL_DOUBLE | FL_INDEX);
	show();
}

MainWindow::~MainWindow() {}
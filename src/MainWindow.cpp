#include "MainWindow.h"
#include <string>

MainWindow::MainWindow(int w, int h, const char* title) : Fl_Window(w, h, title),
	OpenButton(std::make_unique<Fl_Button>(30, 30, 100, 30, "Open .wav file")),
	FileInfo(std::make_unique<Fl_Box>(200, 30, 220, 30, "000")),
	Chooser(std::make_unique<Fl_Native_File_Chooser>()),
	Chart(std::make_unique<Fl_Chart>(20, 100, 400, 200, "Waveform")),
	AudioTrack(std::make_unique<AudioFile<double>>())
{
	begin();
	OpenButton->callback(CbOpenButton, this);
	// Initialization of  widgets
	Chart->color(FL_WHITE);
	Chart->type(FL_LINE_CHART);
	Chooser->filter("*.wav");
	end();
	resizable(this);
	show();
}

MainWindow::~MainWindow() {}

void MainWindow::CbOpenButton(Fl_Widget* OpenButton, void* Obj)
{
	static_cast<MainWindow*>(Obj)->ChooserShow();
}

void MainWindow::ChooserShow()
{
	Chooser->show();
	AudioTrack->load(Chooser->filename());
	//Print duration of AudioTrack in seconds
	std::string FileDuration = std::to_string(AudioTrack->getLengthInSeconds());
	std::string LabelMessage = "File duration: " + FileDuration + " seconds";
	FileInfo->copy_label(LabelMessage.c_str());
	FileInfo->redraw();
	// Plot waveform of AudioTrack in Chart widget.
	Chart->clear();
	//	Reducing AudioTrack vector's number of points to PlotCnt.
	int PlotCnt = 2000;
	//	RedCoef - Reduction Coefficient. Helps to plot big vectors
	int RedCoef = AudioTrack->getNumSamplesPerChannel() / PlotCnt;
	for (int i = 0; i < PlotCnt; i++)
	{
		double val = AudioTrack->samples[0][i * RedCoef];
		Chart->add(val);
	}
}
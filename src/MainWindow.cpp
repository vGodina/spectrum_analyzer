#include "MainWindow.h"
#include <string>
#include <memory>

MainWindow::MainWindow(int w, int h, const char* title) : Fl_Window(w, h, title),
OpenButton(new Fl_Button(100, 30, 100, 30, "Open .wav file")),
FileInfo(new Fl_Box(40, 100, 220, 30, "000")),
Chooser(new Fl_Native_File_Chooser()),
AudioTrack(new AudioFile<float>)
{
	begin();
	OpenButton->callback(CbOpenButton, this);
	end();
	resizable(this);
	show();
}

MainWindow::~MainWindow() {}

void MainWindow::CbOpenButton(Fl_Widget* OpenButton, void* Obj)
{
	((MainWindow*)Obj)->ChooserShow();
}

void MainWindow::ChooserShow()
{
	Chooser->filter("*.wav");
	Chooser->show();
	AudioTrack->load(Chooser->filename());
	std::string FileDuration = std::to_string(AudioTrack->getLengthInSeconds());
	std::string LabelMessage = "File duration: " + FileDuration + " seconds";
	FileInfo->copy_label(LabelMessage.c_str());
	FileInfo->redraw();
}
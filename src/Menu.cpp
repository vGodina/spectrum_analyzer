#include <fltk/Fl_Double_Window.H>
#include "Fl_AudioFile.h"
#include "Menu.h"

Menu::Menu() :
	OpenButton(std::make_unique<Fl_Button>(30, 30, 100, 30, "Open .wav file")),
	FileInfo(std::make_unique<Fl_Box>(200, 30, 220, 30, "000")),
	Chooser(std::make_unique<Fl_Native_File_Chooser>())
{
	OpenButton->callback(CbOpenButton, this);
	Chooser->filter("*.wav");
}

Menu::~Menu() {}

void Menu::CbOpenButton(Fl_Widget* OpenButton, void* Obj)
{
	// Get pointer to Group and Window
	Fl_Widget* Widget = static_cast<Fl_Widget*>(OpenButton);
	Fl_Double_Window* Window = static_cast<Fl_Double_Window*>(Widget->parent());
	Fl_AudioFile* AudioTrack = static_cast<Fl_AudioFile*>(Window->child(0));
	static_cast<Menu*>(Obj)->ChooserShow(AudioTrack->GetAudio());
}

void Menu::ChooserShow(AudioFile<float>* AudioTrack)
{
	Chooser->show();
	AudioTrack->load(Chooser->filename());
	std::string FileDuration = std::to_string(AudioTrack->getLengthInSeconds());
	std::string LabelMessage = "File duration: " + FileDuration + " seconds";
	FileInfo->copy_label(LabelMessage.c_str());
	FileInfo->redraw();
	/*
	Slider->slider_size(1);
	WaveformChart->clear();
	WaveformChart->bounds(-1, 1);
	SpectrumChart->clear();
	ChartRedraw();	*/
}

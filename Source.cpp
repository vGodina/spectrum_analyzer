#include "fltk/Fl.h"
#include "fltk/Fl_Box.h"
#include "fltk/Fl_Window.H"
#include "fltk/Fl_Button.h"
#include "fltk/Fl_Native_File_Chooser.h"
#include "audiofile/AudioFile.h"
#include <string>

Fl_Box box(10, 10, 200, 200, "");
AudioFile <float> audioFile;

void whenPushed(Fl_Widget* but, void*)
{
	// Configuring File Chooser widget
	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser();
	chooser->type(Fl_Native_File_Chooser::BROWSE_FILE);
	chooser->title("Open a file");
	chooser->filter("*.wav");
	chooser->show();
	// getting audiofile path from File Chooser to AudioFile object
	audioFile.load(chooser->filename());
	// printing audiofile duration
	std::string fileDuration = std::to_string(audioFile.getLengthInSeconds());
	std::string labelMessage = "File duration: " + fileDuration + " seconds";
	box.copy_label(labelMessage.c_str());
	box.redraw();
}

int main()
{
	Fl_Window* window = new Fl_Window(400, 200, "Check audio file duration");
	Fl_Button* open_button = new Fl_Button(110, 10, 100, 20, "open .wav file");
	window->add(box);
	open_button->callback(whenPushed);
	window->show();
	return Fl::run();
}
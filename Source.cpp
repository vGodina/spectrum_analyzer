#include <fltk/Fl.h>
#include <fltk/Fl_Box.h>
#include <fltk/Fl_Window.H>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>
#include <audiofile/AudioFile.h>
#include <string>

class myWindow : public Fl_Window
{
public:
	myWindow(int w, int h, const char* title);
	~myWindow();
	Fl_Button* open_button;
	Fl_Native_File_Chooser* chooser;
	Fl_Box* box;
	AudioFile <float> audioFile;

private:
	static void cb_open_button(Fl_Widget*, void*);
	inline void chooser_show();
};

int main()
{
	myWindow win(300, 200, "Spectrum Analyzer");
	return Fl::run();
}

myWindow::myWindow(int w, int h, const char* title) :Fl_Window(w, h, title)
{
	begin();
	open_button = new Fl_Button(100, 30, 100, 30, "Open .wav file");
	chooser = new Fl_Native_File_Chooser();
	chooser->title("Open a file");
	chooser->filter("*.wav");
	open_button->callback(cb_open_button, this);
	box = new Fl_Box(40, 100, 220, 30, "000");
	end();
	resizable(this);
	show();
}
//----------------------------------------------------
myWindow::~myWindow() {}

void myWindow::cb_open_button(Fl_Widget* openButton, void* obj)
{
	((myWindow*)obj)->chooser_show();
}

void myWindow::chooser_show()
{
	chooser->show();
	audioFile.load(chooser->filename());
	std::string fileDuration = std::to_string(audioFile.getLengthInSeconds());
	std::string labelMessage = "File duration: " + fileDuration + " seconds";
	box->copy_label(labelMessage.c_str());
	box->redraw();
}
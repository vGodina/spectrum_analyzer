#include <fltk/Fl.h>
#include <fltk/Fl_Box.h>
#include <fltk/Fl_Window.H>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>
#include <audiofile/AudioFile.h>
#include <string>

class MainWindow : public Fl_Window {
public:
	MainWindow(int w, int h, const char* title);
	~MainWindow();
	Fl_Button* OpenButton;
	Fl_Native_File_Chooser* Chooser;
	Fl_Box* FileInfo;
	AudioFile <float> AudioTrack;
	
private:
	static void CbOpenButton(Fl_Widget*, void*);
	inline void ChooserShow();
};

MainWindow::MainWindow(int w, int h, const char* title) :Fl_Window(w, h, title)
{
	begin();
	Chooser = new Fl_Native_File_Chooser();
	Chooser->title("Open a file");
	Chooser->filter("*.wav");
	OpenButton = new Fl_Button(100, 30, 100, 30, "Open .wav file");
	OpenButton->callback(CbOpenButton, this);
	FileInfo = new Fl_Box(40, 100, 220, 30, "000");
	end();
	resizable(this);
	show();
}
//----------------------------------------------------
MainWindow::~MainWindow() {}

void MainWindow::CbOpenButton(Fl_Widget* OpenButton, void* Obj)
{
	((MainWindow*)Obj)->ChooserShow();
}

void MainWindow::ChooserShow()
{
	Chooser->show();
	AudioTrack.load(Chooser->filename());
	std::string FileDuration = std::to_string(AudioTrack.getLengthInSeconds());
	std::string LabelMessage = "File duration: " + FileDuration + " seconds";
	FileInfo->copy_label(LabelMessage.c_str());
	FileInfo->redraw();
}
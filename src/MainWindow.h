#include <fltk/Fl.h>
#include <fltk/Fl_Box.h>
#include <fltk/Fl_Window.H>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>
#include <audiofile/AudioFile.h>

class MainWindow : public Fl_Window {
public:
	MainWindow(int w, int h, const char* title);
	~MainWindow();
private:
	Fl_Button* OpenButton;
	Fl_Native_File_Chooser* Chooser;
	Fl_Box* FileInfo;
	AudioFile <float> AudioTrack;
	
	static void CbOpenButton(Fl_Widget*, void*);
	void ChooserShow();
};
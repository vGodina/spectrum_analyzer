#include <fltk/Fl.h>
#include <fltk/Fl_Box.h>
#include <fltk/Fl_Window.H>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>
#include <audiofile/AudioFile.h>
#include <string>
#include <MainWindow.h>

int main()
{
	MainWindow BaseWindow(300, 200, "Spectrum Analyzer");
	return Fl::run();
}
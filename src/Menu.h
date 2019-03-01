#include <fltk/Fl_Box.h>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>

class Menu {
public:
	Menu();
	~Menu();
private:
	std::unique_ptr<Fl_Button>OpenButton;
	std::unique_ptr<Fl_Box>FileInfo;
	std::unique_ptr<Fl_Native_File_Chooser>Chooser;

	static void CbOpenButton(Fl_Widget*, void*);
	void ChooserShow(std::shared_ptr<AudioFile<float>>);
};


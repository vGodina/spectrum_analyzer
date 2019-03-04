#include <fltk/Fl_Box.h>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>
#include <boost/signals2.hpp>


class Menu {

public:
	typedef boost::signals2::signal<void ()>  signal_t;
	boost::signals2::connection connect(const signal_t::slot_type &subscriber);
	std::string GetFilename();

public:
	Menu();
	~Menu();
	
private:
	Fl_Native_File_Chooser Chooser;
	Fl_Button OpenButton;
	Fl_Box FileInfo;
	
	static void CbOpenButton(Fl_Widget*, void*);
	
	signal_t MenuSignal;
	void Emit();
};
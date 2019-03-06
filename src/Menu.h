#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>
#include <boost/signals2.hpp>

class Menu {
public:
	Menu();
	using signal_t = boost::signals2::signal <void (std::string)>;
	boost::signals2::connection connect (const signal_t::slot_type &slot);
private:
	Fl_Native_File_Chooser Chooser;
	Fl_Button OpenButton;
	signal_t MenuSignal;

	static void CbOpenButton(Fl_Widget*, void*);
	void Emit();
};
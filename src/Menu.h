#include <boost/signals2.hpp>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Group.H>
#include <fltk/Fl_Native_File_Chooser.h>
#include "IMenu.h"

class Menu : public IMenu, public Fl_Group {
public:
	Menu();
	boost::signals2::connection connect (const signal_t::slot_type &slot);
private:
	Fl_Native_File_Chooser Chooser;
	Fl_Button OpenButton;
	signal_t MenuSignal;

	static void CbOpenButton(Fl_Widget*, void*);
	void Emit();
};
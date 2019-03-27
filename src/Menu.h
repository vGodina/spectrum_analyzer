#include <boost/signals2.hpp>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Group.H>
#include <fltk/Fl_Native_File_Chooser.h>
#include "IMenu.h"
#include "RFileChooser.h"

class Menu : public Fl_Group, public IMenu {
public:
	Menu();
	boost::signals2::connection connect (const signal_t::slot_type &slot);
	Fl_Group* getImplWidget() override;

private:
	Fl_Native_File_Chooser r;
	//std::unique_ptr<RFileChooser> Chooser;
	RFileChooser Chooser;
	Fl_Button OpenButton;
	signal_t MenuSignal;

	static void CbOpenButton(Fl_Widget*, void*);
	void Emit();
};
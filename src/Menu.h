#include <boost/signals2.hpp>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Group.H>
#include <fltk/Fl_Native_File_Chooser.h>
#include "IMenu.h"
#include "IFileChooser.h"
#include "IButton.h"

class Menu : public IMenu {
public: 
	Menu(int x, int y, int w, int h, std::unique_ptr<IFileChooser> FileChooser, std::unique_ptr<IButton> Button);

	boost::signals2::connection connect (const signal_t::slot_type &slot);
	
	Fl_Group* GetImplWidget() override;

private:
	Fl_Group Group;
	std::unique_ptr<IFileChooser> Chooser;
	std::unique_ptr<IButton> OpenButton;

	signal_t MenuSignal;

	static void CbOpenButton(Fl_Widget*, void*);
	void Emit();
};
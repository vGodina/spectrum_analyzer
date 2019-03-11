#include "Menu.h"
#include <iostream>

Menu::Menu() :
	Chooser(),
	OpenButton (30, 30, 100, 30, "Open .wav file")
{
	OpenButton.callback (CbOpenButton, this);
	Chooser.filter("*.wav");
}

void Menu::CbOpenButton(Fl_Widget* OpenButton, void* Obj)
{
	static_cast<Menu*>(Obj)->Emit();
}

void Menu::Emit()
{
	// Open FileChooser and emit signal if file is choosen
	if (Chooser.show() == 0)
	{
		MenuSignal(Chooser.filename());
	}
}

boost::signals2::connection Menu::connect(const signal_t::slot_type &slot)
{
	return MenuSignal.connect(slot);
}
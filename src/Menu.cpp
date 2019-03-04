#include "Menu.h"


Menu::Menu() :
	Chooser(),
	OpenButton (30, 30, 100, 30, "Open .wav file"),
	FileInfo (200, 30, 220, 30, "000")
{
	OpenButton.callback (CbOpenButton, this);
	Chooser.filter("*.wav");
}

Menu::~Menu() {}

void Menu::CbOpenButton(Fl_Widget* OpenButton, void* Obj)
{
	static_cast<Menu*>(Obj)->Emit();
}


void Menu::Emit()
{
	// Open FileChooser and emit signal if file is choosen
	if (Chooser.show() == 0)
	{
		MenuSignal();
	}
}

boost::signals2::connection Menu::connect(const signal_t::slot_type &subscriber)
{
	return MenuSignal.connect(subscriber);
}

std::string Menu::GetFilename()
{
	return Chooser.filename();
}
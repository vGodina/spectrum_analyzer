#include "Menu.h"
#include <iostream>

Menu::Menu(int x, int y, int w, int h, std::unique_ptr<IFileChooser> FileChooser, std::unique_ptr<IButton> Button) :
	Group{ x, y, w, h },
	Chooser{ std::move(FileChooser) },
	OpenButton {std::move(Button)}
{
	OpenButton->callback (CbOpenButton, this);
	Chooser->filter("Audio files\t*.wav");

	Group.add(OpenButton->GetImplWidget());

	Group.end();
}

void Menu::CbOpenButton(Fl_Widget*, void* Obj)
{
	static_cast<Menu*>(Obj)->Emit();
}

void Menu::Emit()
{
	// Open FileChooser and emit signal if file is choosen
	if (Chooser->show() == 0)
	{
		MenuSignal(std::data(Chooser->filename()));
	}
}

boost::signals2::connection Menu::connect(const signal_t::slot_type &slot)
{
	return MenuSignal.connect(slot);
}

Fl_Group* Menu::GetImplWidget()
{
	return &Group;
}
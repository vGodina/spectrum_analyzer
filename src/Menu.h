#include <fltk/Fl_Group.H>
#include "IMenu.h"
#include "IFileChooser.h"
#include "IButton.h"

class Menu : public IMenu {
public: 
	Menu(std::unique_ptr<IFileChooser> FileChooser, std::unique_ptr<IButton> Button);

	boost::signals2::connection connect (const signal_t::slot_type &slot);
	
	Fl_Group* GetImplWidget() override;

	void SetGeometry(int x, int y, int w, int h) override;

private:
	Fl_Group Group;
	std::unique_ptr<IFileChooser> Chooser;
	std::unique_ptr<IButton> OpenButton;

	signal_t MenuSignal;

	static void CbOpenButton(Fl_Widget*, void*);
	void Emit();
};
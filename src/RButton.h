#ifndef RBUTTON
#define RBUTTON
#include "IButton.h"
#include "fltk/Fl_Button.h"
#include <memory>

class RButton : public IButton
{
public:
	RButton(int x, int y, int w, int h, std::string_view L);

	void callback(Fl_Callback*, void*) override;
	virtual Fl_Widget* GetImplWidget() override;
private:
	Fl_Button Button;
};
#endif RBUTTON
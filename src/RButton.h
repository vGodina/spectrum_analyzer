#ifndef RBUTTON_H
#define RBUTTON_H

#include "IButton.h"
#include "fltk/Fl_Button.h"

class RButton : public IButton
{
public:
	RButton();

	void callback(Fl_Callback*, void*) override;

	virtual Fl_Widget* GetImplWidget() override;

	void SetGeometry(int x, int y, int w, int h) override;

	virtual void SetCaption(std::string_view L) override;

private:
	Fl_Button Button;
};

#endif
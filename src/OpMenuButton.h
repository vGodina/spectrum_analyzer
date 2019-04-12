#include "IButton.h"
#include "fltk/Fl_Button.h"
#include <memory>

class OpMenuButton : public IButton
{
public:
	OpMenuButton();

	void callback(Fl_Callback*, void*) override;
	virtual Fl_Widget* GetImplWidget() override;
private:
	Fl_Button Button;
};
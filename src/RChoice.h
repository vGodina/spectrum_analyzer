#ifndef RCHOICE_H
#define RCHOICE_H
#include "IChoice.h"
#include "fltk/Fl_Choice.h"
#include <memory>

class RChoice : public IChoice
{
public:
	RChoice();

	int value() const override;
	int value(int v) override;
	int add(std::string_view v) override;
	void callback(Fl_Callback*, void*) override;
	Fl_Widget* GetImplWidget() override;
	void SetGeometry(int x, int y, int w, int h) override;
	virtual void SetCaption(std::string_view L) override;
private:
	Fl_Choice Choice;
};
#endif RCHOICE_H
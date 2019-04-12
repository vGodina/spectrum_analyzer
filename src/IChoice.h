#ifndef ICHOICE
#define ICHOICE
#include <memory>
#include <string_view>
#include <fltk/Fl_Widget.h>

// Interface of Choice

struct IChoice
{
	virtual ~IChoice() = default;

	virtual int value() const = 0;
	virtual int value(int v) = 0;
	virtual int add(std::string_view v) = 0;
	virtual void callback(Fl_Callback*, void*) = 0;
	virtual Fl_Widget* GetImplWidget() = 0;
	virtual void SetGeometry(int x, int y, int w, int h) = 0;
	virtual void SetCaption(std::string_view L) = 0;
};
#endif
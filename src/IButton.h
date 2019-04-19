#ifndef IBUTTON
#define IBUTTON

#include <fltk/Fl_Widget.H>
#include <string_view>

// Interface of Button

struct IButton
{
	virtual ~IButton () = default;

	virtual void callback(Fl_Callback*, void*) = 0;

	virtual Fl_Widget* GetImplWidget() = 0;

	virtual void SetGeometry(int x, int y, int w, int h) = 0;

	virtual void SetCaption(std::string_view L) = 0;
};

#endif
#ifndef IBUTTON
#define IBUTTON
#include <memory>
#include <string_view>
#include <fltk/Fl_Widget.h>

// Interface of Button

 /*

*/

struct IButton
{
	virtual ~IButton () = default;

	virtual void callback(Fl_Callback*, void*) = 0;
	virtual Fl_Widget* GetImplWidget() = 0;
};
#endif IBUTTON
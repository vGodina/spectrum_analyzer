#ifndef IFILECHOOSER
#define IFILECHOOSER
#include <fltk/Fl_Widget.H>

// Interface of FileChooser

 /*
int show()
case -1:   // ERROR
case  1:   // CANCEL
default 0: // FILE CHOSEN

void filter(const char *f)
filter("Text\t*.txt\n" "C Files\t*.{cxx,h,c}");

const char *filename() const;

void filter(const char *f);
*/

struct IFileChooser
{
	virtual ~IFileChooser () = default;
	virtual void filter(const char*) = 0;
	virtual int show() = 0;
	virtual const char* filename () = 0;
	//virtual Fl_Widget* getImplWidget() = 0;
};
#endif IFILECHOOSER
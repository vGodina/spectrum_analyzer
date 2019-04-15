#ifndef IFILECHOOSER
#define IFILECHOOSER

#include <fltk/Fl_Native_File_Chooser.H>
#include <string_view>

/* Interface of FileChooser

void filter(const char *f);	//filter("Text\t*.txt\n" "C Files\t*.{cxx,h,c}");

int show()
case -1:   // ERROR
case  1:   // CANCEL
default 0: // FILE CHOSEN

const char *filename() const;
*/

struct IFileChooser
{
	virtual ~IFileChooser () = default;

	virtual void filter(std::string_view filter) = 0;

	virtual int show() = 0;

	virtual std::string_view filename() = 0;
};
#endif
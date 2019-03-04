#include <fltk/Fl_Box.h>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Native_File_Chooser.h>
#include <boost/signals2.hpp>


class Menu {
public:
	Menu();
	using signal_t = boost::signals2::signal<void (const std::string)>;
	boost::signals2::connection connect(const signal_t::slot_type &slot);
	std::string GetFilename();
private:
	Fl_Native_File_Chooser Chooser;
	Fl_Button OpenButton;
	Fl_Box FileInfo;
	signal_t MenuSignal;

	static void CbOpenButton(Fl_Widget*, void*);
	void Emit();
};
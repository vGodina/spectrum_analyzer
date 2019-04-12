#ifndef IMENU
#define IMENU
#include <boost/signals2.hpp>

// Interface of AudioFile

struct IMenu
{
	virtual ~IMenu() = default;

	using signal_t = boost::signals2::signal <bool (std::string)>;

	virtual boost::signals2::connection connect (const signal_t::slot_type &slot) = 0;

	virtual Fl_Widget* GetImplWidget() = 0;

	virtual void SetGeometry(int x, int y, int w, int h) = 0;
};
#endif
#ifndef IMENU
#define IMENU
#include <boost/signals2.hpp>

// Interface of AudioFile

class IMenu
{
public:
	virtual ~IMenu() = default;
	using signal_t = boost::signals2::signal <bool (std::string)>;
	virtual boost::signals2::connection connect (const signal_t::slot_type &slot) = 0;
};
#endif IMENU